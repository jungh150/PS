#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 첫번째 방법:
// 품질이 가장 높은 미니어쳐 (여러개라면 가격 가장 낮은거)
// 두번째 방법:
// 가격이 가장 낮은 미니어쳐 (여러개라면 품질 가장 높은거)

// 품질 내림차순, 가격 오름차순
bool compare1(pair<int, int> &a, pair<int, int> &b) {
    if (a.first == b.first) return a.second < b.second;
    else return a.first > b.first;
}

// 가격 오름차순, 품질 내림차순
bool compare2(pair<int, int> &a, pair<int, int> &b) {
    if (a.second == b.second) return a.first > b.first;
    else return a.second < b.second;
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int q, p;
        cin >> q >> p;
        a[i] = {q, p};
    }

    sort(a.begin(), a.end(), compare1);
    for (int i = 0; i < 2; i++) cout << a[i].first << ' ' << a[i].second << ' ';
    cout << '\n';

    sort(a.begin(), a.end(), compare2);
    for (int i = 0; i < 2; i++) cout << a[i].first << ' ' << a[i].second << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}