#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<long long> t(n + 1, 0);
    t[0] = 1;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < i; j++) {
            t[i] += t[j] * t[i - j - 1];
        }
    }

    cout << t[n] << '\n';
}