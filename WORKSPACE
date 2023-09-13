load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "upb",
    commit = "e7430e66d6e51def2a88f0b66fdab62b0d9492c1",
    remote = "https://github.com/protocolbuffers/upb.git",
)

load("@upb//bazel:workspace_deps.bzl", "upb_deps")

upb_deps()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "b1e80761a8a8243d03ebca8845e9cc1ba6c82ce7c5179ce2b295cd36f7e394bf",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.25.0/rules_docker-v0.25.0.tar.gz"],
)

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

http_archive(
    name = "rules_proto",
    sha256 = "dc3fb206a2cb3441b485eb1e423165b231235a1ea9b031b4433cf7bc1fa460dd",
    strip_prefix = "rules_proto-5.3.0-21.7",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/5.3.0-21.7.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

http_archive(
    name = "rules_python",
    strip_prefix = "rules_python-0.25.0",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.25.0/rules_python-0.25.0.tar.gz",
)

git_repository(
    name = "com_github_nanopb_nanopb",
    commit = "f5f65a90c8057a591f3cc98de40874bd78c9880d",
    remote = "https://github.com/nanopb/nanopb.git",
)

load("@com_github_nanopb_nanopb//extra/bazel:nanopb_deps.bzl", "nanopb_deps")

nanopb_deps()

load("@rules_python//python:repositories.bzl", "py_repositories", "python_register_toolchains")

py_repositories()

python_register_toolchains(
    name = "python3_11",
    python_version = "3.8.10",
)

load("@com_github_nanopb_nanopb//extra/bazel:python_deps.bzl", "nanopb_python_deps")
load("@python3_11//:defs.bzl", "interpreter")

nanopb_python_deps(interpreter)

load("@com_github_nanopb_nanopb//extra/bazel:nanopb_workspace.bzl", "nanopb_workspace")

nanopb_workspace()

git_repository(
    name = "com_github_mvukov_rules_ros2",
    commit = "3fb8a99e074b166f21a719c6144a37eab35e9199",
    remote = "https://github.com/mvukov/rules_ros2.git",
)

load("@com_github_mvukov_rules_ros2//repositories:repositories.bzl", "ros2_repositories")

ros2_repositories()

load("@com_github_mvukov_rules_ros2//repositories:deps.bzl", "PIP_ANNOTATIONS", "ros2_deps")

ros2_deps()

python_register_toolchains(
    name = "rules_ros2_python",
    python_version = "3.8.13",
)

load("@rules_python//python:pip.bzl", "pip_parse")
load("@rules_ros2_python//:defs.bzl", python_interpreter_target = "interpreter")

pip_parse(
    name = "rules_ros2_pip_deps",
    annotations = PIP_ANNOTATIONS,
    python_interpreter_target = python_interpreter_target,
    requirements_lock = "@com_github_mvukov_rules_ros2//:requirements_lock.txt",
)

load(
    "@rules_ros2_pip_deps//:requirements.bzl",
    install_rules_ros2_pip_deps = "install_deps",
)

install_rules_ros2_pip_deps()

http_archive(
    name = "msgpack",
    build_file = "//buildfiles:msgpack.BUILD",
    strip_prefix = "msgpack-c-37fcaa1264746456c14aec08bf6efc8d1ab06f7b",
    url = "https://github.com/msgpack/msgpack-c/archive/37fcaa1264746456c14aec08bf6efc8d1ab06f7b.zip",
)
