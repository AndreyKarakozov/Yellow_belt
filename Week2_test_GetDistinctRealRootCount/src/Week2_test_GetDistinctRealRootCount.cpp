#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
    const string& hint)
{
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
    func();
    cerr << test_name << " OK" << endl;
  } catch (runtime_error& e) {
    ++fail_count;
    cerr << test_name << " fail: " << e.what() << endl;
  }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


//int GetDistinctRealRootCount(double a, double b, double c);

void TestNormalCase() {
  // x^2 - 5x + 6 = 0
  // x1 = 3; x2 = 2
  AssertEqual(GetDistinctRealRootCount(1.0, -5.0, 6.0), 2, "normal case");
}

void TestDoubleRoot() {
  // x^2 - 4x + 4 = 0
  // x1 = 2; x2 = 2
  AssertEqual(GetDistinctRealRootCount(1.0, -4.0, 4.0), 1, "double root");
}

void TestNoRoots() {
  // x^2 + 4 = 0
  AssertEqual(GetDistinctRealRootCount(1.0, 0, 4.0), 0, "no roots");
}

void TestLinearCase() {
  // 4x + 17 = 0
  AssertEqual(GetDistinctRealRootCount(0, 4.0, 17.0), 1, "linear");
}

void TestAAndBZeros() {
  // 42 = 0
  AssertEqual(GetDistinctRealRootCount(0, 0, 42), 0, "case a = b = 0");
}

void TestAll() {
  TestRunner test_runner;
  test_runner.RunTest(TestNormalCase, "TestNormalCase");
  test_runner.RunTest(TestDoubleRoot, "TestDoubleRoot");
  test_runner.RunTest(TestNoRoots, "TestNoRoots");
  test_runner.RunTest(TestLinearCase, "TestLinearCase");
  test_runner.RunTest(TestAAndBZeros, "TestAAndBZeros");
}


int main() {
  TestAll();

}
