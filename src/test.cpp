#define _XOPEN_SOURCE_EXTENDED
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdint>
#include <vector>
#include "test.h"

// using namespace std;
using std::cout;
using std::tuple;
using std::wcerr;
using std::string;
using std::endl;
using std::pair;
using std::get;
using std::make_tuple;
using std::vector;
using Test::TestResults;
using std::optional;
using std::function;
using std::for_each;

// using namespace Test;

namespace Test {
    const string fn1(const string& s, int l) {
        return s.substr(0, l);
    }
  
    // Test lifecycle
    // suiteSetupFn(); - This is called to allocate any suite level resources. This is called once when the suite begins.
    // These functions may be called in parallel but execution will not proceed past this block until they have all finished.
    //   testSetupFn(); - This is called once for every test in tests. You may use it to allocate resources or setup mocks, stubs, and spies.
    //   testFn(...); - This is called once for every test to execute the test.
    //   Only one of these test functions will actually be run for each test in tests. They should return true if the test passed, return false if the test failed or there was an error, and be nullptr if they should be skipped. The executed function will be called with expectedOutput and the result of testFn(...). They can be used to test functions with side effects, especially void functions.
    //   maybe_compare_function; - This is the highest priority compare function. If it is not nullptr then it will be called.
    //   suite_compare_function; - This is the second highest priority compare function. If maybe_compare_function is nullptr and this is not nullptr then it will be called.
    //   [](TResult expected, TResult actual) { return expected, actual; } - This is the lowest priority compare function. If all other compare functions are nullptr then this will be called to evaluate the test.
    //   testTeardownFn(); - This is called once for every test in tests. You must free/release any resources allocated by testSetupFn.
    // This ends the parallel test functions section all tests will have completed before execution proceeds.
    // Collect reports - Ths step is not visible to the user at this point, but data returned by all of the test functions is collected here. This is where you will eventually be able to format/log data for reports.
    // suiteTeardownFn(); - This is called after all test calls have completed, all testTeardownFn calls have completed, and all test reports/logs have been written. You should free any resources allocated in suiteSetupFn.
    
    // TODO: Add TShared(*)(string /*test_name*/, UUID /*testRunId*/) allocateSharedData to the test tuple to make some shared data that can be used in a thread safe way by setup, teardown, and evaluate steps of the test.
    // TODO: Add TShared to be returned by the setup functions, and consumed by the evaluate and teardown functions.
    //   Suite setup/teardown functions should allocate/free.
    //   Test setup/teardown functions should consume the data allocated by Suite setup.
    //   Test setup functions may allocate additional resources. If they do then the allocated resources they should be freed by test teardown function.
    //   Suite and/or Test compare functions may consume this shared data, but it will not be shared with the execution of testFn.

