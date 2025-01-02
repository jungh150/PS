#include <iostream>
using namespace std;

int fib(int n) {
    if (n == 1 || n == 2) return 1;
    else return (fib(n - 1) + fib(n - 2));
}

int fibonacci(int n) {
    int res = 0;
    for (int i = 3; i <= n; i++) res++;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    cout << fib(n) << ' ' << fibonacci(n) << '\n';
}