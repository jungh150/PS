#include <iostream>
#include <vector>
using namespace std;

const int M = 1000000007;
vector<int> fib;

int findPisanoPeriod(int m) {
    fib.push_back(0);
    fib.push_back(1);
    int idx = 2;
    while (1) {
        fib.push_back((fib[idx - 1] + fib[idx - 2]) % m);
        if (fib[idx] == 1 && fib[idx - 1] == 0) {
            break;
        }
        idx++;
    }
    return idx - 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    int pi = findPisanoPeriod(M);
    cout << fib[n % pi] << '\n';
}