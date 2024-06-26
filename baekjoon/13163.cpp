#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    string tmp;
    getline(cin, tmp);

    while(n--) {
        string name;
        string ans = "god";
        getline(cin, name);
        
        bool isfirst = true;
        for (char c: name) {
            if (c == ' ') {
                if (isfirst) isfirst = false;
            } else {
                if (!isfirst) ans.push_back(c);
            }
        }

        cout << ans << '\n';
    }
}