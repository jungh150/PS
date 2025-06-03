#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    set<int> s;

    int cur = 0;
    int pre = 0;
    s.insert(cur);
    for (int i = 1; i < n + 1; i++) {
        cur = pre - i;
        if (cur < 0 || s.count(cur)) cur = pre + i;
        s.insert(cur);
        pre = cur;
    }

    cout << cur << '\n';
}