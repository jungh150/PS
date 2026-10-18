#include <iostream>
#include <vector>
using namespace std;

struct Manacher{
    vector<long long> S;
    long long N, r = 0, p = 0;
    vector<long long> A;
    Manacher(const vector<long long>& T){
        S.clear();
        S.push_back(-1); // # 대용
        for(auto c : T){
            S.push_back(c);
            S.push_back(-1);
        }
        N = S.size();
        A.assign(N, 0);
        for (int i = 0; i < N; i++) {
            if(i <= r) A[i] = min(A[2*p-i], r-i);
            else A[i] = 0;

            while(1){
                if(i-A[i]-1 < 0 || i+A[i]+1 >= N) break;
                if(S[i-A[i]-1] != S[i+A[i]+1]) break;
                A[i]++;
            }

            if(r < i+A[i]){
                r = i+A[i];
                p = i;
            }
        }
    }

    long long countPal(){
        long long ret = 0;
        for(auto a : A) ret += (a + 1) / 2;
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // vector<vector<bool>> p(n, vector<bool>(n, false));
    // for (int i = 0; i < n; i++) p[i][i] = true;
    // for (int i = 0; i < n - 1; i++) {
    //     if (a[i] == a[i + 1]) p[i][i + 1] = true;
    // }
    // for (int i = 2; i < n; i++) {
    //     for (int j = 0; j + i < n; j++) {
    //         if (p[j + 1][j + i - 1] && a[j] == a[j + i]) p[j][j + i] = true;
    //     }
    // }

    // int cnt = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (p[i][j]) cnt++;
    //     }
    // }

    Manacher mana(a);

    cout << 1 + n * (n + 1) / 2 - mana.countPal() << '\n';
}