#include <iostream>
#include <list>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    list<pair<long long, int>> li;
    int n;
    cin >> n;
    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        li.emplace_back(x, i);
    }

    while (li.size() > 1) {
        for (auto i = li.begin(); i != li.end(); i++) {
            long long a = i->first; // 현재 가리키고 있는 미생물의 크기
            long long newa = a; // 새로운 미생물의 크기 (흡수 후)

            // 첫 번째 미생물이 아닐 때만
            if (i != li.begin()) {
                auto prev_i = prev(i);
                // 바로 앞 미생물이 작거나 같으면
                if (prev_i->first <= a) {
                    newa += prev_i->first;
                    // i는 계속 현재 미생물을 가리키도록 유지
                    i = li.erase(prev_i);
                }
            }

            // 마지막 미생물이 아닐 때만
            if (next(i) != li.end()) {
                auto next_i = next(i);
                // 바로 뒤 미생물이 작거나 같으면
                if (next_i->first <= a) {
                    newa += next_i->first;
                    // i는 계속 현재 미생물을 가리키도록 유지
                    i = li.erase(next_i);
                    i--;
                }
            }

            // 미생물의 크기 갱신
            i->first = newa;
        }
    }

    auto ans = li.begin();
    cout << ans->first << '\n' << ans->second << '\n';
}