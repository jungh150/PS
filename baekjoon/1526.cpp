#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;

void func(int x, int cnt) {
    a.push_back(x);
    if (cnt == 7) return;
    func(10 * x + 4, cnt + 1);
    func(10 * x + 7, cnt + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    func(0, 0);
    sort(a.begin(), a.end());

    int an = a.size();
    for (int i = 1; i < an; i++) {
        if (a[i] > n) {
            cout << a[i - 1] << '\n';
            break;
        }
    }
}