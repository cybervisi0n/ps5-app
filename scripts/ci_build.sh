#!/bin/bash

./scripts/download_dependencies.sh
./setup_build_meson.sh
meson compile -C build
