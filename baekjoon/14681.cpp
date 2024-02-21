#include <iostream>
using namespace std;

int main() {
    int x, y;
    int ans;
    cin >> x >> y;

    if (x > 0)
        if (y > 0)
            ans = 1;
        else
            ans = 4;
    else
        if (y > 0)
            ans = 2;
        else
            ans = 3;

    cout << ans;

    return 0;
}