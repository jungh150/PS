#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, sum = 0;
    cin >> n;

    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        sum += data[i];
    }

    sort(data.begin(), data.end());

    int maxCnt = 0;
    vector<int> cnt(8001, 0);
    for (int x: data) {
        cnt[x + 4000]++;
        if (maxCnt < cnt[x + 4000]) {
            maxCnt = cnt[x + 4000];
        }
    }

    int tmp = 0, mode;
    for (int i = 0; i < 8001; i++) {
        if (cnt[i] == maxCnt) {
            tmp++;
            mode = i - 4000;
            if (tmp == 2) {
                mode = i - 4000;
                break;
            }
        }
    }

    int min = data[0];
    int max = data[n - 1];
    int mid = data[n / 2];
    int avg = round(float(sum) / n);

    cout << avg << '\n' << mid << '\n' << mode
         << '\n' << (max - min) << '\n';
}