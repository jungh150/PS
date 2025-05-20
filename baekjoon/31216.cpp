#include <iostream>
#include <vector>
using namespace std;

bool p[1000000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fill_n(p, 1000000, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i < 500000; i++) {
        int tmp = i + i;
        while (tmp < 1000000) {
            p[tmp] = 0;
            tmp += i;
        }
    }

    vector<int> prime;
    prime.push_back(0);
    for (int i = 1; i < 1000000; i++) {
        if (p[i]) prime.push_back(i);
    }

    int pn = prime.size();
    vector<int> ans;
    for (int x: prime) {
        if (x < pn) ans.push_back(prime[x]);
    }

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        cout << ans[n] << '\n';
    }
}