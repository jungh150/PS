#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> in;
vector<int> post;

void pre(int postl, int postr, int inl, int inr) {
    if (postl > postr || inl > inr) return;

    int root = post[postr];
    int inrootidx;
    for (int i = inl; i <= inr; i++) {
        if (in[i] == root) {
            inrootidx = i;
            break;
        }
    }
    int lsize = inrootidx - inl;
    int rsize = inr - inrootidx;

    cout << root << ' ';
    pre(postl, postl + lsize - 1, inl, inrootidx - 1);
    pre(postr - rsize, postr - 1, inrootidx + 1, inr);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    in = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> in[i];

    post = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> post[i];

    pre(0, n - 1, 0, n - 1);
    cout << '\n';
}