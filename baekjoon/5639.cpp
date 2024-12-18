#include <iostream>
#include <vector>
using namespace std;

vector<int> a;

void post(int s, int e) {
    if (s >= e) return;

    int idx = e;
    for (int i = s + 1; i < e; i++) {
        if (a[i] > a[s]) {
            idx = i;
            break;
        }
    }
    
    post(s + 1, idx);
    post(idx, e);
    cout << a[s] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x;
    while (cin >> x) {
        a.push_back(x);
    }

    int n = a.size();
    post(0, n);
}