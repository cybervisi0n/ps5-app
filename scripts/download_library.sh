#!/bin/bash

# Usage: download_library.sh github-url release-file-name

GithubRepoUrl=$1
ReleaseFileName=$2

url=$GithubRepoUrl/releases/latest/download/$ReleaseFileName

rm -f temp.zip

wget $url -O temp.zip
unzip -o ./temp.zip -d deps

rm -f temp.zip
