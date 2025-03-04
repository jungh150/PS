#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n ; i++) a[i] = i + 1;

    long long idx = 0;
    int curn = n;
    for (int i = 1; i < n; i++) {
        long long tmp = (long long) i * i * i - 1;
        idx = (idx + tmp) % curn;
        a.erase(a.begin() + idx);
        curn--;
    }

    cout << a[0] << '\n';
}