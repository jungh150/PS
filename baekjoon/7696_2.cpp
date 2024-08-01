#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 순열 생성 함수
void make_no_repeats(vector<vector<int>>& result, vector<int>& current, vector<bool>& used, int length, int depth) {
    if (depth == length) {
        if (current[0] != 0) { // 선두에 0이 오지 않도록 필터링
            result.push_back(current);
        }
        return;
    }
    
    for (int i = 0; i < 10; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(i);
            make_no_repeats(result, current, used, length, depth + 1);
            current.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while (true) {
        int count;
        cin >> count;
        if (count == 0) break;

        vector<vector<int>> result;
        for (int length = 1; length <= 10; ++length) {
            vector<int> current;
            vector<bool> used(10, false);
            make_no_repeats(result, current, used, length, 0);
            if (result.size() >= count) break;
        }

        if (count <= result.size()) {
            vector<int> result_number = result[count - 1];
            for (int num : result_number) {
                cout << num;
            }
            cout << '\n';
        }
    }
    
    return 0;
}