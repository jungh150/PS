#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cout << fixed;
    cout.precision(3);

    double x[4];
    double y[4];
    double xmid, ymid;

    while(1){
        cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2] >> x[3] >> y[3];
        if (cin.eof()) break;

        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (x[i] == x[j] && y[i] == y[j]) {
                    xmid = x[i];
                    ymid = y[i];
                    break;
                }
            }
        }

        double ansx = x[0] + x[1] + x[2] + x[3] - 3 * xmid;
        double ansy = y[0] + y[1] + y[2] + y[3] - 3 * ymid;
        cout << ansx << ' ' << ansy << '\n';
    }
}