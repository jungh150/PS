#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        if (x == n) cnt++;
    }

    cout << cnt << '\n';
}