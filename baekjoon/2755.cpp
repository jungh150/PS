#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    int cnt = 0;
    double sums = 0;
    while (n--) {
        string name, grade;
        int weight;
        double score = 0;
        cin >> name >> weight >> grade;

        if (grade == "A+") score = 4.3;
        else if (grade == "A0") score = 4.0;
        else if (grade == "A-") score = 3.7;
        else if (grade == "B+") score = 3.3;
        else if (grade == "B0") score = 3.0;
        else if (grade == "B-") score = 2.7;
        else if (grade == "C+") score = 2.3;
        else if (grade == "C0") score = 2.0;
        else if (grade == "C-") score = 1.7;
        else if (grade == "D+") score = 1.3;
        else if (grade == "D0") score = 1.0;
        else if (grade == "D-") score = 0.7;
        else if (grade == "F") score = 0.0;

        sums += weight * score;
        cnt += weight;
    }

    cout << fixed;
    cout.precision(2);
    cout << (sums / cnt + 0.000001) << '\n';
}