#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string str1, str2;
        cin >> str1 >> str2;

        string tmp1 = str1;
        string tmp2 = str2;

        sort(tmp1.begin(), tmp1.end());
        sort(tmp2.begin(), tmp2.end());

        cout << str1 << " & " << str2 << " are ";
        if (tmp1 == tmp2) cout << "anagrams.\n";
        else cout << "NOT anagrams.\n";
    }
}