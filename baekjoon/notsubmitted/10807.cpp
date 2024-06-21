#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> num(n);
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    int v;
    cin >> v;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (v == num[i]) cnt++;
    }

    cout << cnt << '\n';
}