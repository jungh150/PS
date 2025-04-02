#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    set<int> ans;
    for (int a = -200; a < 201; a++) {
        for (int b = -20000; b < 20001; b++) {
            bool psb = true;
            for (int i = 1; i < n; i++) {
                if (a * arr[i - 1] + b != arr[i]) {
                    psb = false;
                    break;
                }
            }
            if (psb) {
                ans.insert(a * arr[n - 1] + b);
            }
        }
    }

    if (ans.size() == 1) cout << *ans.begin() << '\n';
    else if (ans.size() > 2) cout << "A\n";
    else cout << "B\n";
}