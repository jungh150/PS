#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(4);
    vector<tuple<string, int, int, int, int>> query;

    // 4개의 원소가 각 행이동과 열이동으로 어느 위치로 갔는지 기록
    // 쿼리도 전부 저장해둠 (이따가 역추적 시 사용)

    a[0] = make_pair(1, 1);
    a[1] = make_pair(1, 2);
    a[2] = make_pair(2, 1);
    a[3] = make_pair(2, 2);

    while (q--) {
        string op;
        cin >> op;
        if (op == "RO") {
            for (int i = 0; i < 4; i++) {
                if (a[i].first % 2 == 1) a[i].second = a[i].second % n + 1;
            }
            query.push_back({op, 0, 0, 0, 0});
        } else if (op == "RE") {
            for (int i = 0; i < 4; i++) {
                if (a[i].first % 2 == 0) a[i].second = a[i].second % n + 1;
            }
            query.push_back({op, 0, 0, 0, 0});
        } else if (op == "CO") {
            for (int i = 0; i < 4; i++) {
                if (a[i].second % 2 == 1) a[i].first = a[i].first % n + 1;
            }
            query.push_back({op, 0, 0, 0, 0});
        } else if (op == "CE") {
            for (int i = 0; i < 4; i++) {
                if (a[i].second % 2 == 0) a[i].first = a[i].first % n + 1;
            }
            query.push_back({op, 0, 0, 0, 0});
        } else if (op == "S") {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            query.push_back({op, r1, c1, r2, c2});
        }
    }

    // 4개의 원소의 위치를 통해 다른 원소들의 위치도 결정

    vector<vector<int>> ans(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[0].first + i - 1) % n + 1][(a[0].second + j - 1) % n + 1] = n * i + 1 + j;
        }
    }

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[1].first + i - 1) % n + 1][(a[1].second + j - 1) % n + 1] = n * i + 2 + j;
        }
    }

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[2].first + i - 1) % n + 1][(a[2].second + j - 1) % n + 1] = n * i + n + 1 + j;
        }
    }

    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            ans[(a[3].first + i - 1) % n + 1][(a[3].second + j - 1) % n + 1] = n * i + n + 2 + j;
        }
    }

    // 역추적하면서 각 스왑 연산 이후에 어떻게 원소들이 이동했는지 파악해서 스왑에 저장해둠

    vector<pair<int, int>> pos(4); // <행 이동량, 열 이동량>
    vector<tuple<int, int, int, int>> swaps;
    pos[0] = {0, 0}; // OO
    pos[1] = {0, 0}; // OE
    pos[2] = {0, 0}; // EO
    pos[3] = {0, 0}; // EE

    for (int i = q - 1; i >= 0; i--) {
        auto [op, x1, y1, x2, y2] = query[i];
        if (op == "RO") {
            pos[0].second++;
            pos[1].second++;
            swap(pos[0], pos[1]); // 홀짝이 바뀌었으니 swap까지 해주기
        } else if (op == "RE") {
            pos[2].second++;
            pos[3].second++;
            swap(pos[2], pos[3]); // 홀짝이 바뀌었으니 swap까지 해주기
        } else if (op == "CO") {
            pos[0].first++;
            pos[2].first++;
            swap(pos[0], pos[2]); // 홀짝이 바뀌었으니 swap까지 해주기
        } else if (op == "CE") {
            pos[1].first++;
            pos[3].first++;
            swap(pos[1], pos[3]); // 홀짝이 바뀌었으니 swap까지 해주기
        } else if (op == "S") {
            // 현재 스왑 연산 이후에 있던 연산들 모두 반영해서 swaps에 넣어주기
            // (x1, y1) 계산
            if (x1 % 2 == 1 && y1 % 2 == 1) { // OO
                x1 = (x1 + pos[0].first - 1) % n + 1;
                y1 = (y1 + pos[0].second - 1) % n + 1;
            } else if (x1 % 2 == 1 && y1 % 2 == 0) { // OE
                x1 = (x1 + pos[1].first - 1) % n + 1;
                y1 = (y1 + pos[1].second - 1) % n + 1;
            } else if (x1 % 2 == 0 && y1 % 2 == 1) { // EO
                x1 = (x1 + pos[2].first - 1) % n + 1;
                y1 = (y1 + pos[2].second - 1) % n + 1;
            } else if (x1 % 2 == 0 && y1 % 2 == 0) { // EE
                x1 = (x1 + pos[3].first - 1) % n + 1;
                y1 = (y1 + pos[3].second - 1) % n + 1;
            }
            // (x2, y2) 계산
            if (x2 % 2 == 1 && y2 % 2 == 1) { // OO
                x2 = (x2 + pos[0].first - 1) % n + 1;
                y2 = (y2 + pos[0].second - 1) % n + 1;
            } else if (x2 % 2 == 1 && y2 % 2 == 0) { // OE
                x2 = (x2 + pos[1].first - 1) % n + 1;
                y2 = (y2 + pos[1].second - 1) % n + 1;
            } else if (x2 % 2 == 0 && y2 % 2 == 1) { // EO
                x2 = (x2 + pos[2].first - 1) % n + 1;
                y2 = (y2 + pos[2].second - 1) % n + 1;
            } else if (x2 % 2 == 0 && y2 % 2 == 0) { // EE
                x2 = (x2 + pos[3].first - 1) % n + 1;
                y2 = (y2 + pos[3].second - 1) % n + 1;
            }
            // swaps에 넣어주기
            swaps.push_back({x1, y1, x2, y2});
        }
    }

    // 아까 계산해둔대로 실제로 스왑해주기

    int sn = swaps.size();
    for (int i = sn - 1; i >= 0; i--) {
        auto [x1, y1, x2, y2] = swaps[i];
        swap(ans[x1][y1], ans[x2][y2]);
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}