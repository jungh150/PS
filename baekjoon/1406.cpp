#include <iostream>
#include <list>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    list<char> li(s.begin(), s.end());

    int n;
    cin >> n;

    // 최초의 커서 위치는 문장의 맨 뒤
    auto cur = li.end();

    while (n--) {
        char cmd;
        cin >> cmd;

        if (cmd == 'L') {
            // 커서가 맨 앞이 아니라면 한 칸 앞으로 이동
            if (cur != li.begin()) cur--;
        } else if (cmd == 'D') {
            // 커서가 맨 뒤가 아니라면 한 칸 뒤로 이동
            if (cur != li.end()) cur++;
        } else if (cmd == 'B') {
            // 커서가 맨 앞이 아니라면 바로 앞 문자 하나 삭제
            if (cur != li.begin()) li.erase(prev(cur));
        } else if (cmd == 'P') {
            // 커서 바로 앞에 문자 하나 추가
            char c;
            cin >> c;
            li.insert(cur, c);
        }
    }

    for (auto i = li.begin(); i != li.end(); i++) cout << *i;
    cout << '\n';
}