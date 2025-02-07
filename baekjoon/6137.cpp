#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    string str;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        str += c;
    }

    int s = 0;
    int e = n - 1;
    string ans = "";

    while (s <= e) {
        if (str[s] < str[e]) { // 앞쪽 문자가 더 작으면
            ans += str[s];
            s++;
        } else if (str[s] > str[e]) { // 뒤쪽 문자가 더 작으면
            ans += str[e];
            e--;
        } else { // 앞쪽 문자와 뒤쪽 문자가 동일하면
            int tmps = s + 1;
            int tmpe = e - 1;
            while (tmps < tmpe && str[tmps] == str[tmpe]) { // 같으면 계속 이동
                tmps++;
                tmpe--;
            }
            if (str[tmps] < str[tmpe]) {
                ans += str[s];
                s++;
            } else {
                ans += str[e];
                e--;
            }
        }
    }

    int ansn = ans.size();
    for (int i = 0; i < n; i++) {
        if (i != 0 && i % 80 == 0) cout << '\n'; // 80글자마다 줄바꿈
        cout << ans[i];
    }
    cout << '\n';
}