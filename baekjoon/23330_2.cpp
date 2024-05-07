#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<long long> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    sort(data.begin(), data.end());

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (4 * i - 2 * n + 2) * data[i];
    }

    cout << sum << '\n';
}