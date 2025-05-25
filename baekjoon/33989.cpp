#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> bcnt(n);
    int bcur = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            bcur++;
            bcnt[i] = bcur;
        }
    }
    int btotal = bcur;

    int mina = btotal;
    // i까지 벚꽃(B), i+1부터 단풍(D)
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        tmp += (i + 1) - bcnt[i]; // i까지의 D 개수
        tmp += btotal - bcnt[i]; // i+1부터 B개수
        mina = min(mina, tmp);
    }

    cout << mina << '\n';
}