    // This function is called to execute a test suite. You provide it with some configuration info, optional utility callback functions, and test data (input parameters for each call to testFn and the expected result). It returns a TestResults that should be treated as an opaque data type.
    // Not all parameters are named in code, but they are named and explained in the comments and will be described by those names below.
    //   string suite_label - This is the name of this test suite. It is used for reporting messages.
    //   FnToTest testFn - This is the function to test. This may be replaced if necessary by function. It may not currently support class methods, but that is planned.
    //   vector<tuple<...>> tests - This is the test run data. Each tuple in the vector is a single test run. It's members are explained below.
    //     string test_name - This is the name of this test. It is used for reporting messages.
    //     TResult expectedOutput - This is the expected result of executing this test.
    //     bool(*)(const TResult expected, const TResult actual) maybe_compare_function - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called to evaluate the test results. It takes the expected and actual results as parameters and should return true if the test passed and false otherwise. This may be changed to return a TestResults at some point.
    //     void(*)(TInputParams...) testSetupFn - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called before each test to setup the environment for the test. You may use it to allocate resources and setup mocks, stubs, and spies.
    //     void(*)(TInputParams...) testTeardownFn - This is optiona. If unset or set to nullptr it is skipped. If set to a function it is called after each test to cleanup the environment after the test. You should free resources allocated by testSetupFn.
    //     bool isEnabled - This is optional. If unset or set to true the test is run. If set to false this test is skipped. If skipped it will be reported as a skipped/disabled test.
    //   bool(*)(const TResult expected, const TResult actual) suite_compare_function - This is optional. If unset or set to nullptr it is skipped. If set to a function and maybe_compare_function is not called for a test run then this function is called to evaluate the test results. It takes the expected and actual results as parameters and should return true if the test passed and false otherwise. This may be changed to return a TestResults at some point.
    //   void(*)() suiteSetupFn - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called before starting this test suite to setup the environment. You may use it to allocate resources and setup mocks, stubs, and spies.
    //   void(*)() suiteTeardownFn - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called after all tests in this suite have finished and all reporting has finished. You should free resources allocated by suiteSetupFn.
    // This method should be called like so. This is the minimal call and omits all of the optional params. This is the most common usage. You should put one tuple of inputs and expected output for each test case.
    //   results = collect_and_report_TestResultstest_fn(
    //     "Test: functionUnderTest",
    //     functionUnderTest,
    //     vector({
    //       make_tuple(
    //         "ShouldReturnAppleForGroupId_1_and_ItemId_2",
    //         string("Apple"),
    //         make_tuple(1,2),
    //       ),
    //     }),
    //   );
    // The suites can be run from one file as such. From a file called ThingDoer_test.cpp to test the class/methods ThingDoer declared in ThingDoer.cpp. This isn't mandatory but is a best practice.
    // You can use testFn without calling collect_and_report_TestResults() and also could call it from a normal int main(int argc, char** argv) or other function.
    //   TestResults test_main_ThingDoer(int argc, char** argv) {
    //     TestResults results;
    //     results = collect_and_report_TestResults(results, testFn("doThing1", ...), argc, argv);
    //     results = collect_and_report_TestResults(results, testFn("doThing2", ...), argc, argv);
    //     return results;
    //   }
    // Then some test harness either generated or explicit can call test_main_ThingDoer(...) and optionally reported there. Reporting granularity is controlled by how frequently you call collect_and_report_TestResults(...).
    // You can combine test results with results = results + testFn(..); and then collect_and_report_TestResults on the aggregate TestResults value.
    
    template <typename TResult, typename... TInputParams>
    TestResults execute_suite(
        string suite_label,
        function<TResult(TInputParams...)> function_to_test,
        vector<TestTuple<TResult, TInputParams...>> tests,
        MaybeTestCompareFunction<TResult> maybe_suite_compare_function,
        MaybeTestConfigureFunction maybe_suite_before_each_function,
        MaybeTestConfigureFunction maybe_suite_after_each_function,
        bool is_enabled) {
        TestResults results;
        cout << "🚀 Beginning Suite: " << suite_label << endl;

        // Step 1: Suite Setup

        if (maybe_suite_before_each_function.has_value()) {
            (*maybe_suite_before_each_function)();
        }

        // Step 2: Execute Tests
        for_each(tests.begin(), tests.end(), [&suite_label, &function_to_test, &results, &maybe_suite_compare_function](
            TestTuple<TResult, TInputParams...> test_data
        ) {
            // Step 2a: Extract our variables from the TestTuple.
            const std::string& test_name = get<0>(test_data);
            const std::string qualified_test_name = suite_label + "::" + test_name;
            const TResult& expected_output = get<1>(test_data);
            std::tuple<TInputParams...> input_params = get<2>(test_data);
            MaybeTestCompareFunction<TResult> maybe_compare_function = get<3>(test_data);
            TestCompareFunction<TResult> compare_function = maybe_compare_function.has_value()
            ? *maybe_compare_function
            : maybe_suite_compare_function.has_value()
            ? *maybe_suite_compare_function
            : [](const TResult& l, const TResult& r){return l==r;};
            MaybeTestConfigureFunction before_each = get<4>(test_data);
            MaybeTestConfigureFunction after_each = get<5>(test_data);

            // Step 2b: Test Setup
            cout << "  Beginning Test: " << qualified_test_name << endl;
            if(before_each.has_value()) {
                (*before_each)();
            }

            TResult actual;
            try {
                // Step 2c: Execute the test method.
                actual = std::apply(function_to_test, input_params);
            } catch(const std::exception& ex) {
                cout << "    ERROR: Caught exception \"" << ex.what() << "\"" << endl;
            } catch(const std::string& message) {
                cout << "    ERROR: Caught string \"" << message << "\"" << endl;
            } catch(...) {
                cout << "    ERROR: Caught something that is neither an std::exception nor a std::string." << endl;
            }

            // Step 2d: Pass or fail.
            TestResults result;
            if (compare_function(expected_output, actual)) {
                result = TestResults().pass();
                cout << "    PASSED" << endl;
            } else {
                result = TestResults().fail();
                cout << "    FAILED: expected: " << expected_output << ", actual: " << actual << endl;
            }
            results += result;

            // Step 2e: Test Teardown
            if (after_each.has_value()) {
                (*after_each)();
            }
            cout << "  Ending Test: " << test_name << endl;
        });

        // Step 3: Suite Teardown
        if (maybe_suite_after_each_function.has_value()) {
            (*maybe_suite_after_each_function)();
        }
        cout << "Ending Suite: " << suite_label << endl;
        return results;
    }

