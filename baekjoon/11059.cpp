#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();

    int maxt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; i + 2 * j - 1 < n; j++) {
            string s1 = s.substr(i, j);
            int sum1 = 0;
            for (char c: s1) sum1 += (c - '0');

            string s2 = s.substr(i + j, j);
            int sum2 = 0;
            for (char c: s2) sum2 += (c - '0');

            if (sum1 == sum2) maxt = max(maxt, 2 * j);
        }
    }

    cout << maxt << '\n';
}