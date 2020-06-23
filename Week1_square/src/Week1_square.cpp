#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <sstream>
using namespace std;

template <typename T>
T Sqr(T v);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);

template <typename T>
vector<T> Sqr(const vector<T>& v);

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);

template <typename T>
T Sqr(T v) {
	return v * v;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> result;
	for (auto i : v) {
		result.push_back(Sqr(i));
	}
	return result;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> result;
	for (auto i : m) {
		result[i.first] = Sqr(i.second);
	}
	return result;
}

int main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}
