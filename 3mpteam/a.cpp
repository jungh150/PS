#include <iostream>
#include <vector>
using namespace std;

char d[] = {'N', 'E', 'S', 'W'};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int cur = 0;
    for (int i = 0; i < 10; i++) {
        int t;
        cin >> t;
        if (t == 1) cur = (cur + 1) % 4;
        else if (t == 2) cur = (cur + 2) % 4;
        else if (t == 3) cur = (cur + 3) % 4;
    }

    cout << d[cur] << '\n';
}