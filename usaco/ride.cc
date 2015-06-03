/*
ID: wulihua1
PROG:ride
LANG:C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int cal(string& a) {
	size_t size = a.size();
	int ret = 1;
	for (size_t i = 0; i < size; i++) {
		int cur = a[i] - 'A' + 1;
		ret = (ret * cur) % 47;
	}
	return ret;
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
	string a, b;
	fin >> a;
	fin >> b;

	int ret_a = cal(a);
	int ret_b = cal(b);
	if (ret_a == ret_b) {fout << "GO" << endl;}
	else { fout << "STAY" << endl;}
    return 0;
}

