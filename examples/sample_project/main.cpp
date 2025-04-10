#include <iostream>
#include <string>
#include <vector>
#include <tinytest/tinytest.h>

// Function to test
std::string truncate(const std::string& text, int length) {
  if (text.length() <= length) {
    return text;
  }
  return text.substr(0, length) + "...";
}

int main() {
  // Define test suites using TinyTest
  auto truncate_tests = TinyTest::MakeTestSuite(
    "TruncateFunction",
    truncate,
    {
      TinyTest::MakeTest(
        "should return the original text if it's shorter than the limit",
        std::string("Hello"),
        std::make_tuple(std::string("Hello"), 10)
      ),
      TinyTest::MakeTest(
        "should truncate the text with ellipsis if it's longer than the limit",
        std::string("Hello..."),
        std::make_tuple(std::string("Hello, World!"), 5)
      ),
      TinyTest::MakeTest(
        "should handle empty strings",
        std::string(""),
        std::make_tuple(std::string(""), 5)
      )
    }
  );
  
  // Execute test suite
  auto results = TinyTest::ExecuteSuite(truncate_tests);
  
  // Print results
  TinyTest::PrintResults(std::cout, results);
  
  // Return non-zero exit code if any tests failed
  return (results.Failed() > 0 || results.Errors() > 0) ? 1 : 0;
} 