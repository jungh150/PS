#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // s: 문자열
    string s;
    cin >> s;

    // n = 문자열 s의 길이 = 접미사 배열 a의 크기
    int n = s.size();
    // a: 접미사를 담는 배열
    vector<string> a;

    for (int i = 0; i < n; i++) a.push_back(s.substr(i));

    sort(a.begin(), a.end());

    for (string tmp: a) cout << tmp << '\n';
}