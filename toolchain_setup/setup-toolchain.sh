#! /bin/sh

TOOLCHAIN_BASE_PATH=$1
TOOLCHAIN_URL=http://releases.linaro.org/14.11/components/toolchain/binaries/arm-linux-gnueabi/gcc-linaro-4.9-2014.11-x86_64_arm-linux-gnueabi.tar.xz
TOOLCHAIN_ARCHIVE=$TOOLCHAIN_BASE_PATH/arm-linux-gnueabi.tar.xz
TOOLCHAIN_FULL_PATH=$TOOLCHAIN_BASE_PATH/arm-linux-gnueabi

mkdir -p $TOOLCHAIN_FULL_PATH
wget $TOOLCHAIN_URL -O $TOOLCHAIN_ARCHIVE
tar -xvf $TOOLCHAIN_ARCHIVE -C $TOOLCHAIN_FULL_PATH --strip-components 1
cp -R arm-linux-gnueabi/* $TOOLCHAIN_FULL_PATH
