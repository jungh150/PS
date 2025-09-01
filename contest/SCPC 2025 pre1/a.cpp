#include <iostream>
#include <vector>
using namespace std;
    
int Answer;

int main() {
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

        vector<int> cnt(3, 0);
        
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        for (int i = 0; i < n; i++) {
            if (a[i] == 500) {
                cnt[0]++;
                Answer++;
            } else if (a[i] == 1000) {
                if (cnt[0] < 1) break;
                cnt[0]--;
                cnt[1]++;
                Answer++;
            } else if (a[i] == 5000) {
                if (cnt[1] >= 4 && cnt[0] >= 1) {
                    cnt[1] -= 4;
                    cnt[0]--;
                } else if (cnt[1] >= 3 && cnt[0] >= 3) {
                    cnt[1] -= 3;
                    cnt[0] -= 3;
                } else if (cnt[1] >= 2 && cnt[0] >= 5) {
                    cnt[1] -= 2;
                    cnt[0] -= 5;
                } else if (cnt[1] >= 1 && cnt[0] >= 7) {
                    cnt[1] -= 1;
                    cnt[0] -= 7;
                } else if (cnt[0] >= 9) {
                    cnt[0] -= 9;
                } else {
                    break;
                }
                cnt[2]++;
                Answer++;
            }
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

    return 0;
}