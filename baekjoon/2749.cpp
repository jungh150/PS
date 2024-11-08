#include <iostream>
using namespace std;

const int M = 1000000;
const int PI = 15 * (M / 10);
int fib[PI];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;
    
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < PI; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % M;
    }

    cout << fib[n % PI] << '\n';
}