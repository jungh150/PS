#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int cnt = 0;
    int maxa = 0;
    
    for (int i = 0; i < 10; i++) {
        int a, b;
        cin >> a >> b;
        cnt += (b - a);
        maxa = max(maxa, cnt);
    }
    
    cout << maxa << '\n';
}