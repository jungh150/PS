#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int n, k;
vector<int> card;
vector<bool> chk;
set<int> ans;

void dfs(int cnt, string num) {
    if (cnt == k) {
        ans.insert(stoi(num));
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!chk[i]) {
            chk[i] = true;
            dfs(cnt + 1, num + to_string(card[i]));
            chk[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    card = vector<int>(n);
    chk = vector<bool>(n, false);
    for (int i = 0; i < n; i++) cin >> card[i];

    dfs(0, "");

    cout << ans.size() << '\n';
}