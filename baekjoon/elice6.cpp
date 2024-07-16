#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> parent;
vector<int> sizes;

int find(int a) {
    if (a == parent[a]) {
        return a;
    } else {
        parent[a] = find(parent[a]);
        return parent[a];
    }
}

void unions(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[b] = a;
        sizes[a] += sizes[b];
        sizes[b] = sizes[a];
    }
    for (int i = 0; i < n; i++) {
        sizes[i] = sizes[find(i)];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    parent = vector<int>(n);
    sizes = vector<int>(n, 1);

    for (int i = 0; i < n; i++) parent[i] = i;

    int redcnt = 0;
    for (int i = 0; i < n - 1; i++) {
        int color;
        cin >> color;
        if (color == 1) { // 파란 간선 -> degree 큰 애들
            // degree 최대 2개 찾기
            int maxi1 = 0;
            int maxv1 = -1;
            for (int j = 0; j < n; j++) {
                int sizest = sizes[find(j)];
                if (sizest > maxv1) {
                    maxi1 = j;
                    maxv1 = sizest;
                }
            }
            int maxi2 = 0;
            int maxv2 = -1;
            for (int j = 0; j < n; j++) {
                if (find(j) == find(maxi1)) continue;
                int sizest = sizes[find(j)];
                if (sizest > maxv2) {
                    maxi2 = j;
                    maxv2 = sizest;
                }
            }
            unions(maxi1, maxi2);
        } else if (color == 0) { // 빨간 간선 -> degree 작은 애들
            // degree 최소 2개 찾기
            int mini1 = 0;
            int minv1 = 100;
            for (int j = 0; j < n; j++) {
                int sizest = sizes[find(j)];
                if (sizest < minv1) {
                    mini1 = j;
                    minv1 = sizest;
                }
            }
            int mini2 = 0;
            int minv2 = 100;
            for (int j = 0; j < n; j++) {
                if (find(j) == find(mini1)) continue;
                int sizest = sizes[find(j)];
                if (sizest < minv2) {
                    mini2 = j;
                    minv2 = sizest;
                }
            }
            redcnt += sizes[find(mini1)] * sizes[find(mini2)];
            unions(mini2, mini1);
        }
    }

    cout << redcnt << '\n';
}