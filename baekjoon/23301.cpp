#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, t;
    cin >> n >> t;

    vector<int> avl(1000, 0);

    while (n--) {
        int k;
        cin >> k;

        while (k--) {
            int s, e;
            cin >> s >> e;
            for (int i = s; i < e; i++) avl[i]++;
        }
    }

    int si = 0;
    int ei = t;
    int tmp = 0;
    for (int i = si; i < ei; i++) tmp += avl[i];

    int maxt = tmp;
    int maxi = 0;
    while (ei < 1000) {
        tmp -= avl[si];
        si++;
        tmp += avl[ei];
        ei++;
        if (tmp > maxt) {
            maxt = tmp;
            maxi = si;
        }
    }

    cout << maxi << ' ' << maxi + t << '\n';
}