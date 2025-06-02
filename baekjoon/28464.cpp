#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int hn = n / 2;
    
    int tmp = 0;
    for (int i = 0; i < hn; i++) tmp += a[i];
    cout << tmp << ' ';

    tmp = 0;
    for (int i = hn; i < n; i++) tmp += a[i];
    cout << tmp << '\n';
}