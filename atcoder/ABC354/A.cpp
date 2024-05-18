#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int h;
    cin >> h;

    int curh = 0;
    int day = 0;
    int growth = 1;
    while (curh <= h) {
        curh += growth;
        day++;
        growth *= 2;
    }

    cout << day << '\n';
}