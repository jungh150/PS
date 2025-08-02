#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    while (n--) {
        string s;
        cin >> s;
        if (s.size() >= 6 && s.size() <= 9) cout << "yes\n";
        else cout << "no\n";
    }
}