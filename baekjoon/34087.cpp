#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MAXVAL;
int n, m, k;
vector<long long> a; // (i - 1) -> i 얻는 에너지
vector<long long> ps; // 얻는 에너지 누적합
vector<long long> b; // b[i] = ps[i] - k * i
vector<long long> comp; // b 배열에 대해 좌표 압축한 결과

struct SegTree {
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
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
        return update(1, 0, MAXVAL, target, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 0, MAXVAL, wl, wr);
    }
};

// cnt(x) = x를 초과하는 w의 개수
// w = b[j] - b[i];
long long cnt(long long x) {
    SegTree seg;
    seg.tree.assign(4 * MAXVAL + 1, 0);

    long long ans = 0;
    for (int i = 0; i < n + 1; i++) { // 왼->오 순회 (i < j 조건을 만족시키기 위해서)
        long long target = b[i] - x;
        int idx = lower_bound(comp.begin(), comp.end(), target) - comp.begin();
        ans += seg.query(0, idx - 1); // target 보다 작은 값들의 개수를 구해야 하므로
        int pos = lower_bound(comp.begin(), comp.end(), b[i]) - comp.begin();
        seg.update(pos, seg.query(pos, pos) + 1); // 현재 B[i] 업데이트
    }

    return ans;
}

// sumx(x) = {x를 초과하는 w의 개수 = (cnt(x)), x를 초과하는 w의 합}
// w = b[j] - b[i];
pair<long long, long long> sumx(long long x) {
    SegTree segCnt;
    SegTree segSum;

    segCnt.tree.assign(4 * MAXVAL + 1, 0);
    segSum.tree.assign(4 * MAXVAL + 1, 0);

    pair<long long, long long> ans = {0, 0};
    for (int i = 0; i < n + 1; i++) { // 왼->오 순회 (i < j 조건을 만족시키기 위해서)
        long long target = b[i] - x;

        int idx = lower_bound(comp.begin(), comp.end(), target) - comp.begin();
        long long cntt = segCnt.query(0, idx - 1); // target 보다 작은 값들의 개수를 구해야 하므로
        long long sumt = segSum.query(0, idx - 1); // target 보다 작은 값들의 합을 구해야 하므로
        ans.first += cntt;
        ans.second += (b[i] * cntt - sumt);

        int pos = lower_bound(comp.begin(), comp.end(), b[i]) - comp.begin();
        // 현재 B[i] 업데이트
        segCnt.update(pos, segCnt.query(pos, pos) + 1);
        segSum.update(pos, segSum.query(pos, pos) + b[i]);
    }

    return ans;
}

void solve() {
    cin >> n >> m >> k;
    a = vector<long long>(n + 1, 0);
    ps = vector<long long>(n + 1, 0);
    b = vector<long long>(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        ps[i] = ps[i - 1] + a[i];
        b[i] = ps[i] - k * i;
    }

    // b 배열에 대해서 좌표 압축
    comp = b;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    MAXVAL = comp.size();

    // 이분탐색 -> w_{m'} 찾기
    // cnt(x) < M 를 처음으로 만족하는 값 중 가장 작은 값 => w_{m'}
    // m' = M 이하의 w_{m'}이 양수인 최대 정수
    long long minb = *min_element(b.begin(), b.end());
    long long maxb = *max_element(b.begin(), b.end());
    long long minw = minb - maxb;
    long long maxw = maxb - minb;

    long long l = minw - 1;
    long long r = maxw + 1;

    while (l + 1 < r) {
        long long mid = (l + r) / 2;
        if (cnt(mid) >= m) l = mid;
        else r = mid;
    }

    // w_{m'} = r
    if (r < 0) r = 0;

    // 답 구하기
    // 답 = (M - w_{m'}을 초과하는 w의 개수) * w_{m'} + (w_{m'}을 초과하는 w의 합) + 모든 a의 합
    auto [cntt, sumt] = sumx(r);
    long long ans = (m - cntt) * r + sumt + ps[n];
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}