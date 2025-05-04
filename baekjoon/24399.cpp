#include <iostream>
#include <vector>
using namespace std;



/*

ceil(a/b)
(a+b-1)/b


*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    int ccnt = 0;
    int ecnt = 0;

    for (char c: s) {
        if (c == 'C') ccnt++;
        else ecnt++;
    }

    cout << (ccnt + ecnt) / (ecnt + 1) << '\n';
}