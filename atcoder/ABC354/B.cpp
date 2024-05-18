#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> s;
vector<int> c;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    s = vector<string>(n);
    c = vector<int>(n);
    int t = 0;

    for (int i = 0; i < n; i++) {
        cin >> s[i] >> c[i];
        t += c[i];
    }

    sort(s.begin(), s.end());

    cout << s[t % n] << '\n';
}