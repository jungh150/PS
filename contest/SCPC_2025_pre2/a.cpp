/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>

using namespace std;

long long ans;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

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

		ans = 0;
		
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        for (int i = 0; i < n; i++) {
            if (a[i] >= 3) {
                if (i == n - 1) {
                    int l = i - 1;
                    while (a[i] > 2) {
                        while (l >= 0 && a[l] >= 2) l--;
                        a[l]++;
                        a[i]--;
                        ans += (i - l);
                        l--;
                    }
                } else {
                    int dif = a[i] - 2;
                    a[i] = 2;
                    a[i + 1] += dif;
                    ans += dif;
                }
            } else if (a[i] == 0) {
                int l = i - 1;
                while (l >= 0 && a[l] < 2) l--;
                int r = i + 1;
                while (r < n && a[r] < 2) r++;

                if (l < 0) {
                    a[r]--;
                    a[i]++;
                    ans += (r - i);
                } else if (r >= n) {
                    a[l]--;
                    a[i]++;
                    ans += (i - l);
                } else {
                    if ((i - l) <= (r - i)) {
                        a[l]--;
                        a[i]++;
                        ans += (i - l);
                    } else {
                        a[r]--;
                        a[i]++;
                        ans += (r - i);
                    }
                }
            }
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
        for (int i = 0; i < n; i++) cout << a[i] << ' ';
        cout << '\n';
		cout << ans << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}