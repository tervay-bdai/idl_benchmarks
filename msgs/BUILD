load("@com_github_nanopb_nanopb//extra/bazel:nanopb_cc_proto_library.bzl", "cc_nanopb_proto_library")
load("@rules_capnproto//capnp:capnp_library.bzl", "capnp_library")
load("@rules_capnproto//capnp:cc_capnp_library.bzl", "cc_capnp_library")
load("@rules_flatbuffers//flatbuffers:cc_flatbuffers_library.bzl", "cc_flatbuffers_library")
load("@rules_flatbuffers//flatbuffers:flatbuffers_library.bzl", "flatbuffers_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@upb//bazel:upb_proto_library.bzl", "upb_proto_library", "upb_proto_reflection_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "robolog_npb",
    srcs = ["robolog_npb.proto"],
    deps = ["@com_github_nanopb_nanopb//:nanopb_proto"],
)

cc_nanopb_proto_library(
    name = "robolog_npb_cc",
    defines = ["PB_FIELD_32BIT"],
    protos = [":robolog_npb"],
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

proto_library(
    name = "robolog_upb",
    srcs = ["robolog_upb.proto"],
)

upb_proto_library(
    name = "robolog_upb_cc",
    deps = [
        ":robolog_upb",
    ],
)

upb_proto_reflection_library(
    name = "robolog_upb_cc_reflection",
    deps = [
        ":robolog_upb",
    ],
)

capnp_library(
    name = "robolog_capnp",
    srcs = ["robolog_cnp.capnp"],
)

cc_capnp_library(
    name = "robolog_capnp_cc",
    deps = [":robolog_capnp"],
)
