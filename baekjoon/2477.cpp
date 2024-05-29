#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int k;
    cin >> k;
    int ans = 0;
    
    vector<vector<int>> data = vector<vector<int>>(6, vector<int>(2)); 
    vector<int> cnt = vector<int>(5, 0);

    for (int i = 0; i < 6; i++) {
        cin >> data[i][0] >> data[i][1];
        cnt[data[i][0]]++;
    }

    int cur = 0;
    int nxt = 0;

    while (true) {
        nxt = (cur + 1) % 6;
        if (cnt[data[cur][0]] == 1 && cnt[data[nxt][0]] == 1) {
            ans += data[cur][1] * data[nxt][1];
            cur = (nxt + 2) % 6;
            nxt = (cur + 1) % 6;
            ans -= data[cur][1] * data[nxt][1];
            break;
        }
        cur++;
    }

    cout << ans * k << '\n';
}