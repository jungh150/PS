#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;  // 트리의 정점 개수
    cin >> n;

    vector<vector<int>> g(n + 1);  // 인접 리스트
    for (int i = 0; i < n - 1; i++) {  // n-1개의 간선 입력 받기
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int q;  // 질의 개수
    cin >> q;

    while (q--) {
        int t, k;
        cin >> t >> k;

        if (t == 1) {  // 단절점 여부 판별
            if (g[k].size() > 1) cout << "yes\n";  // 연결된 정점이 2개 이상이면 단절점
            else cout << "no\n";  // 리프 노드면 단절점 아님
        } else if (t == 2) {  // 단절선 여부 판별
            cout << "yes\n";  // 모든 간선은 단절선
        }
    }
}