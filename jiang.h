#pragma once

#include<vector>
#include<algorithm>

#include "common.cpp"

using std::vector;
using std::sort;
using std::pair;


vector<int> assignment_hungary(int n, int m, const vector<vector<int>>& graph);
vector<int> assignment_greedy(int n, const vector<vector<int>>& graph);
string jiang(const vector<string>& S, bool adapted = false);