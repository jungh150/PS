#include<bits/stdc++.h>
using namespace std;

int a[1000010];

int min(int n, const string& coins) {

    int tails = 0,cnt= 0;
    for (char c : coins) {
        if (c == 'T') {

            a[tails++] = cnt;

        }
        cnt++;
    }

    if (tails % 2 != 0) {
        return -1;
    }

    int CNT = 0;
    int flips = 0;

    while(1) {
    int check = 0;
    int a1 = -1,a2 =-1;
    for(int i=0; i<tails; i++) {
        if(a[i] != -1 && a1 == -1) a1 = i;
        else if(a[i] != -1 && a2 == -1) a2 = i;

        if(a1 != -1 && a2 != -1) {
            if((a[a2] - a[a1] - 1) %2 == 0) {

                flips += a[a2] - a[a1];
                a[a2] = -1;
                a[a1] = -1;
                check = 1;
                a1 = -1;
                a2 = -1;
                CNT+=2;
            }
            else {
                a1 = a2;
                a2 = -1;
            }
        }


    }
    if(CNT == tails) return flips;
    if(check == 0) return -1;

    }
    return flips;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<int> results(T);

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        string S;
        cin >> S;
        cout << min(N, S) <<"\n";
        memset(a, 0, sizeof(a));
    }


    return 0;
}