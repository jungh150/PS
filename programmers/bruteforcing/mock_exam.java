import java.util.*;

class Solution {
    public int[] solution(int[] answers) {
        ArrayList<Integer> res = new ArrayList<>();
        
        int n = answers.length;
        
        int[] ans1 = {1, 2, 3, 4, 5};
        int[] ans2 = {2, 1, 2, 3, 2, 4, 2, 5};
        int[] ans3 = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
        
        int cnt1 = 0;
        int cnt2 = 0;
        int cnt3 = 0;
        
        for (int i = 0; i < n; i++) {
            if (answers[i] == ans1[i % 5]) cnt1++;
            if (answers[i] == ans2[i % 8]) cnt2++;
            if (answers[i] == ans3[i % 10]) cnt3++;
        }
        
        int maxt = Math.max(Math.max(cnt1, cnt2), cnt3);
        if (cnt1 == maxt) res.add(1);
        if (cnt2 == maxt) res.add(2);
        if (cnt3 == maxt) res.add(3);
        
        int sz = res.size();
        int[] answer = new int[sz];
        for (int i = 0; i < sz; i++) answer[i] = res.get(i);
        
        return answer;
    }
}