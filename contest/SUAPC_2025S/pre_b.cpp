#include <iostream>
#include <vector>
using namespace std;

void solve() {
    vector<string> minim(3);
    for (int i = 0; i < 3; i++) cin >> minim[i];
    if (minim[1][2] == 'G') {
        cout << "? R\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "? L\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "!\n";
        cout << flush;
        return;
    } else if (minim[1][0] == 'G') {
        cout << "? L\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "? R\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "!\n";
        cout << flush;
        return;
    } else if (minim[0][1] == 'G') {
        cout << "? U\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "? D\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "!\n";
        cout << flush;
        return;
    } else if (minim[2][1] == 'G') {
        cout << "? D\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "? U\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        cout << "!\n";
        cout << flush;
        return;
    }

    int n = 1;
    while (true) {
        cout << "? R\n";
        cout << flush;
        for (int i = 0; i < 3; i++) cin >> minim[i];
        if (minim[1][1] == 'R') break;

        n++;
        if (minim[1][2] == 'G') {
            cout << "? R\n";
            cout << flush;
            for (int i = 0; i < 3; i++) cin >> minim[i];

            for (int i = 0; i < n; i++) {
                cout << "? L\n";
                cout << flush;
                for (int i = 0; i < 3; i++) cin >> minim[i];
            }
            cout << "!\n";
            cout << flush;
            return;
        }
    }
    // cout << "n = " << n << '\n';

    int curi = 0;
    int curj = 0;
    int gi = -1;
    int gj = -1;
    bool found = false;

    // 9칸 중 G가 있는지 체크
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (minim[i][j] == 'G') {
                gi = curi + i - 1;
                gj = curj + j - 1;
                found = true;
            }
        }
    }

    for (int x = 0; x < n; x++) {
        if (found) break;
        // 오른쪽으로 쭉 이동
        for (int y = 0; y < n; y++) {
            if (found) break;
            cout << "? R\n";
            cout << flush;
            curj++;
            if (curj >= n) curj -= n;
            for (int i = 0; i < 3; i++) cin >> minim[i];
            
            // 9칸 중 G가 있는지 체크
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (minim[i][j] == 'G') {
                        gi = curi + i - 1;
                        gj = curj + j - 1;
                        found = true;
                    }
                }
            }
            if (found) break;
        }
        if (found) break;

        // 아래로 두번 이동
        for (int y = 0; y < 3; y++) {
            if (found) break;
            cout << "? D\n";
            cout << flush;
            curi++;
            if (curi >= n) curi -= n;
            for (int i = 0; i < 3; i++) cin >> minim[i];

            // 9칸 중 G가 있는지 체크
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (minim[i][j] == 'G') {
                        gi = curi + i - 1;
                        gj = curj + j - 1;
                        found = true;
                    }
                }
            }
            if (found) break;
        }
        if (found) break;
    }
    // cout << "gi = " << gi << '\n';
    // cout << "gj = " << gj << '\n';

    // 국렬 구출
    if (curi < gi) {
        cout << "? D\n";
        cout << flush;
        curi++;
        if (curi >= n) curi -= n;
        for (int i = 0; i < 3; i++) cin >> minim[i];

        if (curj < gj) {
            cout << "? R\n";
            cout << flush;
            curj++;
            if (curj >= n) curj -= n;
            for (int i = 0; i < 3; i++) cin >> minim[i];
        } else if (curj > gj) {
            cout << "? L\n";
            cout << flush;
            curj--;
            if (curj < 0) curj += n;
            for (int i = 0; i < 3; i++) cin >> minim[i];
        }
    } else if (curi > gi) {
        cout << "? U\n";
        cout << flush;
        curi--;
        if (curi < 0) curi += n;
        for (int i = 0; i < 3; i++) cin >> minim[i];

        if (curj < gj) {
            cout << "? R\n";
            cout << flush;
            curj++;
            if (curj >= n) curj -= n;
            for (int i = 0; i < 3; i++) cin >> minim[i];
        } else if (curj > gj) {
            cout << "? L\n";
            cout << flush;
            curj--;
            if (curj < 0) curj += n;
            for (int i = 0; i < 3; i++) cin >> minim[i];
        }
    }
    // cout << "curi = " << curi << '\n';
    // cout << "curj = " << curj << '\n';

    while (curi != 0) {
        cout << "? U\n";
        cout << flush;
        curi--;
        if (curi < 0) curi += n;
        for (int i = 0; i < 3; i++) cin >> minim[i];
    }

    while (curj != 0) {
        cout << "? L\n";
        cout << flush;
        curj--;
        if (curj < 0) curj += n;
        for (int i = 0; i < 3; i++) cin >> minim[i];
    }

    cout << "!\n";
    cout << flush;
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