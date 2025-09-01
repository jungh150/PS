/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int Answer;

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
		
		int n, l;
		cin >> n >> l;
		
		vector<int> a(n);
		for (int i = 0; i < n; i++) cin >> a[i];
		
        double m = (double) l / 2;
		double minv = 1000000;
		int mini = 0;
		
		for (int i = 0; i < n; i++) {
            double tmp = abs(a[i] - m);
            if (tmp < minv) {
                minv = tmp;
                mini = i;
            }
        }
		
        if (n == 1) {
            Answer = min(2 * a[0], l);
        } else if (mini == n - 1) {
            for (int i = 0; i < n; i++) Answer += 2 * a[i];
        } else {
		    for (int i = 0; i < mini; i++) Answer += 2 * a[i];
		    for (int i = mini + 1; i < n; i++) Answer += 2 * (l - a[i]);
		    Answer += l;
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}