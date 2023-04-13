#ifndef TEST_H__
#define TEST_H__
#include <cstdint>
#include <tuple>
#include <utility>
#include <string>

// Test lifecycle
// suite_setup_function(); - This is called to allocate any suite level resources. This is called once when the suite begins.
// These functions may be called in parallel but execution will not proceed past this block until they have all finished.
//   test_setup_function(); - This is called once for every test in tests. You may use it to allocate resources or setup mocks, stubs, and spies.
//   function_to_test(...); - This is called once for every test to execute the test.
//   Only one of these test functions will actually be run for each test in tests. They should return true if the test passed, return false if the test failed or there was an error, and be nullptr if they should be skipped. The executed function will be called with expected_output and the result of function_to_test(...). They can be used to test functions with side effects, especially void functions.
//   test_compare_function; - This is the highest priority compare function. If it is not nullptr then it will be called.
//   suite_compare_function; - This is the second highest priority compare function. If test_compare_function is nullptr and this is not nullptr then it will be called.
//   [](TResult expected, TResult actual) { return expected, actual; } - This is the lowest priority compare function. If all other compare functions are nullptr then this will be called to evaluate the test.
//   test_teardown_function(); - This is called once for every test in tests. You must free/release any resources allocated by test_setup_function.
// This ends the parallel test functions section all tests will have completed before execution proceeds.
// Collect reports - Ths step is not visible to the user at this point, but data returned by all of the test functions is collected here. This is where you will eventually be able to format/log data for reports.
// suite_teardown_function(); - This is called after all test calls have completed, all test_teardown_function calls have completed, and all test reports/logs have been written. You should free any resources allocated in suite_setup_function.

namespace Test {
    using std::tuple;
    using std::pair;
    using std::vector;
    using std::string;

    /// @brief 
    class TestResults {
        public:
            /// @brief Creates an empty TestResults instance representing no tests run.
            TestResults();

            /// @brief Creates a new TestResults instance that is a copy of other.
            /// @param other 
            TestResults(const TestResults& other);
            
            /// @brief Creates a new TestResults instance with specific counts.
            /// @param failed The number of failed tests.
            /// @param passed The number of passed tests.
            /// @param skipped The number of skipped tests.
            /// @param total The total number of tests run. This should equal the sum of failed, passed, and skipped tests.
            TestResults(uint32_t failed, uint32_t passed, uint32_t skipped, uint32_t total);
            
            /// @brief Adds a failed test. This increments total and failed.
            /// @return A reference to this instance. Used for chaining.
            TestResults& fail();
            
            /// @brief Adds a passed test. This increments total and passed.
            /// @return A reference to this instance. Used for chaining.
            TestResults& pass();

            /// @brief Adds a skipped test. This increments total and skipped.
            /// @return A reference to this instance. Used for chaining.
            TestResults& skip();
            
            /// @brief Getter for the count of failed tests.
            /// @return The count of failed tests.
            uint32_t failed();
            
            /// @brief Getter for the count of passed tests.
            /// @return The count of passed tests.
            uint32_t passed();
            
            /// @brief Getter for the count of skipped tests.
            /// @return The count of skipped tests.
            uint32_t skipped();
            
            /// @brief Getter for the count of total tests.
            /// @return The count of total tests run.
            uint32_t total();

            /// @brief Returns the combination of this and another TestResults instance.
            /// @param other The other TestResults instance to add to this one.
            /// @return The combination of the two TestResults instances.
            TestResults operator+(const TestResults& other) const;
            
            /// @brief Adds another TestResults to this one and returns a reference to this instance.
            /// @param other The other TestResults instance to add to this one.
            /// @return A reference to this instance.
            TestResults& operator+=(const TestResults& other);
            
        private:
            uint32_t failed_;
            uint32_t passed_;
            uint32_t skipped_;
            uint32_t total_;
    };
   
    /// @brief 
    /// @tparam TResult 
    template<typename TResult>
    using TestCompareFunction = std::function<bool(const TResult& expected, const TResult& actual)>;

    /// @brief 
    /// @tparam TResult 
    template<typename TResult>
    using MaybeTestCompareFunction = std::optional<TestCompareFunction<TResult>>;

    using TestConfigureFunction = std::function<void()>;
    using MaybeTestConfigureFunction = std::optional<TestConfigureFunction>;

    /// @brief 
    /// @tparam TResult 
    /// @tparam ...TInputParams 
    template<typename TResult, typename... TInputParams>
    using TestTuple = std::tuple<
        const std::string& /* test_name */,
        const TResult& /* expected_output */,
        std::tuple<TInputParams...> /* input_params - The input parameters for this test. These will be used when calling std::apply with function_to_test to execute the test. */,
        MaybeTestCompareFunction<TResult> /* test_compare_function - If this is not nullprt then this function will be called instead of suite_compare_function to determine if the test passes. Use this to check for side effects of the test. Return true if the test passes and false otherwise. */,
        MaybeTestConfigureFunction /* test_setup_function - If this is not nullptr this function is called before each test to setup the environment. It is called with std::apply and input_params so you can use them to mock records with specific IDs or calculate an expected result. */,
        MaybeTestConfigureFunction /* test_teardown_function If this is not nullptr this function is called after each test to cleanup any allocated/shared resources. */,
        bool /* is_enabled If this is false the test, setup, and teardown functions are not run. */>;
    
