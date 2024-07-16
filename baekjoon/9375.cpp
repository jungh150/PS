#include <iostream>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        map<string, int> m;
        int ans = 1;
        while (n--) {
            string name, type;
            cin >> name >> type;
            if (m.find(type) == m.end()) m.insert({type, 1});
            else m[type]++;
        }
        for (auto x: m) {
            ans *= x.second + 1;
        }
        cout << ans - 1 << '\n';
    }
}