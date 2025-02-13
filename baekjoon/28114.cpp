#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> years(3);
    vector<pair<int, string>> problems(3);
    
    for (int i = 0; i < 3; i++) {
        int p, y;
        string s;
        cin >> p >> y >> s;
        problems[i].first = p;
        problems[i].second = s;
        years[i] = y % 100;
    }

    sort(years.begin(), years.end());
    sort(problems.begin(), problems.end());

    for (int i = 0; i < 3; i++) cout << years[i];
    cout << '\n';

    for (int i = 2; i >= 0; i--) cout << problems[i].second[0];
    cout << '\n';
}