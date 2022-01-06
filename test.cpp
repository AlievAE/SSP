#include "optimal.cpp"
#include "greedy.cpp"
#include "jiang.cpp"

#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<ctime>


using std::rand;

string rand_string(int n, int alph=4) {
    string s = "";
    for (int i = 0; i < n; ++i) {
        s += (rand() % 4) + 'a';
    }
    return s;
}

vector<string> rand_substrings(int n, int m, int replicate, int alph=4) {
    auto super = rand_string(n, alph);
    vector<string> res;
    for (int t = 0; t < replicate; ++t) {
        int start = rand() % (n - m + 1);
        res.push_back(super.substr(start, m));
    }
    return res;
}

struct experiment {
    string method;
    int length;
    double time;
};  

std::ostream& operator<<(std::ostream& out, const experiment& exp) {
    out << exp.method << " " << exp.length << " " << exp.time;
    return out;
 }

int main() {
    std::cout << "start, jiang_res, greedy_res, jiang_time, greedy_time\n";
    for (int i = 1000; i < 100000; i += 1000) {
        auto S = rand_substrings(i, 400, 3 * i / 400, 4);
        S = erase_sub(S);
        auto start = time(nullptr);
        auto jiang_res = jiang(S, true);
        auto chill = time(nullptr);
        auto greedy_res = greedy(S, true);
        auto finish = time(nullptr);
        std::cout << i << ", " << jiang_res.size() << ", " << greedy_res.size() << ", "
                  << chill - start << ", " << finish - chill << std::endl;
    }
}