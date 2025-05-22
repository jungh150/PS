#include <iostream>
#include <queue>
using namespace std;

int a[] = {3, 2, 1, 2, 3, 3, 3, 3, 1, 1, 3, 1, 3, 3, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    string s;
    cin >> s;
    
    queue<int> q;
    for (char c: s) q.push(a[c - 'A']);
    
    while (q.size() > 1) {
        int qs = q.size();
        int hqs = qs / 2;
        
        for (int i = 0; i < hqs; i++) {
            int x1 = q.front();
            q.pop();
            int x2 = q.front();
            q.pop();
            q.push(x1 + x2);
        }
        
        if (qs % 2 == 1) {
            int x = q.front();
            q.pop();
            q.push(x);
        }
    }
    
    int ans = q.front();
    if (ans % 2 == 1) cout << "I'm a winner!\n";
    else cout << "You're the winner?\n";
}