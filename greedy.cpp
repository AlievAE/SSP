#pragma once

#include "greedy.h"

string greedy(const vector<string>& S, bool adapted) {
    vector<string> curset = S;
    if (!adapted) {
        curset = erase_sub(curset);
    }
    int n = curset.size();
    while (n > 1) {
        pair<int, int> cand = {0, 1};
        int max_ov = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (overlap(curset[i], curset[j]) > max_ov) {
                    max_ov = overlap(curset[i], curset[j]);
                    cand = {i, j};
                }
                if (overlap(curset[j], curset[i]) > max_ov) {
                    max_ov = overlap(curset[j], curset[i]);
                    cand = {j, i};
                }
            }
        }
        vector<string> upd;
        for (int i = 0; i < n; ++i) {
            if (i != cand.first && i != cand.second) {
                upd.push_back(curset[i]);
            }
        }
        upd.push_back(merge(curset[cand.first], curset[cand.second]));
        curset = upd;
        n--;
    }
    return curset[0];
}
