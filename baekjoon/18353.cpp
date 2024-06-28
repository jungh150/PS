#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<int> d(n);
    int maxa = 0;

    for (int i = 0; i < n; i++) {
        int maxt = 0;
        for (int j = 0; j < i; j++) {
            if (s[i] < s[j]) maxt = max(maxt, d[j]);
        }
        d[i] = maxt + 1;
        maxa = max(maxa, d[i]);
    }

    cout << n - maxa << '\n';
}