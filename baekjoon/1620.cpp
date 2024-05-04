#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    map<int, string> num;
    map<string, int> name;
    string input;

    for (int i = 1; i <= n; i++) {
        cin >> input;
        num.insert({i, input});
        name.insert({input, i});
    }

    for (int i = 0; i < m; i++) {
        cin >> input;
        if (input[0] >= 48 && input[0] < 58) {
            cout << num[stoi(input)] << '\n';
        }
        else {
            cout << name[input] << '\n';
        }
    }
}