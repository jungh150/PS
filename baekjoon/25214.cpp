#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int mint = 1e9 + 1;
    vector<int> minl(n);
    for (int i = 0; i < n; i++) {
        mint = min(mint, a[i]);
        minl[i] = mint;
    }
    
    int maxt = 0;
    for (int i = 0; i < n; i++) {
        maxt = max(maxt, a[i] - minl[i]);
        cout << maxt << ' ';
    }
    
    cout << '\n';
}