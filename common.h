#pragma once

#include<string>
#include<vector>

using std::string;
using std::min;
using std::vector;

int overlap(const string& A, const string& B);

string merge(const string& A, const string& B);
string merge(const vector<string>& S);

bool is_substring(const string& small, const string& big) {
    return big.find(small) != std::string::npos;
}
vector<string> erase_sub(const vector<string>& S);