# ps5-app
A minimal template for building a native app to run from the PS5's home screen. Currently supports the meson build system, with plans to add support for other build systems. Based on the work of [BlackBearReloaded](https://github.com/blackbearreloaded/ps5-native-app-boilerplate) and the [PS5 Payload SDK](https://github.com/ps5-payload-dev/sdk)

## Requirements
Any linux system with Docker

## Usage
Use the ./drun.sh script to interface with the dev container. On the first run of the script, the image will be built locally.
 * ./drun.sh {command}
 * ./drun.sh --interactive

### Setup
1. ./drun.sh ./scripts/download_dependencies.sh
2. ./drun.sh ./setup_build_meson.sh
3. ./drun.sh meson compile -C build
4. Copy PPSA99999 folder from build/ to your PS5 /data/homebrew
5. Run ShadowMount+
6. Launch app from the PS5 homescreen

### Customization
* Change the serial of your app by editing app_serial in meson.build, don't forget to also edit param.json in sce_sys
* Replace the pic0, pic1, and icon0.png with any images
* Replace snd0.at9 with music encoded with ATRAC9