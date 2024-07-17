#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int org[26][2] = {{2, 1}, {2, 2}, {2, 3}, {3, 1}, {3, 2}, {3, 3}, {4, 1}, {4, 2}, {4, 3}, {5, 1}, {5, 2}, {5, 3}, {6, 1}, {6, 2}, {6, 3}, 
                      {7, 1}, {7, 2}, {7, 3}, {7, 4}, {8, 1}, {8, 2}, {8, 3}, {9, 1}, {9, 2}, {9, 3}, {9, 4}};

    char k[10];
    k[0] = '#';
    for (int i = 1; i < 10; i++) {
        int tmp;
        cin >> tmp;
        k[tmp] = i + '1' - 1;
    }

    string str;
    cin >> str;

    vector<int> ans;
    int pre = 0;
    for (char c: str) {
        int tmp = org[c -'a'][0];
        int rep = org[c -'a'][1];
        if (tmp == pre) ans.push_back(0);
        for (int i = 0; i < rep; i++) ans.push_back(tmp);
        pre = tmp;
    }

    for (int x: ans) cout << k[x];
    cout << '\n';
}