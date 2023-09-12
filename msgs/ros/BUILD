load(
    "@com_github_mvukov_rules_ros2//ros2:interfaces.bzl",
    "cpp_ros2_interface_library",
    "py_ros2_interface_library",
    "ros2_interface_library",
)

package(default_visibility = ["//visibility:public"])

ros2_interface_library(
    name = "robolog_interface",
    srcs = glob(["*.msg"]),
    deps = [
        "@ros2_common_interfaces//:std_msgs",
    ],
)

cpp_ros2_interface_library(
    name = "robolog_interface_cc",
    deps = [":robolog_interface"],
)
