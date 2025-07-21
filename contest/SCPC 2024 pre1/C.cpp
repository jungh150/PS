/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>

using namespace std;

long long Answer;

long long comb(int n, int r) {
    if (n < r) return 0;
    if (n == r) return 1;
    long long ans = 1;
    for (int i = n; i > n - r; i--) {
        ans *= i;
    }
    for (int i = r; i > 0; i--) {
        ans /= i;
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{

		Answer = 0;
		
        int n;
        cin >> n;

        vector<vector<int>> g(n + 1, vector<int>());
        for (int i = 0; i < n + 1; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<int> ac; // additionally connected
        for (int i = 1; i < n + 1; i++) {
            if (g[i].size() > 2) ac.push_back(i);
        }

        int cur = ac[0];
        int cnt = 0;
        int pre = 0;

        int acCnt = 0;
        for (int x: g[cur]) {
            if (x == ac[1]) {
                acCnt++;
            }
        }
        
        if (acCnt == 2) {
            Answer = comb(n - 1, 2);
        } else {
            for (int x: g[cur]) {
                if (x != ac[1]) {
                    pre = cur;
                    cur = x;
                    cnt++;
                    break;
                }
            }

            while (cur != ac[1]) {
                for (int x: g[cur]) {
                    if (x != pre) {
                        pre = cur;
                        cur = x;
                        cnt++;
                        break;
                    }
                }
            }

            Answer = comb(cnt, 2) + comb(n - cnt, 2);
        }

		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}