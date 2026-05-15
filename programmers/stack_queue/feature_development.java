import java.util.*;

class Solution {
    public int[] solution(int[] progresses, int[] speeds) {
        ArrayList<Integer> res = new ArrayList<>();
        
        int n = progresses.length;
        ArrayList<Integer> time = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            time.add((100 - progresses[i] + speeds[i] - 1) / speeds[i]);
        }
        
        int cur = 0;
        int cnt = 0;
        for (int x: time) {
            if (x > cur) {
                if (cnt > 0) res.add(cnt);
                cur = x;
                cnt = 1;
            } else {
                cnt++;
            }
        }
        if (cnt > 0) res.add(cnt);
        
        int sz = res.size();
        int[] answer = new int[sz];
        for (int i = 0; i < sz; i++) answer[i] = res.get(i);
        
        return answer;
    }
}