#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char c;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cin >> c;
            if (c == 'w') {
                cout << "chunbae\n";
                return 0;
            } else if (c == 'b') {
                cout << "nabi\n";
                return 0;
            } else if (c == 'g') {
                cout << "yeongcheol\n";
                return 0;
            }
        }
    }
}