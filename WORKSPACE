load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
# To update config run `bazel run @hedron_compile_commands//:refresh_all`
http_archive(
    name = "hedron_compile_commands",
    sha256 = "99bc3106eb6ce5ffab3c31de8501d4d628de5f1acd74b8b563a876bd39a2e32f",
    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    strip_prefix = "bazel-compile-commands-extractor-b33a4b05c2287372c8e932c55ff4d3a37e6761ed",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/b33a4b05c2287372c8e932c55ff4d3a37e6761ed.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

http_archive(
    name = "com_google_googletest",
    sha256 = "d0491ad8a4f6d4dadbc33229a0a1c4bfd3b61a750411b69c4945acd5cbb6d73f",
    strip_prefix = "googletest-ccdeec888ebb740a7ea4e07d3e84a1b7ee32b315",
    urls = ["https://github.com/google/googletest/archive/ccdeec888ebb740a7ea4e07d3e84a1b7ee32b315.zip"],
)
