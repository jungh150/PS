#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cout << "Hello World, Judge " << i + 1 << "!\n";
    }
}