#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    vector<int> loc = vector<int>(n);
    vector<int> avl = vector<int>(n - 1);

    for (int i = 0; i < n; i++) {
        cin >> loc[i];
    }

    for (int i = 0; i < n - 1; i++) {
        cin >> avl[i];
    }

    if (n == 1) {
        cout << "권병장님, 중대장님이 찾으십니다\n";
        return 0;
    }

    int nxt = loc[n - 1];
    
    for (int i = n - 2; i > 0; i--) {
        if (loc[i] + avl[i] >= nxt) {
            nxt = loc[i];
        }
    }

    if (loc[0] + avl[0] >= nxt) {
        cout << "권병장님, 중대장님이 찾으십니다\n";
    } else {
        cout << "엄마 나 전역 늦어질 것 같아\n";
    }
}