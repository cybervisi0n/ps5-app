project('ps5-app', ['c', 'cpp'],
    default_options: {
        'default_library': 'static',
        'prefer_static':    true
    },
    meson_version: '>=1.2.0',
    version: '1.0'
)

fs = import('fs')

ps5app_elf = executable(
    'ps5-app.elf',
    sources: files('src/main.cpp'),
    dependencies: [],
    link_args: [],
    native: false
)
