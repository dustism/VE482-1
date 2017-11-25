//
// Created by liu on 17-11-7.
//

#include <ctime>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

void printRes(ostream &os, const vector<pair<size_t, size_t> > &resource) {
    os << "allocated ( ";
    for_each(resource.begin(), resource.end(), [&os](const pair<size_t, size_t> &p) {
        os << p.first << " ";
    });
    os << ") maximum ( ";
    for_each(resource.begin(), resource.end(), [&os](const pair<size_t, size_t> &p) {
        os << p.second << " ";
    });
    os << ")";
}

int main() {
    minstd_rand randEngine;
    randEngine.seed((size_t) time(0));

    size_t typeNum, processNum, availableInit;
    cout << "Input the number of resource types: ";
    cin >> typeNum;
    cout << "Input the number of processes: ";
    cin >> processNum;
    cout << "Input the number of resource initially: ";
    cin >> availableInit;
    cout << "Generate data: " << endl;
    list<pair<size_t, vector<pair<size_t, size_t> > > > data(processNum);
    vector<size_t> available(typeNum, 2);
    size_t i = 0;
    for (auto &process : data) {
        process.first = i++;
        process.second = vector<pair<size_t, size_t> >(typeNum);
        for (auto &resource: process.second) {
            size_t num = randEngine() % 10;
            resource.second = num;
            resource.first = num == 0 ? 0 : randEngine() % num;
        }
        cout << "P" << process.first << "\t";
        printRes(cout, process.second);
        cout << endl;
    }
    cout << "Begin simulation: " << endl;
    bool flag;
    do {
        flag = false;
        for (auto it = data.begin(); it != data.end();) {
            bool processable = true;
            auto it2 = available.begin();
            for_each(it->second.begin(), it->second.end(), [&it2, &processable](const pair<size_t, size_t> &p) {
                processable &= (p.second - p.first <= *(it2++));
            });
            if (processable) {
                flag = true;
                it2 = available.begin();
                for_each(it->second.begin(), it->second.end(), [&it2](pair<size_t, size_t> &p) {
                    *(it2++) += p.first;
                });
                cout << "Run P" << it->first << "\t";
                printRes(cout, it->second);
                cout << " available ( ";
                for_each(available.begin(), available.end(), [](const size_t &p) {
                    cout << p << " ";
                });
                cout << ")" << endl;
                it = data.erase(it);
            } else {
                ++it;
            }
        }
    } while (flag);
    if (data.empty()) {
        cout << "All completed" << endl;
    } else {
        cout << "Not completed, available( ";
        for_each(available.begin(), available.end(), [](const size_t &p) {
            cout << p << " ";
        });
        cout << ")" << endl;
        cout << "Remain processes:" << endl;
        for (auto &process : data) {
            cout << "P" << process.first << "\t";
            printRes(cout, process.second);
            cout << endl;
        }
    }
    return 0;
}


