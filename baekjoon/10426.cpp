#include <iostream>
#include <vector>
#include <string>
using namespace std;

int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string start;
    int days, y, m, d;

    cin >> start >> days;
    y = stoi(start.substr(0, 4));
    m = stoi(start.substr(5, 2));
    d = stoi(start.substr(8, 2));
    
    bool isleap;
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) isleap = true;
    else isleap = false;

    while (true) {
        int tmp = 0;
        if (m == 2 && isleap) tmp = 29;
        else tmp = mon[m];
        if (days > tmp) {
            days -= tmp;
            m++;
            if (m > 13) {
                y++;
                m = 1;
                if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) isleap = true;
                else isleap = false;
            }
            int lastday = 0;
            if (m == 2 && isleap) lastday = 29;
            else lastday = mon[m];
            if (d > lastday) {
                m++;
                d -= lastday;
            }
            if (m > 13) {
                y++;
                m = 1;
                if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) isleap = true;
                else isleap = false;
            }
        } else {
            break;
        }
    }

    int lastday = 0;
    if (m == 2 && isleap) lastday = 29;
    else lastday = mon[m];
    while (days > 1) {
        if (d == lastday) {
            m++;
            d = 1;
            if (m > 12) {
                y++;
                m = 1;
            }
        } else {
            d++;
        }
        days--;
    }

    printf("%04d-%02d-%02d\n", y, m, d);
}