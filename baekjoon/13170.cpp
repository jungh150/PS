#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    double p, w;
    cin >> n >> k >> p >> w;

    cout << ceil(p / w) << '\n';
}