#include <iostream>
using namespace std;

void solve(){
    long long n;
    cin >> n;

    if (n % 10 == 0) cout << 1 << '\n';
    else cout << 0 << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}