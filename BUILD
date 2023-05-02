load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "tinytest",
    srcs = ["tinytest.cpp"],
    hdrs = ["tinytest.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
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
