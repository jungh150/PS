#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, string>> s(n);
    set<int> mrs;

    for (int i = 0; i < n; i++) {
        int tmp = 0;
        int maxt = 0;
        string cur;
        for (int j = 0; j < m; j++) {
            cin >> cur;
            if (cur == ".") {
                tmp++;
                if (tmp > maxt) maxt = tmp;
            } else {
                tmp = 0;
            }
        }
        string name;
        cin >> name;
        s[i].first = maxt;
        s[i].second = name;
        mrs.insert(maxt);
    }

    cout << mrs.size() << '\n';

    for (int i = 0; i < n; i++) {
        cout << s[i].first << ' ' << s[i].second << '\n';
    }
}