#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> pro(n);
    for (int i = 0; i < n; i++) {
        char c;
        int num;
        cin >> c >> num;
        if (c == 'B') num += 50000;
        else if (c == 'S') num += 40000;
        else if (c == 'G') num += 30000;
        else if (c == 'P') num += 20000;
        else if (c == 'D') num += 10000;
        pro[i] = num;
    }

    bool isok = true;
    int idx1 = -1;
    int idx2 = -1;
    for (int i = 0; i < n - 1; i++) {
        if (pro[i] < pro[i + 1]) {
            isok = false;
            if (idx1 == -1) idx1 = i;
            else idx2 = i + 1;
        }
    }
    
    if (isok) {
        cout << "OK\n";
    } else {
        if (idx2 == -1) idx2 = idx1 + 1;
        cout << "KO\n";
        // first
        int cn2 = pro[idx2] / 10000;
        if (cn2 == 5) cout << "B";
        else if (cn2 == 4) cout << "S";
        else if (cn2 == 3) cout << "G";
        else if (cn2 == 2) cout << "P";
        else if (cn2 == 1) cout << "D";
        cout << pro[idx2] % 10000 << ' ';
        // second
        int cn1 = pro[idx1] / 10000;
        if (cn1 == 5) cout << "B";
        else if (cn1 == 4) cout << "S";
        else if (cn1 == 3) cout << "G";
        else if (cn1 == 2) cout << "P";
        else if (cn1 == 1) cout << "D";
        cout << pro[idx1] % 10000 << '\n';
    }
}