# Roomba Controller
C++ tools for controlling Roomba 650 series remotely.

## Compiling Locally
In order to build this you must have:

 - git
 - g++/clang (support for C++11)
 - [bazel](http://bazel.io/docs/install.html)

From the `base_workspace` directory simply:

    bazel build //cc/roomba

The binary and built libraries will be output to `bazel-bin`.

## Cross Compiling For ARM
In addition to the requirements listed above, you must download the appropriate
toolchains. In order to do this, first go to `toolchain_setup` and execute:

    ./setup-toolchain.sh /path/to/toolchain

where `/path/to/toolchain` is where you would like it to setup the toolchain
(this should be somewhere outside of this project).

Then call bazel as such:

    bazel build --dynamic_mode=off \
        --package_path=%workspace%:/path/to/toolchain:/path/to/bazel-repo \ 
        --crosstool_top=//arm-linux-gnueabi:toolchain \
        --host_crosstool_top=//tools/cpp:toolchain \
        --cpu=armeabi \
        --custom_malloc=//arm-linux-gnueabi:malloc \
        //cc/roomba

Now the output binaries are built for ARM.
