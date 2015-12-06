cc_binary(
  name = "roomba",
  srcs = ["main.cc"],
  deps = [
    ":config",
    ":error",
    ":roomba_controller",
    ":roomba_controller_factory",
    ":serial_port",
  ],
)

cc_library(
  name = "roomba_controller_factory",
  hdrs = ["roomba_controller_factory.h"],
  srcs = ["roomba_controller_factory.cc"],
  deps = [
    ":config",
    ":error",
    ":roomba_controller",
    ":serial_port",
  ],
)

cc_library(
  name = "config",
  hdrs = ["config.h"],
)

cc_library(
  name = "roomba_controller",
  hdrs = ["roomba_controller.h"],
  srcs = ["roomba_controller.cc"],
  deps = [
    ":error",
    ":serial_port",
  ],
)

cc_library(
  name = "serial_port",
  hdrs = ["serial_port.h"],
  srcs = ["serial_port.cc"],
  deps = [":error"],
)

cc_library(
  name = "error",
  hdrs = ["error.h"],
  srcs = ["error.cc"],
)
