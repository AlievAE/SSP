#pragma once

#include "common.h"
#include <iostream>

using std::string;
using std::min;

int overlap(const string& A, const string& B) {
    int ov = 0;
    for (int i = 0; i < min(A.size(), B.size()); ++i) {
        auto suf = A.substr(A.size()-i, i);
        auto pref = B.substr(0, i);
        if (suf == pref) {
            ov = i;
        }
    }
    return ov;
}

string merge(const string& A, const string& B) {
    auto ov = overlap(A, B);
    return A.substr(0, A.size() - ov) + B;
}

string merge(const vector<string>& S) {
    string res;
    for (int i = 0; i < S.size() - 1; ++i) {
        res += S[i].substr(0, S[i].size() - overlap(S[i], S[i+1]));
    }
    res += S.back();
    return res;
}

vector<string> erase_sub(const vector<string>& S) {
    vector<string> result;
    for (int i = 0; i < S.size(); ++i) {
        bool used = false;
        for (int j = 0; j < S.size(); ++j) {
            if (is_substring(S[i], S[j]) && (j < i || S[i] != S[j])) {
                used = true;
                break;
            }
        }
        if (!used) {
            result.push_back(S[i]);
        }
    }
    return result;
}