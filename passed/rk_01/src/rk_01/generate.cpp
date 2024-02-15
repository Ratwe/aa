#include <string>
#include <iostream>
#include "generate.h"

using namespace std;

string generate_substring(int s) {
	string sub = "";

	for (int j = 0; j < s; j++)
		sub += 97 + rand() % 25;

	return sub;
}

string generate_string(string sub, int x) {
	srand(time(0));
	string str = "";
	int s = sub.length();

	for (int i = 0; i < x; i++) {
		int n = rand() % 8;

		if (n == 7) {
			str += sub[0] + sub[1];
			for (int j = 0; j < s; j++)
				str += sub[j];
		}
		else {
			for (int j = 0; j < s; j++)
				str += 97 + rand() % 25;
		}
	}

	return str;
}
