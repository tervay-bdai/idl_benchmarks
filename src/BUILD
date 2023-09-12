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
        # ":benchmark_nanopb",
        ":benchmark_proto2",
        ":benchmark_proto3",
        ":benchmark_upb",
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
        "//msgs:robolog_fbs_cc",
    ],
)

cc_library(
    name = "benchmark_proto2",
    srcs = [],
    hdrs = ["benchmark_proto2.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:robolog_pb2_cc",
    ],
)

cc_library(
    name = "benchmark_proto3",
    srcs = [],
    hdrs = ["benchmark_proto3.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:robolog_pb3_cc",
    ],
)

cc_library(
    name = "benchmark_nanopb",
    srcs = [],
    hdrs = ["benchmark_nanopb.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:address_book_nanopb_cc",
    ],
)

cc_library(
    name = "benchmark_upb",
    srcs = [],
    hdrs = ["benchmark_upb.h"],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:robolog_upb_cc",
        "//msgs:robolog_upb_cc_reflection",
        "@upb",
    ],
)
