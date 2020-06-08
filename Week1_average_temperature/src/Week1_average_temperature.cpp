#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> temp(n);

	int64_t aver = 0;
	for (int& t : temp) {
		cin >> t;
		aver += t;
	}
	aver /= n;

	vector<size_t> days_greater_aver;
	for (size_t i = 0; i < temp.size(); ++i) {
		if (temp[i] > aver) {
			days_greater_aver.push_back(i);
		}
	}

	cout << days_greater_aver.size() << endl;
	for (auto day_num : days_greater_aver) {
		cout << day_num << ' ';
	}

	return 0;
}
