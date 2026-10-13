#!/bin/bash


PAYLOAD_SDK_URL=https://github.com/ps5-payload-dev/sdk/releases/latest/download/ps5-payload-sdk.zip
WIBO_URL=https://github.com/decompals/wibo/releases/latest/download/wibo-x86_64

mkdir -p deps/

wget $PAYLOAD_SDK_URL
unzip ./ps5-payload-sdk.zip -d deps
rm -f ps5-payload-sdk.zip
