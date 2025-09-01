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
vector<int> dp;

long long dfs(int idx, string s0, string s1, string s2, string s3, long long res) {
    if (idx == 0) return res;
    if (idx == 1) {
        if (s >= s2) {
            //cout << "type1\n";
            return dfs(idx - 1, s2 + '0', s2 + '1', s2 + '2', s3 + '0', (res + 3 * dp[idx]) % MOD);
        } else if (s >= s1) {
            //cout << "type2\n";
            return dfs(idx - 1, s1 + '0', s1 + '1', s1 + '2', s2 + '0', (res + 2 * dp[idx]) % MOD);
        } else if (s >= s0) {
            //cout << "type3\n";
            return dfs(idx - 1, s0 + '0', s0 + '1', s0 + '2', s1 + '0', (res + dp[idx]) % MOD);
        } else {
            //cout << "type4\n";
            return res % MOD;
        }
    } else {
        if (s < s1) {
            //cout << "type1\n";
            return dfs(idx - 1, s0 + '0', s0 + '1', s0 + '2', s1 + '0', res % MOD);
        } else if (s < s2) {
            //cout << "type2\n";
            return dfs(idx - 1, s1 + '0', s1 + '1', s1 + '2', s2 + '0', (res + dp[idx]) % MOD);
        } else if (s < s3) {
            //cout << "type3\n";
            return dfs(idx - 1, s2 + '0', s2 + '1', s2 + '2', s3 + '0', (res + 2 * dp[idx]) % MOD);
        } else {
            //cout << "type4\n";
            return (res + 3 * dp[idx]) % MOD;
        }
    }
}

int main(int argc, char** argv)
{
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
		dp = vector<int>(n);
		
		long long tmp = 1;
		for (int i = 1; i <= n - 1; i++) {
		    Answer += (2 * tmp);
		    Answer = Answer % MOD;
		    dp[i] = tmp;
		    tmp = (tmp * 3) % MOD;
		}
		
        if (n == 1) {
            if (s == "1") Answer = 1;
            else Answer = 2;
        } else {
		    if (s < "2") Answer += dfs(n - 1, "10", "11", "12", "20", 0);
		    else Answer += dfs(n - 1, "20", "21", "22", "30", 3 * dp[n - 1]); 
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}