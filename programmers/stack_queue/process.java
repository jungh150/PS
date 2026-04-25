import java.util.*;

class Solution {
    public int solution(int[] priorities, int location) {
        int answer = 1;
        
        Queue<int[]> q = new LinkedList<>();
        int n = priorities.length;
        for (int i = 0; i < n; i++) {
            q.offer(new int[]{priorities[i], i});
        }

        while (true) {
            int sz = q.size();
            int maxp = 0;
            for (int i = 0; i < sz; i++) {
                int[] tmp = q.poll();
                maxp = Math.max(maxp, tmp[0]);
                q.offer(tmp);
            }
            
            int[] cur = q.poll();
            if (cur[0] == maxp) {
                if (cur[1] == location) break;
                answer++;
            } else {
                q.offer(cur);
            }
        }
        
        return answer;
    }
}