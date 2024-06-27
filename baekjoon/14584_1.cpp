#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    int n;
    cin >> n;

    vector<string> dic(n);
    for (int i = 0; i < n; i++) {
        cin >> dic[i];
    }

    for (int k = 0; k < 26; k++) {
        // check if there is any dictionary word in input string
        for (int i = 0; i < n; i++) {
            int sidx = 0; // start index
            int cidx = sidx; // current index
            int idx = 0; // index of dictionary word
            while (cidx < str.size()) {
                if (dic[i][idx] == str[cidx]) {
                    idx++;
                    cidx++;
                } else {
                    idx = 0;
                    sidx++;
                    cidx = sidx;
                }
                if (idx >= dic[i].size()) {
                    cout << str << '\n';
                    return 0;
                }
            }
        }
        // shift
        for (int i = 0; i < str.size(); i++) {
            str[i] = str[i] + 1;
            if (str[i] > 'z') str[i] = 'a';
        }
    }
}