#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> p;
int cnt0 = 0;  // 햐얀색 색종이의 개수
int cnt1 = 0;  // 파란색 색종이의 개수

void countp(int r, int c, int s) {
    bool chk = true;
    int tmp = p[r][c];

    for (int i = r; i < r + s; i++) {
        for (int j = c; j < c + s; j++) {
            if (p[i][j] != tmp) {
                chk = false;
                break;
            }
        }
        if (!chk) {
            break;
        }
    }

    // 같은 색으로 이루어졌다면 개수 증가
    if (chk) {
        if (tmp == 0) {
            cnt0++;
        }
        else {
            cnt1++;
        }
    }
    // 그렇지 않다면 4등분하여 재귀 호출
    else {
        int news = s / 2;
        countp(r, c, news);
        countp(r, c + news, news);
        countp(r + news, c, news);
        countp(r + news, c + news, news);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    p = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }
    
    countp(0, 0, n);

    cout << cnt0 << '\n' << cnt1 << '\n';
}