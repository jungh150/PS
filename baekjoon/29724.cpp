#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int weight = 0;
    int cost = 0;

    while (n--) {
        char c;
        int w, h, l;
        cin >> c >> w >> h >> l;

        if (c == 'A') {
            int tmp = (w / 12) * (h / 12) * (l / 12);
            weight += (tmp * 500 + 1000);
            cost += tmp * 4000;
        } else if (c == 'B') {
            weight += 6000;
        }
    }

    cout << weight << '\n' << cost << '\n';
}