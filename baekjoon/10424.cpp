#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a = vector<int>(n);

    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        a[tmp - 1] = tmp - (i + 1);
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }
}