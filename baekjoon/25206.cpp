#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double sumt = 0;
    int cnt = 0;

    for (int i = 0; i < 20; i++) {
        string name, grade;
        double unit;
        cin >> name >> unit >> grade;
        if (grade == "A+") {
            sumt += 4.5 * unit;
            cnt += unit;
        } else if (grade == "A0") {
            sumt += 4.0 * unit;
            cnt += unit;
        } else if (grade == "B+") {
            sumt += 3.5 * unit;
            cnt += unit;
        } else if (grade == "B0") {
            sumt += 3.0 * unit;
            cnt += unit;
        } else if (grade == "C+") {
            sumt += 2.5 * unit;
            cnt += unit;
        } else if (grade == "C0") {
            sumt += 2.0 * unit;
            cnt += unit;
        } else if (grade == "D+") {
            sumt += 1.5 * unit;
            cnt += unit;
        } else if (grade == "D0") {
            sumt += 1.0 * unit;
            cnt += unit;
        } else if (grade == "F") {
            cnt += unit;
        }
    }

    cout << fixed;
    cout.precision(10);
    cout << sumt / cnt << '\n';
}