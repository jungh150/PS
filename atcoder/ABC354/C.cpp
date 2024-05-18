#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> card;

// card의 strength 기준 정렬
bool cmp1(vector<int> &v1, vector<int> &v2) {
    return v1[1] > v2[1];
}

// card의 number 기준 정렬
bool cmp2(vector<int> &v1, vector<int> &v2) {
    return v1[0] < v2[0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    card = vector<vector<int>>(n, vector<int>(3));

    for (int i = 0; i < n; i++) {
        card[i][0] = i + 1;
        cin >> card[i][1] >> card[i][2];
    }

    sort(card.begin(), card.end(), cmp1);

    int i = 0;
    while (i < card.size()) {
        int j = i + 1;
        while (j < card.size()) {
            if (card[i][2] < card[j][2]) {
                card.erase(card.begin() + j);
            }
            j++;
        }
        i++;
    }

    sort(card.begin(), card.end(), cmp2);

    cout << card.size() << '\n';
    for (int k = 0; k < card.size(); k++) {
        cout << card[k][0] << ' ';
    }
    cout << '\n';
}