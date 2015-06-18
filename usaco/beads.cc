/*
ID: wulihua1
PROG:beads
LANG:C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int cal(const std::string& s, int N) {
	siz_t len  = s.size();
	vector<int> left_r(len + 1, 0), left_b(len + 1, 0), right_r(len + 1, 0), right_b(len + 1, 0);
	for (int i = 0; i < len; ++i) {
		if (s[i] == 'r') {

		}
	}



}
 
int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
	int N;
	fin >> N;
	std::string s;
	fin >> s;

	s += s;

	int cnt = cal(s, N);
	fout << cnt << endl;
    return 0;
}

