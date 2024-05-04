#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, b;
    cin >> n >> m >> b;

    vector<vector<int>> data(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> data[i][j];
        }
    }

    int mint = 1e9, minh, tmp, lack, over;

    for (int h = 0; h <= 256; h++) {
        lack = over = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (data[i][j] > h)
                    over += data[i][j] - h;
                else
                    lack += h - data[i][j];
            }
        }
        if (lack <= over + b) {
            tmp = over * 2 + lack;
            if (tmp <= mint) {
                mint = tmp;
                minh = h;
            }
        }
    }

    cout << mint << ' ' << minh << '\n';
}