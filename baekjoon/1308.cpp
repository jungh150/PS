#include <iostream>
using namespace std;

bool isleap(int n) {
    if (n % 4 == 0) {
        if (n % 100 == 0) {
            if (n % 400 == 0) return true;
            else return false;
        }
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int y1, y2, m1, m2, d1, d2;
    cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;

    int y3 = y2 - y1;

    if ((y3 > 1000) || (y3 == 1000 && m2 >= m1 && d2 >= d1)) {
        cout << "gg\n";
    } else {
        int ans = 0;

        if (y3 == 0) {
            while (m1 < m2) {
                if (m1 == 2 && isleap(y1)) ans += 29;
                else ans += month[m1];
                m1++;
            }
            ans += (d2 - d1);
        } else {
            while (m1 < 12) {
                if (m1 == 2 && isleap(y1)) ans += 29;
                else ans += month[m1];
                m1++;
            }

            ans += (month[m1] - d1 + 1);
            y1++;
            m1 = 1;
            d1 = 1;

            while (y1 < y2) {
                if (isleap(y1)) ans += 366;
                else ans += 365;
                y1++;
            }

            while (m1 < m2) {
                if (m1 == 2 && isleap(y1)) ans += 29;
                else ans += month[m1];
                m1++;
            }
            ans += (d2 - d1);
        }

        cout << "D-" << ans << '\n';
    }
}