#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;

bool psb(int k) {//3
    // cout << k << '\n';
    int idx = 0;
    int cnt[50001] = {0};
    for (int i = idx; i < idx + k; i++) cnt[a[i]]++;

    int idxt = 1;
    int cur = 1;
    bool isPossible = true;
    while (idxt < 50001) {
        if (cnt[idxt] == 0) {
            idxt++;
            continue;
        }
        if (cur + cnt[idxt] - 1 <= idxt) {
            cur += cnt[idxt];
            idxt++;
            if (cur > k) break;
        } else {
            isPossible = false;
            break;
        }
    }
    if (isPossible) return true;
    idx++;

    while (idx + k <= n) {
        cnt[a[idx - 1]]--;
        cnt[a[idx + k - 1]]++;
        idxt = 1;
        cur = 1;
        isPossible = true;
        while (idxt < 50001) {
            if (cnt[idxt] == 0) {
                idxt++;
                continue;
            }
            if (cur + cnt[idxt] - 1 <= idxt) {
                cur += cnt[idxt];
                idxt++;
                if (cur > k) break;
            } else {
                isPossible = false;
                break;
            }
        }
        if (isPossible) return true;
        idx++;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n; //5
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 1;
    int r = n + 1;
    while (l < r) {
        int m = (l + r) / 2;//3
        if (psb(m)) l = m + 1;
        else r = m;
    }

    cout << l - 1 << '\n';
}