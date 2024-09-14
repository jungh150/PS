#include <iostream>
using namespace std;

int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string week[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x, y;
    cin >> x >> y;

    int total = y - 1;
    for (int i = 1; i < x; i++) total += days[i];

    cout << week[total % 7] << '\n';
}