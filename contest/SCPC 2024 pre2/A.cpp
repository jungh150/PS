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
		
        int n, s, e;
        cin >> n >> s >> e;
        vector<int> a(n);
        vector<pair<int, int>> op;
        vector<long long> cost; // cost to make 1

        bool isone = false;
        pair<int, int> ptmp= {0, 0};
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x == 1) {
                if (!isone) {
                    ptmp.first = i;
                    isone = true;
                }
                a[i] = 1;
            } else if (x == 0) {
                if (isone) {
                    ptmp.second = i - 1;
                    op.push_back(ptmp);
                    isone = false;
                }
                a[i] = 0;
            }
        }
        if (isone) {
            ptmp.second = n - 1;
            op.push_back(ptmp);
        }

        int ops = op.size();
        for (int i = 0; i < ops; i++) {
            // 0
            int s0, e0;
            if (i == 0) s0 = 0;
            else s0 = op[i - 1].second + 1;
            e0 = op[i].first - 1;
            long long tmp0 = (e0 - s0 + 1) * s;
            cost.push_back(tmp0);
            cout << tmp0 << ' ';
            // 1
            long long tmp1 = (op[i].second - op[i].first + 1) * -e;
            cost.push_back(tmp1);
            cout << tmp1 << ' ';
        }
        // 0
        long long tmp00 = (n - 1 - op[ops - 1].second) * s;
        cost.push_back(tmp00);
        cout << tmp00 << '\n';

        int convertToPositive = 0;
        int convertToNegative = 0;

        int cs = cost.size();
        for (int i = 0; i < cs; ++i) {
            if (cost[i] < 0) {
                convertToPositive += abs(cost[i]);
            } else {
                convertToNegative += cost[i];
            }
        }

        int minCost = min(convertToPositive, convertToNegative);
        cout << "minCost: " << minCost << endl;

		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}