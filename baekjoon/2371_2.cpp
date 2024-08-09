#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> lists;
set<int> uniqueSet;

int read() {
    int num;
    cin >> num;
    return num;
}

bool isDistinct(int k) {
    uniqueSet.clear();
    for (const auto& list : lists) {
        if (k < list.size()) {
            if (uniqueSet.find(list[k]) != uniqueSet.end()) return false;
            uniqueSet.insert(list[k]);
        }
    }
    return true;
}

int main() {
    int n, i;
    cin >> n;

    while (n-- > 0) {
        vector<int> list;
        while ((i = read()) != -1) list.push_back(i);
        lists.push_back(list);
    }

    int k = 0;
    while (!isDistinct(k++));
    
    cout << k << endl;
    return 0;
}
