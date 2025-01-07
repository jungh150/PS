#include <iostream>
using namespace std;

bool prime[100001];
int arr[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b;
    cin >> a >> b;
    int ans = 0;

    fill(prime, prime + 100001, true);
    prime[0] = prime[1] = false;

    for (int i = 2; i < 100001; i++) {
        if (prime[i]) {
            for (int j = i * 2; j <= b; j += i) {
                prime[j] = false;
                int cur = j;
                while (cur % i == 0) {
                    cur /= i;
                    arr[j]++;
                }
            }
        }
    }

    for (int i = a; i <= b; i++) {
        if (prime[arr[i]]) ans++;
    }

    cout << ans << '\n';
}