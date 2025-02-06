#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int sumt = 0;
    int s = 0;
    int e = 0;
    while (e < x) {
        sumt += a[e];
        e++;
    }

    int maxt = sumt;
    int cnt = 1;

    while (e < n) {
        sumt -= a[s];
        s++;
        sumt += a[e];
        e++;

        if (sumt > maxt) {
            maxt = sumt;
            cnt = 1;
        } else if (sumt == maxt) {
            cnt++;
        }
    }

    if (maxt == 0) cout << "SAD\n";
    else cout << maxt << '\n' << cnt << '\n';
}