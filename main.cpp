#include "optimal.cpp"
#include "greedy.cpp"
#include "young.cpp"

#include<iostream>
#include<iomanip>
#include<algorithm>

using std::rand;


vector<string> generate(int n=7, int min_size=3, int max_size=6, int alphabet=4) {
    vector<string> result;
    for (int i = 0; i < n; ++i) {
        int size = rand() % (max_size - min_size + 1) + min_size;
        string cur = "";
        for (int j = 0; j < size; ++j) {
            cur += 'a' + rand() % alphabet;
        }
        result.push_back(cur);
    }
    return result;
}

bool check_gen(int arg_num, char** argv) {
    vector<int> args = {7, 3, 6, 4};
    for (int i = 3; i < arg_num; ++i) {
        args[i-3] = strtol(argv[i], NULL, 10);
    }
    if (args[2] < args[1] || arg_num == 4) {
        args[2] = args[1];
    }
    vector<double> rates;
    vector<double> rates_young;
    for (int i = 0; i < strtol(argv[2], NULL, 10); ++i) {
        auto S = generate(args[0], args[1], args[2], args[3]);
        auto greedy_res = greedy(S);
        auto opt_res = optimal(S);
        auto young_res = young(S);
        double rate = (double)(greedy_res.size()) / opt_res.size();
        double rate_y = (double)(young_res.size()) / opt_res.size();
        if (1 > rate || rate > 2) {
            std::cout << "ERROR!\n";
            std::cout << "greedy and optimal sizes are " << greedy_res.size() << " and " << opt_res.size();
            std::cout << "\nwrong rate on following set:\n";
            for (auto el : S) {
                std::cout << el << std::endl;
            }
            return false;
        }
        if (1 > rate_y || rate_y > 4) {
            std::cout << "ERROR!\n";
            std::cout << "young and optimal sizes are " << young_res.size() << " and " << opt_res.size();
            std::cout << "\nwrong rate on following set:\n";
            for (auto el : S) {
                std::cout << el << std::endl;
            }
            return false;
        }
        rates.push_back(rate);
        rates_young.push_back(rate_y);
    }
    std::cout << "min greedy rate = " << std::setprecision(3) << *(std::min_element(rates.begin(), rates.end())) << std::endl;
    std::cout << "max greedy rate = " << std::setprecision(3) << *(std::max_element(rates.begin(), rates.end())) << std::endl;
    std::cout << "min young rate = " << std::setprecision(3) << *(std::min_element(rates_young.begin(), rates_young.end())) << std::endl;
    std::cout << "max young rate = " << std::setprecision(3) << *(std::max_element(rates_young.begin(), rates_young.end())) << std::endl;
    return true;
}

void example() {
    int n;
    std::cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    std::cout << "straight merge: size " << merge(v).size() << ", string: " << merge(v) << "\n";
    std::cout << "greedy: size " << greedy(v).size() << ", string: " << greedy(v) << "\n";
    std::cout << "young: size " << young(v).size() << ", string: " << young(v) << "\n";
    std::cout << "optimal: size " << optimal(v).size() << ", string: " << optimal(v) << "\n";
}


int main(int argc, char** argv) {
    if (argc >= 2 && string(argv[1]) == "gen") {
        check_gen(argc, argv);
    } else {
        example();
    }
}