#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> s;
vector<pair<int, int>> emp;
int n;
bool fin = false;

bool chk(int idxi, int idxj, int num) {
    for (int i = 0; i < 9; i++) {
        if (i != idxi && s[i][idxj] == num) return false;
    }

    for (int j = 0; j < 9; j++) {
        if (j != idxj && s[idxi][j] == num) return false;
    }

    int blki = (idxi / 3) * 3;
    int blkj = (idxj / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((blki + i != idxi || blkj + j != idxj) && s[blki + i][blkj + j] == num) return false;
        }
    }

    return true;
}

void dfs(int idx) {
    if (idx == n) {
        fin = true;
        return;
    }
    for (int x = 1; x < 10; x++) {
        if (chk(emp[idx].first, emp[idx].second, x)) {
            s[emp[idx].first][emp[idx].second] = x;
            dfs(idx + 1);
            if (fin) return;
            s[emp[idx].first][emp[idx].second] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    s = vector<vector<int>>(9, vector<int>(9));
    emp = vector<pair<int, int>>();

    for (int i = 0; i < 9; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < 9; j++) {
            s[i][j] = str[j] - '0';
            if (s[i][j] == 0) emp.emplace_back(i, j);
        }
    }

    n = emp.size();
    dfs(0);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << s[i][j];
        }
        cout << '\n';
    }
}