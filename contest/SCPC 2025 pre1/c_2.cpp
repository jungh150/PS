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
		dp = vector<int>(n);
		
		long long tmp = 1;
		for (int i = 1; i <= n - 1; i++) {
		    Answer += (2 * tmp);
		    Answer = Answer % MOD;
		    dp[i] = tmp;
		    tmp = (tmp * 3) % MOD;
		}
		
        string ps0, ps1, ps2, ps3, s0, s1, s2, s3;

        if (s < "2") {
            ps0 = "10"; ps1 = "11"; ps2 = "12"; ps3 = "20";
        } else {
            ps0 = "20"; ps1 = "21"; ps2 = "22"; ps3 = "30";
            Answer += 3 * dp[n - 1];
            Answer = Answer % MOD;
        }

        for (int idx = n - 1; idx > 0; idx--) {
            if (idx == 1) {
                if (s >= ps2) {
                    s0 = ps2 + '0'; s1 = ps2 + '1'; s2 = ps2 + '2'; s3 = ps3 + '0';
                    Answer += 3 * dp[idx];
                    Answer = Answer % MOD;
                } else if (s >= ps1) {
                    s0 = ps1 + '0'; s1 = ps1 + '1'; s2 = ps1 + '2'; s3 = ps2 + '0';
                    Answer += 2 * dp[idx];
                    Answer = Answer % MOD;
                } else if (s >= ps0) {
                    s0 = ps0 + '0'; s1 = ps0 + '1'; s2 = ps0 + '2'; s3 = ps1 + '0';
                    Answer += dp[idx];
                    Answer = Answer % MOD;
                }
            } else {
                if (s < ps1) {
                    s0 = ps0 + '0'; s1 = ps0 + '1'; s2 = ps0 + '2'; s3 = ps1 + '0';
                } else if (s < ps2) {
                    s0 = ps1 + '0'; s1 = ps1 + '1'; s2 = ps1 + '2'; s3 = ps2 + '0';
                    Answer += dp[idx];
                    Answer = Answer % MOD;
                } else if (s < ps3) {
                    s0 = ps2 + '0'; s1 = ps2 + '1'; s2 = ps2 + '2'; s3 = ps3 + '0';
                    Answer += 2 * dp[idx];
                    Answer = Answer % MOD;
                } else {
                    Answer += 3 * dp[idx];
                    Answer = Answer % MOD;
                }
            }
            swap(ps0, s0); swap(ps1, s1); swap(ps2, s2); swap(ps3, s3); 
        }

        if (n == 1) {
            if (s == "1") Answer = 1;
            else Answer = 2;
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}