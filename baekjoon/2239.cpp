#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> s;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    s = vector<vector<int>>(9, vector<int>(9));

    for (int i = 0; i < 9; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < 9; j++) {
            s[i][j] = str[j] - '0';
        }
    }
}