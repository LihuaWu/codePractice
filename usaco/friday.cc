/*
ID: wulihua1
PROG:friday
LANG:C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void cal(int n, vector<int>& v) {
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int start = 0;
	for (int i = 0; i < n; i++) {
		int year = 1900 + i;
//		bool isLeapYear = year % 4 != 0 ? false : year % 100 != 0 ? true : year % 400 == 0 ? true : false; 
		bool isLeapYear = y % 4 == 0 && (y %100 != 0 || y % 400 == 0);
		for (int month = 1; month <= 12; month++) {
			v[(start + 12) % 7] += 1;
			start += days[month - 1];
			if (month == 2 && isLeapYear) {
				start += 1;
			}
		}
	}
}

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
	int N;
	fin >> N;

	vector<int> cnt(7);
	cal(N, cnt);

	for (size_t i = 0; i < cnt.size(); ++i) {
		int idx = (i + 5) % 7;
		fout << cnt[idx];
		if (i != cnt.size() - 1) {
			fout << " ";
		}
	}
	fout << endl;
    return 0;
}
