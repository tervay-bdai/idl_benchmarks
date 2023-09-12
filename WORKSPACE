load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "hedron_compile_commands",
    strip_prefix = "bazel-compile-commands-extractor-e16062717d9b098c3c2ac95717d2b3e661c50608",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/e16062717d9b098c3c2ac95717d2b3e661c50608.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

http_archive(
    name = "com_github_google_benchmark",
    strip_prefix = "benchmark-main",
    urls = ["https://github.com/google/benchmark/archive/main.zip"],
)

http_archive(
    name = "rules_flatbuffers",
    sha256 = "902e649b358846c762829e7aae78db346571ffed7f4a849deebf0f0f69fb398e",
    strip_prefix = "rules_flatbuffers-0.2.0",
    urls = ["https://github.com/kgreenek/rules_flatbuffers/archive/refs/tags/v0.2.0.tar.gz"],
)

load(
    "@rules_flatbuffers//flatbuffers:repositories.bzl",
    "flatbuffers_cc_toolchain",
    "flatbuffers_dependencies",
    "flatbuffers_toolchain",
)

flatbuffers_dependencies()

flatbuffers_toolchain()

flatbuffers_cc_toolchain()
