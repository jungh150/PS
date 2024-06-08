#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string cow[] = {"Bessie", "Elsie", "Daisy", "Gertie", "Annabelle", "Maggie", "Henrietta"};
    vector<int> c(7, 0);

    for (int i = 0; i < n; i++) {
        string str;
        int amt;
        cin >> str >> amt;
        for (int i = 0; i < 7; i++) {
            if (str == cow[i]) {
                c[i] += amt;
                break;
            }
        }
    }

    int minf = 100000;
    for (int i = 0; i < 7; i++) {
        if (c[i] < minf) {
            minf = c[i];
        }
    }

    int mins = 100000;
    for (int i = 0; i < 7; i++) {
        if (c[i] > minf) {
            if (c[i] < mins) {
                mins = c[i];
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < 7; i++) {
        if (c[i] == mins) {
            cnt++;
        }
    }

    if (cnt == 1) {
        for (int i = 0; i < 7; i++) {
            if (c[i] == mins) {
                cout << cow[i] << '\n';
                break;
            }
        }
    } else {
        cout << "Tie\n";
    }
}