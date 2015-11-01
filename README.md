
# Cross compiling roomba controller

    blaze build --dynamic_mode=off \
        --package_path=%workspace%:$HOME/crosstools/arm:$HOME/repos/bazel \ 
        --crosstool_top=//arm-linux-gnueabi:toolchain \
        --host_crosstool_top=//tools/cpp:toolchain \
        --cpu=armeabi \
        --custom_malloc=//arm-linux-gnueabi:malloc \
        //cc/roomba

