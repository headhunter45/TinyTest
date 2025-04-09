#include <iostream>
#include <string>
#include <vector>
#include "tinytest.h"

// Function to test: Simple add function
int add(int a, int b) {
    return a + b;
}

// Function to test: Concatenate strings
std::string concatenate(const std::string& a, const std::string& b) {
    return a + b;
}

// Function to test: Check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to test: Vector sum
int vectorSum(const std::vector<int>& vec) {
    int sum = 0;
    for (int v : vec) {
        sum += v;
    }
    return sum;
}

int main() {
    // Create test suites using TinyTest
    
    // Test suite for add function
    auto addSuite = TinyTest::MakeTestSuite(
        "AddFunction",  // Suite name
        add,            // Function to test
        {   // Test cases - each defined using MakeTest
            TinyTest::MakeTest("should add two positive numbers", 
                5,                // Expected result
                std::make_tuple(2, 3)), // Input parameters
                
            TinyTest::MakeTest("should add a positive and negative number", 
                -1,
                std::make_tuple(2, -3)),
                
            TinyTest::MakeTest("should add two negative numbers", 
                -5,
                std::make_tuple(-2, -3))
        }
    );
    
    // Test suite for concatenate function
    auto concatSuite = TinyTest::MakeTestSuite(
        "ConcatenateFunction", 
        concatenate,
        {
            TinyTest::MakeTest("should concatenate two strings", 
                std::string("HelloWorld"),
                std::make_tuple(std::string("Hello"), std::string("World"))),
                
            TinyTest::MakeTest("should concatenate with empty string", 
                std::string("Hello"),
                std::make_tuple(std::string("Hello"), std::string("")))
        }
    );
    
    // Test suite for isPrime function
    auto primeSuite = TinyTest::MakeTestSuite(
        "IsPrimeFunction", 
        isPrime,
        {
            TinyTest::MakeTest("should identify 2 as prime", 
                true,
                std::make_tuple(2)),
                
            TinyTest::MakeTest("should identify 4 as not prime", 
                false,
                std::make_tuple(4)),
                
            TinyTest::MakeTest("should identify 17 as prime", 
                true,
                std::make_tuple(17)),
                
            TinyTest::MakeTest("should identify negative numbers as not prime", 
                false,
                std::make_tuple(-7))
        }
    );
    
    // Test suite for vectorSum function with a custom compare function
    auto sumSuite = TinyTest::MakeTestSuite(
        "VectorSumFunction", 
        vectorSum,
        {
            TinyTest::MakeTest("should sum empty vector to 0", 
                0,
                std::make_tuple(std::vector<int>{})),
                
            TinyTest::MakeTest("should sum single element vector", 
                5,
                std::make_tuple(std::vector<int>{5})),
                
            TinyTest::MakeTest("should sum multiple elements", 
                10,
                std::make_tuple(std::vector<int>{1, 2, 3, 4}))
        }
    );
    
    // Execute all test suites and get the results
    TinyTest::TestResults results;
    results += TinyTest::ExecuteSuite(addSuite);
    results += TinyTest::ExecuteSuite(concatSuite);
    results += TinyTest::ExecuteSuite(primeSuite);
    results += TinyTest::ExecuteSuite(sumSuite);
    
    // Print the summary of results
    std::cout << "\nTest Results Summary:\n";
    TinyTest::PrintResults(std::cout, results);
    
    // Return non-zero exit code if there were failures or errors
    return (results.Errors() > 0 || results.Failed() > 0) ? 1 : 0;
} 