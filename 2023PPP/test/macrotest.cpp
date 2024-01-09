

#define TEST(name, ...) name, __VA_ARGS__

TEST(int) add(int a, int b) { return a + b; }
/* int divide(int a, int b) { return a / b; } */
/* namespace Test { */
/* int a; */
/* int b; */
/**/
/* void setup() { */
/*   a = 1; */
/*   b = 2; */
/* } */
/**/
/* void test_add(const char *str = __builtin_FUNCTION()) { */
/*   setup(); */
/*   cout << "calling fn" << str << endl; */
/*   cout << "current fn" << __builtin_FUNCTION() << endl; */
/*   assert_equal(add(a, b), 3); */
/*   assert_equal(add(a, b), 4); */
/* } */
/* } // namespace Test */
/* int main(int argc, char *argv[]) { */
/*   Test::test_add(); */
/*   cout << __func__ << __FUNCTION__ << __PRETTY_FUNCTION__; */
/*   return 0; */
/* } */

/* https://en.cppreference.com/w/cpp/preprocessor/replace */
#define F(...) f(0 __VA_OPT__(, ) __VA_ARGS__)
F(a, b, c) // replaced by f(0, a, b, c)
F()        // replaced by f(0)

#define G(X, ...) f(0, X __VA_OPT__(, ) __VA_ARGS__)
G(a, b, c) // replaced by f(0, a, b, c)
G(a, )     // replaced by f(0, a)
G(a)       // replaced by f(0, a)

#define SDEF(sname, ...) S sname __VA_OPT__(= {__VA_ARGS__})
SDEF(foo);       // replaced by S foo;
SDEF(bar, 1, 2); // replaced by S bar = { 1, 2 };
