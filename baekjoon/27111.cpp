#include <iostream>
using namespace std;

bool isin[200001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int cnt = 0;
    while (n--) {
        int a, b;
        cin >> a >> b;
        
        if (b == 1) {
            if (isin[a]) cnt++;
            else isin[a] = true;
        } else if (b == 0) {
            if (!isin[a]) cnt++;
            else isin[a] = false;
        }
    }

    for (int i = 1; i < 200001; i++) {
        if (isin[i]) cnt++;
    }

    cout << cnt << '\n';
}