#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int k, n;
    cin >> k >> n;

    vector<long long> data(k);
    for (int i = 0; i < k; i++) {
        cin >> data[i];
    }

    long long l = 0;  // 최소 길이
    long long r = data[0] + 1;  // 최대 길이

    while (l < r) {
        long long m = (l + r) / 2;
        int cnt = 0;  // 잘라서 얻을 수 있는 랜선 개수
        for (int i = 0; i < k; i++) {
            cnt += data[i] / m;
        }
        if (cnt >= n)  // 필요한 개수 이상이면 더 긴 길이도 가능할 수도 있음
            l = m + 1;
        else  // 필요한 개수보다 적으면 더 짧게 잘라야 함
            r = m;
    }

    cout << l - 1 << '\n';

    return 0;
}