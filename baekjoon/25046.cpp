#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> s(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> s[i][j];
        }
    }

    int bm; // rows seleted by minwoo
    int maxi = 1 << n;
    long long maxa = LONG_LONG_MIN;

    for (int i = 0; i < maxi; i++) {
        long long ms = 0; // minwoo's score
        for (int j = 0; j < n; j++) { // col
            bm = i;
            long long off = 0;
            long long on = 0;
            for (int k = 0; k < n; k++) { // row
                if (bm % 2 == 0) off += s[k][j];
                else on += s[k][j];
                bm = bm >> 1;
            }
            // if jongjin select this col -> jongjin's score = on
            // if jongjin does not select this col -> jongjin's score = off
            if (on > off) ms += off;
            else ms += on;
        }
        if (ms > maxa) maxa = ms;
    }

    cout << maxa << '\n';
}