    TestResults do_the_other_thing(){
        auto p1 = "Microsoft QBasic";
        auto p2 = 5;
        // auto exp = "Micro";
        string s = fn1("Microsoft QBasic", 5);
        TestResults tr;

        // tr = tr + execute_suite<string, const string&, int>(
        //     "Test 8 Function",
        //     (function<string(const string&, int)>)fn1,
        //     vector<TestTuple<string, const string&, int>>({
        //     // vector<tuple<string, string, tuple<const string&, int>, MaybeTestCompareFunction<string>>>({
        //         make_tuple(
        //             string("should do something"), // test_name
        //             string("Micro"), // expectedOutput
        //             make_tuple((string)p1, p2),// inputParams,
        //             std::nullopt, // compare_function
        //             std::nullopt, // before_each
        //             std::nullopt, // after_each
        //             true
        //         ),
        //         make_test<string, string, int>(
        //             "should do something else",
        //             "Micro",
        //             make_tuple((string)p1, p2)
        //         )
        //     }));
        
        auto test_data8 = vector<TestTuple<string, const string&, int>>({
            make_test<string, string, int>(
                "Test 8 equals", "Micro", make_tuple((string)p1, p2),
                [](const string& l, const string& r){ return l==r;}),
            make_test<string, string, int>(
                "Test 8 not equals", "Micro", make_tuple((string)p1, p2),
                [](const string& l, const string& r){ return l!=r;}
            ),
            make_test<string, string, int>("Test 8 default compare", "Micro", make_tuple((string)p1, p2)),
            make_test<string, string, int>("Test 8 default compare", "Micro", make_tuple((string)p1, p2)),
            make_test<string, string, int>("Test 8 default compare", "Micro", make_tuple((string)p1, p2))
        });
        tr = tr + execute_suite<string, const string&, int>(
            "Test 8 Function with extra data",
            (function<string(const string&, int)>)fn1,
            test_data8
        );

        return tr;
    }

    // _Step_9 - if T2 is a single value then make_tuple<T2>(T2) and call longer version
    // auto testFunction = [](int id){return id==0?"":"";};
    // auto compareFunction = [](const string a, const string b){return a==b;};
    // template<typename TResult, typename FnToTest, typename... TInputParams>

    // _Step_10 - 
    // test_fn(string, _FnToTest, vector<tuple<string, _T1, _CompareFn, <tuple<_T2...>>>)
    //   Default to (string, _FnToTest, vector<tuple<"", _T1, [](a,b){return a==b;}, make_tuple())
    //   Also allow make_tuple(T2) if the last param is not a tuple.

    TestResults::TestResults()
    : failed_(0)
    , passed_(0)
    , skipped_(0)
    , total_(0) {}

    TestResults::TestResults(const TestResults& other)
    : failed_(other.failed_)
    , passed_(other.passed_)
    , skipped_(other.skipped_)
    , total_(other.total_) {}

    TestResults::TestResults(uint32_t failed, uint32_t passed, uint32_t skipped, uint32_t total)
    : failed_(failed)
    , passed_(passed)
    , skipped_(skipped)
    , total_(total) {}

    TestResults& TestResults::fail() {
        total_++;
        failed_++;
        return *this;
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
        return TestResults(
            failed_ + other.failed_,
            passed_ + other.passed_,
            skipped_ + other.skipped_,
            total_ + other.total_);
    }

    TestResults& TestResults::operator+=(const TestResults& other) {
        failed_ += other.failed_;
        passed_ += other.passed_;
        skipped_ += other.skipped_;
        total_ += other.total_;
        return *this;
    }
} // End namespace Test
