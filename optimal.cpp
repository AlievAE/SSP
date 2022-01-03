#pragma once

#include "optimal.h"


string optimal(const vector<string>& S, bool adapted) {
    auto S_adapted = S;
    if (!adapted) {
        S_adapted = erase_sub(S_adapted);
    }
    vector<int> perm;
    for (int i = 0; i < S_adapted.size(); ++i) {
        perm.push_back(i);
    }
    string result = merge(S_adapted);
    while (next_permutation(perm.begin(), perm.end())) {
        vector<string> str_perm;
        for (int i = 0; i < S_adapted.size(); ++i) {
            str_perm.push_back(S_adapted[perm[i]]);
        }
        auto cur_res = merge(str_perm);
        if (result.size() > cur_res.size()) {
            result = cur_res;
        }
    }
    return result;
}