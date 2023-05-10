########################################################################################################################
#                                                                                                                      #
# @file BUILD                                                                                                          #
#                                                                                                                      #
# @brief Defines build rules including tests for the top level utilities.                                              #
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
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "tinytest",
    srcs = ["tinytest.cpp"],
    hdrs = ["tinytest.h"],
    includes = ["*.h"],
    visibility = ["//visibility:public"],
    deps = ["@cpputils//:pretty_print"],
)

cc_test(
    name = "tinytest_test",
    size = "small",
    srcs = ["tinytest_test.cpp"],
    deps = [
        ":tinytest",
        "@com_google_googletest//:gtest_main",
    ],
)
