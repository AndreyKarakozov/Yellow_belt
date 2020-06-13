/*
bool operator<(const Region& lhs, const Region& rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
			tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
	if (regions.size() == 0) {
		return 0;
	}

	map<Region, int> repeats;	//регион -> число повторов региона
	for (const Region& r : regions) {
		repeats[r]++;
	}

	int max_repeats = 0;
	for (const auto i : repeats) {
		if (max_repeats < i.second) {
			max_repeats = i.second;
		}
	}
	return max_repeats;
}
*/
