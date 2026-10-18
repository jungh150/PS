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
int MOD = 1000000007;
string s;
int n;
vector<long long> dp;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = 0;
		
		cin >> s;
		
		n = s.size();
		dp = vector<long long>(n + 1);
        dp[0] = 0;
		
		long long tmp = 1;
		for (int i = 1; i < n; i++) {
		    Answer += (2 * tmp);
		    Answer = Answer % MOD;
		    dp[i] = tmp;
		    tmp = (tmp * 3) % MOD;
		}
        dp[n] = tmp;

        for (int i = 0; i < n; i++) {
            if (i == 0) {
                if (s[0] == '1') {
                
                } else if (s[0] == '2') {
                    Answer += dp[n];
                    Answer = Answer % MOD;
                } else {
                    Answer += 2 * dp[n];
                    Answer = Answer % MOD;
                    break;
                }
            } else {
                if (s[i] == '0') {
                    if (i == n - 1) Answer += dp[n - i];
                } else if (s[i] == '1') {
                    if (i == n - 1) Answer += 2 * dp[n - i];
                    else Answer += dp[n - i];
                    Answer = Answer % MOD;
                } else if (s[i] == '2') {
                    if (i == n - 1) Answer += 3 * dp[n - i];
                    else Answer += 2 * dp[n - i];
                    Answer = Answer % MOD;
                } else {
                    Answer += 3 * dp[n - i];
                    Answer = Answer % MOD;
                    break;
                }
            }
        }

        if (s == "1") Answer = 1;
        if (s == "2") Answer = 2;
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}