    /// @brief 
    /// @tparam TResult 
    /// @tparam TFunctionToTest 
    /// @tparam ...TInputParams 
    template<typename TResult, typename... TInputParams>
    using TestSuite = std::tuple<
        std::string,
        std::function<TResult(TInputParams...)>,
        std::vector<TestTuple<TResult, TInputParams...>>,
        MaybeTestCompareFunction<TResult>,
        MaybeTestConfigureFunction,
        MaybeTestConfigureFunction,
        bool
    >;

    // This function is called to execute a test suite. You provide it with some configuration info, optional utility callback functions, and test data (input parameters for each call to function_to_test and the expected result). It returns a TestResults that should be treated as an opaque data type.
    // Not all parameters are named in code, but they are named and explained in the comments and will be described by those names below.
    //   string suite_name - This is the name of this test suite. It is used for reporting messages.
    //   TFunctionToTest function_to_test - This is the function to test. This may be replaced if necessary by std::function. It may not currently support class methods, but that is planned.
    //   vector<tuple<...>> tests - This is the test run data. Each tuple in the vector is a single test run. It's members are explained below.
    //     string test_name - This is the name of this test. It is used for reporting messages.
    //     TResult expected_output - This is the expected result of executing this test.
    //     bool(*)(const TResult expected, const TResult actual) test_compare_function - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called to evaluate the test results. It takes the expected and actual results as parameters and should return true if the test passed and false otherwise. This may be changed to return a TestResults at some point.
    //     void(*)(TInputParams...) test_setup_function - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called before each test to setup the environment for the test. You may use it to allocate resources and setup mocks, stubs, and spies.
    //     void(*)(TInputParams...) test_teardown_function - This is optiona. If unset or set to nullptr it is skipped. If set to a function it is called after each test to cleanup the environment after the test. You should free resources allocated by test_setup_function.
    //     bool is_enabled - This is optional. If unset or set to true the test is run. If set to false this test is skipped. If skipped it will be reported as a skipped/disabled test.
    //   bool(*)(const TResult expected, const TResult actual) suite_compare_function - This is optional. If unset or set to nullptr it is skipped. If set to a function and test_compare_function is not called for a test run then this function is called to evaluate the test results. It takes the expected and actual results as parameters and should return true if the test passed and false otherwise. This may be changed to return a TestResults at some point.
    //   void(*)() suite_setup_function - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called before starting this test suite to setup the environment. You may use it to allocate resources and setup mocks, stubs, and spies.
    //   void(*)() suite_teardown_function - This is optional. If unset or set to nullptr it is skipped. If set to a function it is called after all tests in this suite have finished and all reporting has finished. You should free resources allocated by suite_setup_function.
    // This method should be called like so. This is the minimal call and omits all of the optional params. This is the most common usage. You should put one tuple of inputs and expected output for each test case.
    //   results = collect_and_report_test_resultstest_fn(
    //     "Test: function_under_test",
    //     function_under_test,
    //     vector({
    //       make_tuple(
    //         "ShouldReturnAppleForGroupId_1_and_ItemId_2",
    //         string("Apple"),
    //         make_tuple(1,2),
    //       ),
    //     }),
    //   );
    // The suites can be run from one file as such. From a file called ThingDoer_test.cpp to test the class/methods ThingDoer declared in ThingDoer.cpp. This isn't mandatory but is a best practice.
    // You can use function_to_test without calling collect_and_report_test_results() and also could call it from a normal int main(int argc, char** argv) or other function.
    //   TestResults test_main_ThingDoer(int argc, char** argv) {
    //     TestResults results;
    //     results = collect_and_report_test_results(results, function_to_test("do_thing1", ...), argc, argv);
    //     results = collect_and_report_test_results(results, function_to_test("do_thing2", ...), argc, argv);
    //     return results;
    //   }
    // Then some test harness either generated or explicit can call test_main_ThingDoer(...) and optionally reported there. Reporting granularity is controlled by how frequently you call collect_and_report_test_results(...).
    // You can combine test results with results = results + function_to_test(..); and then collect_and_report_test_results on the aggregate TestResults value.

