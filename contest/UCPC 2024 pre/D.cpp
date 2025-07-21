#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
	public:
        int num;
		int data;
		Node* left;
		Node* right;
        
    Node(int n, int val)
    {
        num = n;
        data = val;
        left = NULL;
        right = NULL;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> nd(n + 1);
    for (int i = 1; i < n + 1; i++) {
        int a, h;
        cin >> a >> h;
        nd[h].push_back({a, i});
    }

    if (nd[1].size() != 1) {
        cout << -1 << '\n';
        return 0;
    }

    Node* nds[n + 1];
    int curh = 1;
    nds[nd[curh][0].second] = new Node(nd[curh][0].second, nd[curh][0].first);
    curh++;

    while (curh < n + 1) {
        for (int i = 0; i < nd[curh].size(); i++) {
            nds[nd[curh][i].second] = new Node(nd[curh][i].second, nd[curh][i].first);
            for (int j = 0; j < nd[curh - 1].size(); j++) {
                if (nd[curh][i].first < nd[curh - 1][j].first) { // 왼쪽 자식
                    if (nds[nd[curh - 1][j].second]->left == NULL) {
                        nds[nd[curh - 1][j].second]->left = nds[nd[curh][i].second];
                        break;
                    } else {
                        cout << -1 << '\n';
                        return 0;
                    }
                } else if (nd[curh][i].first > nd[curh - 1][j].first) { // 왼쪽 자식
                    if (nds[nd[curh - 1][j].second]->right == NULL) {
                        nds[nd[curh - 1][j].second]->right = nds[nd[curh][i].second];
                        break;
                    } else {
                        cout << -1 << '\n';
                        return 0;
                    }
                } else { // 같다면
                    cout << -1 << '\n';
                    return 0;
                }
            }
        }
        curh++;
    }

    for (int i = 1; i < n + 1; i++) {
        if (nds[i]->left == NULL) {
            cout << -1 << ' ';
        } else {
            cout << nds[i]->left->num << ' ';
        }
        if (nds[i]->right == NULL) {
            cout << -1 << '\n';
        } else {
            cout << nds[i]->right->num << '\n';
        }
    }
}