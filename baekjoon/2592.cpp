#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> num(10);
    vector<int> cnt(100, 0);
    int sumv = 0;
    int maxcn = 0;
    int maxcv = 0;

    for (int i = 0; i < 10; i++) {
        cin >> num[i];
        sumv += num[i];
        cnt[num[i]]++;
        if (cnt[num[i]] > maxcv) {
            maxcv = cnt[num[i]];
            maxcn = num[i];
        }
    }

    cout << sumv / 10 << '\n' << maxcn << '\n';
}