#include <iostream>
#include <string>
#include <tinytest/tinytest.h>

// Function to test - simple calculator functions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

int main() {
    // Create and execute test suites
    auto addSuite = TinyTest::MakeTestSuite(
        "Addition",
        add,
        {
            TinyTest::MakeTest("should correctly add positive numbers", 
                5.0, 
                std::make_tuple(2.0, 3.0)),
            TinyTest::MakeTest("should handle negative numbers", 
                -1.0, 
                std::make_tuple(-4.0, 3.0)),
            TinyTest::MakeTest("should handle zeros", 
                3.0, 
                std::make_tuple(3.0, 0.0))
        }
    );
    
    auto subtractSuite = TinyTest::MakeTestSuite(
        "Subtraction",
        subtract,
        {
            TinyTest::MakeTest("should correctly subtract positive numbers", 
                2.0, 
                std::make_tuple(5.0, 3.0)),
            TinyTest::MakeTest("should handle negative numbers", 
                -7.0, 
                std::make_tuple(-4.0, 3.0)),
            TinyTest::MakeTest("should handle zeros", 
                3.0, 
                std::make_tuple(3.0, 0.0))
        }
    );
    
    auto multiplySuite = TinyTest::MakeTestSuite(
        "Multiplication",
        multiply,
        {
            TinyTest::MakeTest("should correctly multiply positive numbers", 
                15.0, 
                std::make_tuple(5.0, 3.0)),
            TinyTest::MakeTest("should handle negative numbers", 
                -12.0, 
                std::make_tuple(-4.0, 3.0)),
            TinyTest::MakeTest("should handle zeros", 
                0.0, 
                std::make_tuple(3.0, 0.0))
        }
    );
    
    auto divideSuite = TinyTest::MakeTestSuite(
        "Division",
        divide,
        {
            TinyTest::MakeTest("should correctly divide positive numbers", 
                2.0, 
                std::make_tuple(6.0, 3.0)),
            TinyTest::MakeTest("should handle negative numbers", 
                -2.0, 
                std::make_tuple(-6.0, 3.0))
            // Division by zero test will be handled separately
        }
    );
    
    // Execute test suites and collect results
    TinyTest::TestResults results;
    results += TinyTest::ExecuteSuite(addSuite);
    results += TinyTest::ExecuteSuite(subtractSuite);
    results += TinyTest::ExecuteSuite(multiplySuite);
    results += TinyTest::ExecuteSuite(divideSuite);
    
    // Manually test the division by zero case
    std::cout << "Testing division by zero exception handling:" << std::endl;
    try {
        divide(1.0, 0.0);
        std::cout << "  ❌FAILED: Division by zero did not throw an exception" << std::endl;
        results.Fail("Division by zero did not throw an exception");
    } catch (const std::invalid_argument&) {
        std::cout << "  ✅PASSED: Division by zero correctly threw an exception" << std::endl;
        results.Pass();
    } catch (...) {
        std::cout << "  ❌FAILED: Division by zero threw an unexpected exception type" << std::endl;
        results.Fail("Division by zero threw an unexpected exception type");
    }
    
    // Print the summary
    std::cout << "\nTest Results Summary:\n";
    TinyTest::PrintResults(std::cout, results);
    
    // Return non-zero exit code if there were failures or errors
    return (results.Errors() > 0 || results.Failed() > 0) ? 1 : 0;
} 