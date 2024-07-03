#include <iostream>
#include <deque>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tn;
    cin >> tn;
    
    while(tn--) {
        string func;
        cin >> func;

        int n;
        cin >> n;

        string str;
        cin >> str;

        string tmp;
        deque<int> deq;
        for (char c: str) {
            if (c == '[') {
                continue;
            } else if (c == ',' || c == ']') {
                if (tmp != "") deq.push_back(stoi(tmp));
                tmp = "";
            } else {
                tmp = tmp + c;
            }
        }

        bool reverse = false;
        bool isError = false;

        for (char c: func) {
            if (c == 'R') {
                if (reverse) reverse = false;
                else reverse = true;
            } else if (c == 'D') {
                if (deq.empty()) {
                    isError = true;
                    break;
                }
                if (reverse) deq.pop_back();
                else deq.pop_front();
            }
        }

        if (isError) {
            cout << "error\n";
        } else {
            cout << "[";
            if (deq.empty()) {
                cout << "]\n";
            } else {
                if (reverse) {
                    while (deq.size() > 1) {
                        cout << deq.back() << ",";
                        deq.pop_back();
                    }
                    cout << deq.back() << "]\n";
                } else {
                    while (deq.size() > 1) {
                        cout << deq.front() << ",";
                        deq.pop_front();
                    }
                    cout << deq.front() << "]\n";
                }
            }
        }
    }
}