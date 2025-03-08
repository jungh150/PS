#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, k;
    cin >> a >> b >> k;

    vector<int> ans;
    ans.push_back(a);
    ans.push_back(b);

    for (int i = a + 1; i < b; i++) {
        if (i % a == 0 && b % i == 0) ans.push_back(i);
    }

    if (ans.size() >= k) {
        for (int i = 0; i < k; i++) cout << ans[i] << ' ';
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}