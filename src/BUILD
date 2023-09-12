cc_library(
    name = "benchmark",
    srcs = [],
    hdrs = ["benchmark.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":benchmark",
        ":benchmark_fbs",
        "@com_github_google_benchmark//:benchmark",
    ],
)

cc_library(
    name = "benchmark_fbs",
    srcs = [],
    hdrs = ["benchmark_fbs.h"],
    deps = [
        ":benchmark",
        "//msgs:address_book_fbs_cc",
    ],
)
