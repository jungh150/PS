/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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
		Answer = -1;
		
        int n, l;
        cin >> n >> l;

        vector<int> a(n);
        vector<int> b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        for (int i = 0; i < n; i++) { // index of a
            for (int j = n - 1; j > -1; j--) { // index of b
                int diff = abs(a[i] - b[j]);
                if (diff <= l && diff > Answer) {
                    int atidx = 0; // temporary index of a
                    int btidx = 0; // temporary index of b
                    bool psb = true;
                    while (atidx < n && btidx < n) {
                        if (atidx == i) {
                            atidx++;
                            continue;
                        }
                        if (btidx == j) {
                            btidx++;
                            continue;
                        }
                        if (abs(a[atidx] - b[btidx]) > diff) {
                            psb = false;
                            break;
                        }
                        atidx++;
                        btidx++;
                    }
                    if (psb) {
                        if (diff > Answer) Answer = diff;
                        break;
                    }
                }
            }
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}