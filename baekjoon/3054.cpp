#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char frame[] = {'*', '#', '#'};

    string str;
    cin >> str;

    int n = str.size();
    int i;

    // line 1
    for (i = 1; i < n + 1; i++) {
        cout << ".." << frame[i % 3] << ".";
    }
    cout << ".\n";

    // line 2
    for (i = 1; i < n + 1; i++) {
        cout << "." << frame[i % 3] << "." << frame[i % 3];
    }
    cout << ".\n";

    // line 3
    for (i = 1; i < n + 1; i++) {
        if (i != 1 && (i - 1) % 3 == 0) cout << frame[(i - 1) % 3];
        else cout << frame[i % 3];
        cout << "." << str[i - 1] << ".";
    }
    cout << frame[(i - 1) % 3] << "\n";

    // line 4
    for (i = 1; i < n + 1; i++) {
        cout << "." << frame[i % 3] << "." << frame[i % 3];
    }
    cout << ".\n";

    // line 5
    for (i = 1; i < n + 1; i++) {
        cout << ".." << frame[i % 3] << ".";
    }
    cout << ".\n";
}