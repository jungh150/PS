/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int Answer;

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

        vector<int> a(n + 1);
        vector<int> dp(n + 1);
        map<int, int> cnt;

        dp[0] = 0;
        int sqrcnt = 0;

        for (int i = 1; i < n + 1; i++) {
            cin >> a[i];
            if (cnt.find(a[i]) == cnt.end()) {
                cnt.insert({a[i], 1});
            } else {
                cnt[a[i]]++;
            }
            int idx = a[i];
            while (cnt[idx] >= idx) {
                cnt[idx] -= idx;
                idx = idx * idx;
                if (cnt.find(idx) == cnt.end()) {
                    cnt.insert({idx, 1});
                } else {
                    cnt[idx]++;
                }
                sqrcnt++;
            }
            dp[i] = sqrcnt;
            cout << dp[i] << ' ';
        }

        //int q;
        //cin >> q;
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}