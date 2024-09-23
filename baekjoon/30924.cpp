#include <iostream>
#include <random>
using namespace std;

bool chka[10001] = {0};
bool chkb[10001] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 10000);

    int resp;
    while (1) {
        int a = dist(mt);

        if (chka[a]) continue;
        else chka[a] = true;

        cout << "? A " << a << endl;
        cin >> resp;

        if (resp == 1) {
            while (1) {
                int b = dist(mt);

                if (chkb[b]) continue;
                else chkb[b] = true;

                cout << "? B " << b << endl;
                cin >> resp;

                if (resp == 1) {
                    std::cout << "! " << a + b;
                    break;
                }
            }
            break;
        }
    }
}