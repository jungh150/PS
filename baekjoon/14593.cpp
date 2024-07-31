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
    vector<int> c(n);
    vector<int> l(n);

    for (int i = 0; i < n; i++) {
        cin >> s[i] >> c[i] >> l[i];
    }

    int win = 0;
    for (int i = 0; i < n; i++) {
        if ((s[i] > s[win]) || (s[i] == s[win] && c[i] < c[win])
        || (s[i] == s[win] && c[i] == c[win] && l[i] < l[win])) {
            win = i;
        }
    }

    cout << win + 1 << '\n';
}