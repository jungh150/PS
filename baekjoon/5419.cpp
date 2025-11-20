#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ysz;

struct SegTree {
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = tree[idx] + val;
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m + 1, r, target, val);
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    long long update(int target, long long val) {
        return update(1, 0, ysz, target, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 0, ysz, wl, wr);
    }
};

// x 기준 오름차순, x 같으면 y 기준 내림차순
bool compare(pair<int,int> &a, const pair<int,int> &b) {
    if (a.first == b.first) return a.second > b.second;
    else return a.first < b.first;
}

void solve() {
    int n;
    cin >> n;
    
    vector<pair<int, int>> p(n);
    vector<int> ycom;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y};
        ycom.push_back(y);
    }

    sort(p.begin(), p.end(), compare);
    sort(ycom.begin(), ycom.end());
    ycom.erase(unique(ycom.begin(), ycom.end()), ycom.end());
    
    ysz = ycom.size() + 1;

    SegTree seg; // 지금까지 본 섬들의 y값 별 개수를 저장하는 세그먼트 트리
    seg.tree.assign(4 * ysz + 1, 0);

    long long ans = 0;
    for (auto [x, y]: p) {
        int yidx = lower_bound(ycom.begin(), ycom.end(), y) - ycom.begin();
        ans += seg.query(yidx, ysz);
        seg.update(yidx, 1);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}