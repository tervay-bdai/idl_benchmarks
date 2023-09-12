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
        ":benchmark_nanopb",
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
    copts = [
        # "-std=c99",
        # "-Wall",
        # "-Wstrict-prototypes",
        # "-Wextra",
        # # "-Wshorten-64-to-32",  # not in GCC (and my Kokoro images doesn't have Clang)
        # "-Werror",
        # "-Wno-unused-parameter",
        # "-Wno-long-long",
    ],
    deps = [
        ":benchmark",
        ":consts",
        "//msgs:address_book_upb_cc",
        "//msgs:address_book_upb_cc_reflection",
        "@upb",
    ],
)
