#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    string nums = "";
    int ans = 0;
    bool isminus = false;
    for (char c: s) {
        if (c >= '0' && c <= '9') {
            nums += c;
        } else if (c == '+') {
            nums = "";
            isminus = false;
        } else if (c == '-') {
            nums = "";
            isminus = true;
        } else if (c == 'x') {
            if (!nums.empty()) {
                if (!isminus) ans += stoi(nums);
                else ans -= stoi(nums);
            } else {
                if (!isminus) ans++;
                else ans--;
            }
        }
    }

    cout << ans << '\n';
}