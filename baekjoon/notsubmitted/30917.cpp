#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int resp;
    for (int a = 1; a <= 9; a++){
        cout << "? A " << a << endl;
        cin >> resp;

        if (resp == 1){
            for (int b = 1; b <= 9; b++){
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