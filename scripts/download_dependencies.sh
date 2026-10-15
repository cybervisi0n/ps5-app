#!/bin/bash


PAYLOAD_SDK_URL=https://github.com/ps5-payload-dev/sdk/releases/latest/download/ps5-payload-sdk.zip
PACBREW_RELEASE_URL=https://github.com/ps5-payload-dev/pacbrew-repo/releases/latest/download/ps5-payload-dev.tar.gz

mkdir -p deps/

wget $PAYLOAD_SDK_URL
unzip ./ps5-payload-sdk.zip -d deps
rm -f ps5-payload-sdk.zip

mkdir -p deps/include
mkdir -p deps/lib


#wget $PACBREW_RELEASE_URL
# Extract archive:/opt/ps5-payload-sdk/target/user/homebrew to deps/ps5-payload-sdk/target/user/homebrew

#tar -zxf ps5-payload-dev.tar.gz opt/ps5-payload-sdk/target/user/homebrew/

#rm -rf deps/ps5-payload-sdk/target/user/homebrew

#mv opt/ps5-payload-sdk/target/user/homebrew/ deps/ps5-payload-sdk/target/user/

#rm -rf opt
#rm -f ps5-payload-dev.tar.gz

