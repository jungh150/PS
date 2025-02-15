#include <iostream>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    set<int> s;
    int x;

    for (int i = 0; i < n; i++) {
        cin >> x;
        s.insert(x);
    }

    for (int i = 0; i < m; i++) {
        cin >> x;
        if (s.find(x) == s.end()) s.insert(x); // 없으면 삽입
        else s.erase(x); // 있으면 삭제
    }

    cout << s.size() << '\n';
}