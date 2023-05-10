# TinyTest
TinyTest is a minimal testing library. The name might change soon, because I realized there were already multiple projects called TinyTest.

## Test Lifecycle
1.  suite_setup_function() - This is called to allocate any suite level resources. This is called once when the suite begins.
2.  This section may be executed in parallel. These functions may be called in parallel but execution will not proceed past this block until they have all finished.
3.  test_setup_function() - This is called once for every test in tests. You may uske it to allocate resources or setup mocks, stubs, and spies.
4.  function_to_test(...) - Thiis is called once for every test row in tests. Only one of these test functions will actually be run for each test in tests. They should return true if the test passed, return false if the test failed or there was an error, and be nullptr if they should be skipped. The execution function will be called with expected_output and the result of function_to_test(...). They can be used to test functions with side effects, especially void functions.
5.  test_compare_function() - This is the highest priority compare function. If it is not nullptr then it will be called to evaluate the test results.
6.  suite_compare_function() - This is the second highest priority compare function. If test_compare_function is nullptr and this is not nullptr then it will be called to evaluate the test results.
7.  [](TResult expected, TResult actual) {return expected == actual; } - This is the lowest priority compare function. If all other compare functions are nullptr then this will be called to evaluate the test.
8.  test_teardown_function() - This is called once for every test in tests. You must free/release any resources allocated by test_setup_function.
9.  This ends the parallel test functions section all tests in this suite will have completed before execution proceeds.
10. Collect reports - This step is not visible to the user at this point, but data returned by all of the test functions is collected here. This is were you will eventually be able to format/log data for reports.
11. suite_teardown_function() - This is called after all tests calls in this suite have completed, all test_teardown_function calls have completed, and all test reports/logs have been written. You should free any resources allocated in suite_setup_function.

## TODO:
* Replace use of overridden operator<< with PrettyPrint function.
* Make ExecuteSuite work even if expected and actual are wstring, wstring_view, or wchar_t*
