#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += abs(data[i] - data[j]);
        }
    }

    cout << sum << '\n';
}