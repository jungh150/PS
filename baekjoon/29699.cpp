#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string s = "WelcomeToSMUPC";
    cout << s[(n - 1) % 14] << '\n';
}