    /// @brief
    /// @tparam TResult The result type of the test.
    /// @tparam TInputParams... The types of parameters sent to the test function.
    /// @param suite_label The label for this test suite. For example a class name such as "MortgageCalculator".
    /// @param function_to_test The function to be tested. It will be called with std::apply and a std::tuple<TInputParams...> made from each item in tests.
    /// @param tests A std::vector of test runs.
    /// @param suite_compare_function A function used to compare the expected and actual test results. This can be overridden per test by setting test_compare_function.
    /// @param after_all This is called before each suite is started to setup the environment. This is where you should build mocks, setup spies, and test fixtures.
    /// @param before_all This is called after each suite has completed to cleanup anything allocated in suite_before_each.
    /// @param is_enabled If false none of these tests are run and they are all reported as skipped.
    template <typename TResult, typename... TInputParams>
    TestResults execute_suite(
        std::string suite_label,
        std::function<TResult(TInputParams...)> function_to_test,
        vector<TestTuple<TResult, TInputParams...>> tests,
        MaybeTestCompareFunction<TResult> suite_compare = std::nullopt,
        MaybeTestConfigureFunction before_all = std::nullopt,
        MaybeTestConfigureFunction after_all = std::nullopt,
        bool is_enabled = true
    );

    /// @brief 
    /// @tparam TResult The result type of the test.
    /// @tparam ...TInputParams The types of parameters sent to the test function.
    /// @param test_name The label for this test. For example "should calculate the interest".
    /// @param expected The expected output of calling the test function with these input parameters.
    /// @param input_params The input parameters to use when calling the test function.
    /// @param test_compare_fn An optional function that can be used to compare the expected and actual return values. This is good for when you only care about certain fields being equal.
    /// @param before_each This is called to setup the environment before running the test. This is where you should build mocks, setup spies, and set any other values you need before calling the test function.
    /// @param after_each This is called after each test run to cleanup anything allocated in before_each.
    /// @param is_enabled If false this test run is not executed and considered skipped for reporting purposes.
    /// @return A TestTuple suitable for use as a test run when calling test_fn.
    template<typename TResult, typename... TInputParams>
    TestTuple<TResult, TInputParams...> make_test(
            const string& test_name,
            const TResult& expected,
            tuple<TInputParams...> input_params,
            MaybeTestCompareFunction<TResult> test_compare_fn = std::nullopt,
            MaybeTestConfigureFunction before_each = std::nullopt,
            MaybeTestConfigureFunction after_each = std::nullopt,
            bool is_enabled = true) {
        return make_tuple(test_name, expected, input_params, test_compare_fn, before_each, after_each, is_enabled);
    }

    /// @brief 
    /// @tparam TResult 
    /// @tparam TFunctionToTest 
    /// @tparam ...TInputParams 
    /// @param suite_name 
    /// @param function_to_test 
    /// @param test_data 
    /// @param compare 
    /// @param before_each 
    /// @param after_each 
    /// @param is_enabled 
    /// @return 
    template<typename TResult, typename TFunctionToTest, typename... TInputParams>
    TestSuite<TResult, TInputParams...> make_test_suite(
        const string& suite_name,
        TFunctionToTest function_to_test,
        vector<TestTuple<TResult, TInputParams...>> test_data,
        MaybeTestCompareFunction<TResult> compare = std::nullopt,
        MaybeTestConfigureFunction before_each = std::nullopt,
        MaybeTestConfigureFunction after_each = std::nullopt,
        bool is_enabled = true) {
        return make_tuple(suite_name, function_to_test, test_data, compare, before_each, after_each, is_enabled);
    }

    template <typename TResult, typename... TInputParams>
    TestResults execute_suite(const TestSuite<TResult, TInputParams...>& test_suite) {
        return std::apply(execute_suite<TResult, TInputParams...>, test_suite);
    }

    /// @brief 
    /// @tparam ...TInputParams 
    /// @param first 
    /// @param second 
    /// @return 
    template<typename... TInputParams>
    MaybeTestConfigureFunction coalesce(
        MaybeTestConfigureFunction first,
        MaybeTestConfigureFunction second) {        
        if (first.has_value()) {
            if (second.has_value()) {
                // This is the only place we actually need to combine them.
                return [&first, &second](TInputParams... input_params) {
                    *first(input_params...);
                    *second(input_params...);
                };
            } else {
                return first;
            }
        } else {
            return second;
        }
    }
} // End namespace Test

// TODO: define operator<< for std::tuple.
// TODO: Add TShared(*)(string /*test_name*/, UUID /*test_run_id*/) allocate_shared_data to the test tuple to make some shared data that can be used in a thread safe way by setup, teardown, and evaluate steps of the test.
// TODO: Add TShared to be returned by the setup functions, and consumed by the evaluate and teardown functions.
//   Suite setup/teardown functions should allocate/free.
//   Test setup/teardown functions should consume the data allocated by suite setup.
//   Test setup functions may allocate additional resources. If they do then the allocated resources they should be freed by test teardown function.
//   Suite and/or test compare functions may consume this shared data, but it will not be shared with the execution of function_to_test.    
#endif // End !defined TEST_H__
