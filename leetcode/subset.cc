#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void dfs(const vector<int>& s,
			vector<int>::iterator start,
			vector<int>& path,
			vector<vector<int> >& result) {
	for_each(path.begin(), path.end(), [](int c) {cout << c << " ";});
	cout<<endl;
	result.push_back(path);
	for (auto i = start; i < s.end(); i++) {
		if (i != start && *i == *(i - 1)) continue;
		printf("*i : %d *i-1 : %d :  ", *i, *(i-1));
		path.push_back(*i);
		dfs(s, i + 1, path, result);
		path.pop_back();
	}
}

vector<vector<int> > subsetsWithDup(vector<int>& s) {
	sort(s.begin(), s.end()); 
	vector<vector<int> > result;
	vector<int> path;
	dfs(s, s.begin(), path, result);
	return result;
}

int main() {
	vector<int> v = {1,2,2,3};
	subsetsWithDup(v);	
	return 0;
}
