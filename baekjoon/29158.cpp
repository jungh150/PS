#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool comp(string a, string b){
    return a + b > b + a;
}

string addBigNumbers(string a, string b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int n = max(a.size(), b.size());
    string result = "";
    int carry = 0;

    for (int i = 0; i < n; i++) {
        int x = 0;
        if (i < a.size()) x = a[i] - '0';
        int y = 0;
        if (i < b.size()) y = b[i] - '0';

        int tmp = x + y + carry;
        result.push_back((tmp % 10) + '0');
        carry = tmp / 10;
    }

    if (carry) result.push_back(carry + '0');

    reverse(result.begin(), result.end());

    return result;
}

void solve() {
    long long n;
    cin >> n;

    if (n == 2) {
        cout << 3 << '\n';
        return;
    }

    // 성현이가 만들 수 있는 수의 최댓값 구하기
    int num = 10000000;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    int sqnum = sqrt(num);
    for (int i = 2; i <= sqnum; i++) {
        if (p[i]) {
            for (int j = i * i; j <= num; j += i) {
                p[j] = 0;
            }
        }
    }

    vector<long long> prime; // 소수 배열
    for (int i = 2; i < num; i++) {
        if (p[i]) prime.push_back(i);
    }

    long long tmp = n;
    vector<string> div;
    for (long long x: prime) {
        while (tmp % x == 0){
            tmp /= x;
            div.push_back(to_string(x));
        }
    }
    if (tmp != 1) div.push_back(to_string(tmp));

    sort(div.begin(), div.end(), comp);
    string ans1 = "";
    for(string s: div) ans1 += s;

    // 지훈이가 만들 수 있는 수의 최댓값 구하기
    tmp = 1;
    long long cnt = 0;
    while (tmp < n) {
        tmp *= 2;
        cnt++;
    }
    tmp /= 2;
    cnt--;

    string ans2 = "";
    if ((tmp / 2) * 3 < n) {
        tmp = (tmp / 2) * 3;
        ans2 += '3';
        for (int i = 0; i < cnt - 1; i++) ans2 += '2';
    } else {
        for (int i = 0; i < cnt; i++) ans2 += '2';
    }

    // 두 최댓값 더하기
    cout << addBigNumbers(ans1, ans2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}