########################################################################################################################
#                                                                                                                      #
# @file WORKSPACE                                                                                                      #
#                                                                                                                      #
# @brief Defines external modules available to all BUILD files in this workspace. This also marks the root folder of   #
# the workspace                                                                                                        #
# @copyright Copyright (C) 2023 by Tom Hicks <headhunter3@gmail.com                                                    #
#                                                                                                                      #
# Licensed under the MIT license. See below for details.                                                               #
#                                                                                                                      #
########################################################################################################################
#                                                                                                                      #
#  MIT License                                                                                                         #
#                                                                                                                      #
# Copyright (c) 2023 Tom Hicks <headhunter3@gmail.com>                                                                 #
#                                                                                                                      #
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated         #
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the  #
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to      #
# permit persons to whom the Software is furnished to do so, subject to the following conditions:                      #
#                                                                                                                      #
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the #
# Software.                                                                                                            #
#                                                                                                                      #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE #
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS   #
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR  #
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.     #
#                                                                                                                      #
########################################################################################################################
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

http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-b971ac5250ea8de900eae9f95e06548d14cd95fe",
    urls = ["https://github.com/abseil/abseil-cpp/archive/b971ac5250ea8de900eae9f95e06548d14cd95fe.zip"],
)

http_archive(
    name = "bazel_skylib",
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
)

http_archive(
    name = "cpputils",
    strip_prefix = "cpp-utils-52de4b8bc2f6d8118dba94ade47f70522ba87b56",
    urls = ["https://github.com/headhunter45/TinyTest/archive/460c9492d927689b9db7f28d8742705dc0bbee62.zip"],
)
