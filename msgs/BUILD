load("@com_github_nanopb_nanopb//extra/bazel:nanopb_cc_proto_library.bzl", "cc_nanopb_proto_library")
load("@rules_flatbuffers//flatbuffers:cc_flatbuffers_library.bzl", "cc_flatbuffers_library")
load("@rules_flatbuffers//flatbuffers:flatbuffers_library.bzl", "flatbuffers_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@upb//bazel:upb_proto_library.bzl", "upb_proto_library", "upb_proto_reflection_library")

package(default_visibility = ["//visibility:public"])

flatbuffers_library(
    name = "address_book_fbs",
    srcs = ["address_book.fbs"],
)

cc_flatbuffers_library(
    name = "address_book_fbs_cc",
    deps = [":address_book_fbs"],
)

proto_library(
    name = "address_book_proto_2",
    srcs = ["address_book_2.proto"],
)

cc_proto_library(
    name = "address_book_proto_2_cc",
    deps = [":address_book_proto_2"],
)

proto_library(
    name = "address_book_proto_3",
    srcs = ["address_book_3.proto"],
)

cc_proto_library(
    name = "address_book_proto_3_cc",
    deps = [":address_book_proto_3"],
)

cc_nanopb_proto_library(
    name = "address_book_nanopb_cc",
    protos = [":address_book_proto_3"],
)

proto_library(
    name = "address_book_proto_upb",
    srcs = ["address_book_upb.proto"],
)

upb_proto_library(
    name = "address_book_upb_cc",
    deps = [
        ":address_book_proto_upb",
    ],
)

upb_proto_reflection_library(
    name = "address_book_upb_cc_reflection",
    deps = [
        ":address_book_proto_upb",
    ],
)

proto_library(
    name = "robolog_pb2",
    srcs = ["robolog_pb2.proto"],
)

cc_proto_library(
    name = "robolog_pb2_cc",
    deps = [":robolog_pb2"],
)

proto_library(
    name = "robolog_pb3",
    srcs = ["robolog_pb3.proto"],
)

cc_proto_library(
    name = "robolog_pb3_cc",
    deps = [":robolog_pb3"],
)

flatbuffers_library(
    name = "robolog_fbs",
    srcs = ["robolog_fbs.fbs"],
)

cc_flatbuffers_library(
    name = "robolog_fbs_cc",
    deps = [":robolog_fbs"],
)
