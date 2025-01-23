#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAX = 21;

vector<vector<int>> win;
int vst[MAX];
set<int> cycle;
vector<int> dfsStack;

void dfs(int cur, int dep) {
    vst[cur] = dep;
    dfsStack.push_back(cur);
    
    for (int nxt: win[cur]) {
        if (vst[nxt] > 0) {
            if (vst[nxt] < dep) {
                for (int i = dfsStack.size() - 1; i >= 0; i--) {
                    cycle.insert(dfsStack[i]);
                    if (dfsStack[i] == nxt) break;
                }
            }
        } else {
            dfs(nxt, dep + 1);
        }
    }

    dfsStack.pop_back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    win = vector<vector<int>>(n + 1);

    while (k--) {
        int a, b, sa, sb;
        cin >> a >> b >> sa >> sb;

        if (sa > sb) win[a].push_back(b);
        else win[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (vst[i] == 0) {
            dfs(i, 1);
        }
    }

    cout << cycle.size() << "\n";
}