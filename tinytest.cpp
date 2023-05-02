/***************************************************************************************
 * @file tinytest.cpp                                                                  *
 *                                                                                     *
 * @brief Defines structs and functions for implementing TinyTest.                     *
 * @copyright Copyright 2023 Tom Hicks <headhunter3@gmail.com>                         *
 * Licensed under the MIT license see the LICENSE file for details.                    *
 ***************************************************************************************/

#define _XOPEN_SOURCE_EXTENDED
#include "tinytest.h"

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

namespace TinyTest {
namespace {
using std::endl;
using std::string;
using std::vector;
}  // End namespace

// TODO: Add TShared(*)(string /*test_name*/, UUID /*testRunId*/)
// allocateSharedData to the test tuple to make some shared data that can be
// used in a thread safe way by setup, teardown, and evaluate steps of the test.
// TODO: Add TShared to be returned by the setup functions, and consumed by the
// evaluate and teardown functions.
//   Suite setup/teardown functions should allocate/free.
//   Test setup/teardown functions should consume the data allocated by Suite
//   setup. Test setup functions may allocate additional resources. If they do
//   then the allocated resources they should be freed by test teardown
//   function. Suite and/or Test compare functions may consume this shared data,
//   but it will not be shared with the execution of function_to_test.

// Begin TestResults methods
TestResults::TestResults() : errors_(0), failed_(0), passed_(0), skipped_(0), total_(0) {}

TestResults::TestResults(const TestResults& other)
    : error_messages_(other.error_messages_),
      errors_(other.errors_),
      failed_(other.failed_),
      failure_messages_(other.failure_messages_),
      passed_(other.passed_),
      skip_messages_(other.skip_messages_),
      skipped_(other.skipped_),
      total_(other.total_) {}

TestResults::TestResults(uint32_t errors,
                         uint32_t failed,
                         uint32_t passed,
                         uint32_t skipped,
                         uint32_t total,
                         vector<string> error_messages,
                         vector<string> failure_messages,
                         vector<string> skip_messages)
    : error_messages_(error_messages),
      errors_(errors),
      failed_(failed),
      failure_messages_(failure_messages),
      passed_(passed),
      skip_messages_(skip_messages),
      skipped_(skipped),
      total_(total) {}

TestResults& TestResults::error() {
  errors_++;
  return *this;
}

TestResults& TestResults::error(string message) {
  errors_++;
  error_messages_.push_back(message);
  return *this;
}

TestResults& TestResults::fail() {
  total_++;
  failed_++;
  return *this;
}

TestResults& TestResults::fail(const string& message) {
  total_++;
  failed_++;
  failure_messages_.push_back(message);
  return *this;
}

vector<string> TestResults::failure_messages() {
  return failure_messages_;
}

TestResults& TestResults::pass() {
  total_++;
  passed_++;
  return *this;
}

TestResults& TestResults::skip() {
  total_++;
  skipped_++;
  return *this;
}

TestResults& TestResults::skip(const string& message) {
  total_++;
  skipped_++;
  skip_messages_.push_back(message);
  return *this;
}

vector<string> TestResults::skip_messages() {
  return skip_messages_;
}

vector<string> TestResults::error_messages() {
  return error_messages_;
}

uint32_t TestResults::errors() {
  return errors_;
}

uint32_t TestResults::failed() {
  return failed_;
}

uint32_t TestResults::passed() {
  return passed_;
}

uint32_t TestResults::skipped() {
  return skipped_;
}

uint32_t TestResults::total() {
  return total_;
}

TestResults TestResults::operator+(const TestResults& other) const {
  vector<string> error_messages;
  error_messages.insert(error_messages.end(), error_messages_.begin(), error_messages_.end());
  error_messages.insert(error_messages.end(), other.error_messages_.begin(), other.error_messages_.end());
  vector<string> failure_messages;
  failure_messages.insert(failure_messages.end(), failure_messages_.begin(), failure_messages_.end());
  failure_messages.insert(failure_messages.end(), other.failure_messages_.begin(), other.failure_messages_.end());
  vector<string> skip_messages;
  skip_messages.insert(skip_messages.end(), skip_messages_.begin(), skip_messages_.end());
  skip_messages.insert(skip_messages.end(), other.skip_messages_.begin(), other.skip_messages_.end());

  return TestResults(errors_ + other.errors_,
                     failed_ + other.failed_,
                     passed_ + other.passed_,
                     skipped_ + other.skipped_,
                     total_ + other.total_,
                     error_messages,
                     failure_messages,
                     skip_messages);
}

TestResults& TestResults::operator+=(const TestResults& other) {
  error_messages_.insert(error_messages_.end(), other.error_messages_.begin(), other.error_messages_.end());
  errors_ += other.errors_;
  failed_ += other.failed_;
  failure_messages_.insert(failure_messages_.end(), other.failure_messages_.begin(), other.failure_messages_.end());
  passed_ += other.passed_;
  skip_messages_.insert(skip_messages_.end(), other.skip_messages_.begin(), other.skip_messages_.end());
  skipped_ += other.skipped_;
  total_ += other.total_;
  return *this;
}

void PrintResults(std::ostream& os, TestResults results) {
  auto skip_messages = results.skip_messages();
  if (skip_messages.size() > 0) {
    os << "Skipped:" << endl;
    for_each(skip_messages.begin(), skip_messages.end(), [&os](const string& message) {
      os << "🚧Skipped: " << message << endl;
    });
  }
  auto failure_messages = results.failure_messages();
  if (failure_messages.size() > 0) {
    os << "Failures:" << endl;
    for_each(failure_messages.begin(), failure_messages.end(), [&os](const string& message) {
      os << "❌FAILED: " << message << endl;
    });
  }
  auto error_messages = results.error_messages();
  if (error_messages.size() > 0) {
    os << "Errors:" << endl;
    for_each(error_messages.begin(), error_messages.end(), [&os](const string& message) {
      os << "🔥ERROR: " << message << endl;
    });
  }
  os << "Total tests: " << results.total() << endl;
  os << "Passed:      " << results.passed() << " ✅" << endl;
  os << "Failed:      " << results.failed() << " ❌" << endl;
  os << "Skipped:     " << results.skipped() << " 🚧" << endl;
  os << "Errors:      " << results.errors() << " 🔥" << endl;
}

// End TestResults methods.

MaybeTestConfigureFunction DefaultTestConfigureFunction() {
  return std::nullopt;
}
}  // namespace TinyTest
