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

fs = import('fs')

subdir('tools')

ps5app_elf = executable(
    'ps5-app.elf',
    sources: files('src/main.cpp'),
    dependencies: [],
    link_args: [
        '-lSceSystemService',
        '-lSceVideoOut'
        ],
    native: false
)

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

ps5app_self = custom_target(
    'ps5-app.self',
    output: 'ps5-app.self',
    depends: [ps5app_elf],
    command: [ ps5_native_tool_exe, 
               'self',
               '--sign',
               '--in',
               ps5app_elf,
               '--out',
               '@OUTPUT@' ]
)

build_app_folder_sh = files('scripts/build_app_folder.sh')
sce_sys_source = meson.project_source_root() + '/sce_sys'


app_folder = custom_target(
    app_serial,
    output: app_serial,
    build_by_default: true,
    depends: [libc_prx, ps5app_self],
    command: [
        build_app_folder_sh,
        meson.project_source_root(),
        ps5app_self,
        libc_prx,
        sce_sys_source,
        '@OUTPUT@'
    ]
)