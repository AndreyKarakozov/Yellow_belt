#include <iostream>
#include <map>
#include <stdexcept>
using namespace std;

template <typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& m, KeyType k);

template <typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& m, KeyType k) {
	if (m.count(k) == 0) {
		throw runtime_error("Key doesn't exist");
	} else {
		return m[k];
	}
}

int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}
