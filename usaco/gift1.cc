/*
ID: wulihua1
PROG:gift1
LANG:C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>

using namespace std;

struct Account {
	string name;
	int	money;
	int initial;
	Account():name("default"), money(0) {}
	Account(const string& n) : name(n), money(0), initial(0) {}
	Account(const Account& that) : name(that.name), money(that.money), initial(that.initial) {}
};

int main() {
	typedef map<string, Account>::iterator it_type;

    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
	int a;
    fin >> a;
	map<string, Account> accounts;
	vector<string> person;

	for (int i = 0; i < a; i++) {
		string name;
		fin >> name;
		person.push_back(name);
		Account acc(name);
		accounts[name] = acc;
	}

	for (int i = 0; i < a; i++) {
		string accountName;
		fin >> accountName;
		int total, cnt;
		fin >> total >> cnt;

		if (total == 0 || cnt == 0) continue;

		Account& acc = accounts[accountName];

		acc.initial = total;

		acc.money += total % cnt;

		int avg = total / cnt;

		for (int i = 0; i < cnt; i++) {
			string name;
			fin >> name;
			accounts[name].money += avg;
		}
	}

	for (int i = 0; i < person.size(); i++) {
		string name = person[i];
		Account a(accounts[name]);
		int diff = a.money - a.initial;
		fout << name << " " << diff << endl;
	}

    return 0;
}

