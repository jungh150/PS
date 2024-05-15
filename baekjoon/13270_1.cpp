#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> minD(n + 1, 0);
    vector<int> maxD(n + 1, 0);

    minD[1] = maxD[1] = 0;
    minD[2] = maxD[2] = 1;

    if (n >= 3)
        minD[3] = maxD[3] = 2;
    
    int x1 = 2;
    int x2 = 3;
    while ((x1 + x2) <= n) {
        minD[x1 + x2] = maxD[x1 + x2] = minD[x2] + minD[x1];
        int tmp = x2;
        x2 = x1 + x2;
        x1 = tmp;
    }

    for (int i = 4; i < n + 1; i++) {
        minD[i] = minD[2] + minD[i - 2];
        maxD[i] = maxD[2] + maxD[i - 2];
        for (int j = 3; j < i - 1; j++) {
            minD[i] = min(minD[i], minD[j] + minD[i - j]);
            maxD[i] = max(maxD[i], maxD[j] + maxD[i - j]);
        }
    }

    cout << minD[n] << ' ' << maxD[n] << '\n';
}