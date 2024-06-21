#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    int uc = 0;
    int dp = 0;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'U' || str[i] == 'C') uc++;
        else if (str[i] == 'D' || str[i] == 'P') dp++;
    }

    bool isC = true;

    // U ?
    if (uc > ((dp + 1) / 2)) {
        cout << "U";
        isC = false;
    }

    // D, P ?
    if (dp > 0) {
        cout << "DP";
        isC = false;
    }

    // C ?
    if (isC) cout << "C\n";
}