#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<long long> a;

    while (n--) {
        long long x;
        cin >> x;
        string s = to_string(x);
        reverse(s.begin(), s.end());
        a.push_back(stoull(s));
    }

    sort(a.begin(), a.end());

    for (long long x: a) cout << x << '\n';
}