#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> itr(n);
    vector<int> rgt(n);
    for (int i = 0; i < n; i++) cin >> itr[i];
    for (int i = 0; i < n; i++) cin >> rgt[i];

    int sumit = 0;
    int sumin = 0;
    for (int i = 0; i < n; i++) {
        sumit += itr[i];
        if (rgt[i] == 0) sumin += itr[i];
    }

    cout << sumit << '\n' << sumin << '\n';
}