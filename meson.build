project('ps5-app', ['c', 'cpp'],
    default_options: {
        'default_library': 'static',
        'prefer_static':    true
    },
    meson_version: '>=1.2.0',
    version: '1.0'
)

# Define your app's serial below:
app_serial = 'PPSA99999'

# PS5 App C Runtime & native tools
subdir('crt')
subdir('tools')

# App code: define your source files in src/meson.build
subdir('src')

# These arguments are required to make an .ELF file that the PS5 will understand
elf_link_args = [
    '-nostartfiles',
    '-T' + meson.global_source_root() + '/' + 'ps5-elf.ld',
    '-e',
    '_start',
    '-Wl,--version-script=' + meson.global_source_root() + '/' + 'ps5-app-symbols.map',
]

# Add your own link arguments here
app_link_args = [
    '-lSceSystemService',
    '-lSceVideoOut',
]

# Link ELF file (PIE)
ps5app_elf = executable(
    'ps5-app.elf',
    sources: ps5app_srcs,
    dependencies: [],
    link_args: [elf_link_args, app_link_args],
    link_with: [crt_lib],
    native: false
)

# Convert elf file to PS5 ELF
eboot_elf = custom_target(
    'eboot.elf',
    output: 'eboot.elf',
    depends: [ps5app_elf],
    command: [
        ps5_native_tool_exe,
        'link',
        '--in',
        ps5app_elf,
        '--out',
        '@OUTPUT@',
        '--stub-dir',
        meson.global_source_root() + '/deps/ps5-payload-sdk/target/lib',
        '--module-sdk',
        '0x02000009',
        '--companion_sdk',
        '0x08050001',
        '--file-name',
        'eboot.elf'
    ]
)

# Sign eboot.elf to eboot.bin
eboot_bin = custom_target(
    'eboot.bin',
    output: 'eboot.bin',
    depends: [eboot_elf],
    command: [ ps5_native_tool_exe, 
               'self',
               '--sign',
               '--in',
               eboot_elf,
               '--out',
               '@OUTPUT@' ]
)

# Generate libc.prx stub (required by PS5 loader)
libc_prx = custom_target(
    'libc.prx',
    output: 'libc.prx',
    depends: [libc_elf],
    command: [ ps5_native_tool_exe, 
               'self',
               '--sign',
               '--in',
               libc_elf,
               '--out',
               '@OUTPUT@' ]
)

# Build the app folder
build_app_folder_sh = files('scripts/build_app_folder.sh')
sce_sys_source = meson.project_source_root() + '/sce_sys'
app_folder = custom_target(
    app_serial,
    output: app_serial,
    build_by_default: true,
    depends: [libc_prx, eboot_bin],
    command: [
        build_app_folder_sh,
        meson.project_source_root(),
        eboot_bin,
        libc_prx,
        sce_sys_source,
        '@OUTPUT@'
    ]
)
