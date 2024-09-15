#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (true) {
        string str;
        cin >> str;
        if (str == "0") break;
        int n = str.size();

        int num = stoi(str);
        while (true) {
            string tmp = to_string(num);
            while (tmp.size() < n) tmp = "0" + tmp;

            bool fin = true;
            for (int i = 0; i < n / 2; i++) {
                if (tmp[i] != tmp[n - i - 1]) {
                    fin = false;
                    break;
                }
            }

            if (fin) break;
            num++;
        }

        cout << num - stoi(str) << '\n';
    }
}