#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int pn[] = {0, 11, 9, 9, 9, 8, 8, 8, 8, 8, 8};
    string p[] = {"", "A B C D E F G H J L M", "A C E F G H I L M",
                  "A C E F G H I L M", "A B C E F G H L M", "A C E F G H L M",
                  "A C E F G H L M", "A C E F G H L M", "A C E F G H L M",
                  "A C E F G H L M", "A B C F G H L M"};
    
    int n;
    cin >> n;

    cout << pn[n] << '\n' << p[n] << '\n';
}