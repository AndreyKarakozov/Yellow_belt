#include <iostream>
#include <map>
#include <cinttypes>
#include <vector>
#include <tuple>
using namespace std;

enum class Lang {DE, FR, IT};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
			tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
	if (regions.size() == 0) {
		return 0;
	}

	int max_repeats = 0;
	map<Region, int> region_to_repeat_count;
	for (const Region& region : regions) {
		max_repeats = max(max_repeats, ++region_to_repeat_count[region]);
	}
	return max_repeats;
}

int main() {
	cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  },
	}) << endl;

	cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Toulouse",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  31
	  },
	}) << endl;

	return 0;
}

/*
Output:
3
1
 */
