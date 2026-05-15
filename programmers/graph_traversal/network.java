import java.util.*;

class Solution {
    public int solution(int n, int[][] computers) {
        int answer = 0;
        
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<Integer>());
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (computers[i][j] == 1) adj.get(i).add(j);
            }
        }
        
        boolean[] vst = new boolean[n];
        for (int i = 0; i < n; i++) vst[i] = false;
        Queue<Integer> q = new LinkedList<>();
        
        for (int i = 0; i < n; i++) {
            if (!vst[i]) {
                answer++;
                vst[i] = true;
                q.offer(i);
                while (q.size() > 0) {
                    int cur = q.poll();
                    for (int nxt: adj.get(cur)) {
                        if (!vst[nxt]) {
                            vst[nxt] = true;
                            q.offer(nxt);
                        }
                    }
                }
            }
        }
        
        return answer;
    }
}