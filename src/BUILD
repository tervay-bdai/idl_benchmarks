cc_library(
    name = "benchmark",
    srcs = [],
    hdrs = ["benchmark.h"],
)

cc_library(
    name = "consts",
    srcs = [],
    hdrs = ["consts.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":benchmark",
        ":benchmark_fbs",
        ":benchmark_proto2",
        ":benchmark_proto3",
        "@com_github_google_benchmark//:benchmark",
    ],
)

cc_library(
    name = "benchmark_fbs",
    srcs = [],
    hdrs = ["benchmark_fbs.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:address_book_fbs_cc",
    ],
)

cc_library(
    name = "benchmark_proto2",
    srcs = [],
    hdrs = ["benchmark_proto2.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:address_book_proto_2_cc",
    ],
)

cc_library(
    name = "benchmark_proto3",
    srcs = [],
    hdrs = ["benchmark_proto3.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:address_book_proto_3_cc",
    ],
)
