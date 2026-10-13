FROM debian:13

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential meson \
    python3 libnss-unknown fuse file \
    ninja-build wget ca-certificates git \
    clang unzip llvm lld zlib1g-dev \
    imagemagick

RUN mkdir -p /home
RUN chmod 777 /home
