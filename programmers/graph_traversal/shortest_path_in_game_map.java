import java.util.*;

class Solution {
    public int solution(int[][] maps) {
        int answer = 0;
        
        int n = maps.length;
        int m = maps[0].length;
        
        int[] dx = {1, -1, 0, 0};
        int[] dy = {0, 0, 1, -1};
        
        int[][] vst = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                vst[i][j] = -1;
            }
        }
        
        Queue<int[]> q = new LinkedList<>();
        vst[0][0] = 1;
        q.offer(new int[]{0, 0});
        while (q.size() > 0) {
            int[] cur = q.poll();
            for (int k = 0; k < 4; k++) {
                int nxti = cur[0] + dx[k];
                int nxtj = cur[1] + dy[k];
                if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && maps[nxti][nxtj] == 1 && vst[nxti][nxtj] == -1) {
                    vst[nxti][nxtj] = vst[cur[0]][cur[1]] + 1;
                    q.offer(new int[]{nxti, nxtj});
                }
            }
        }
        
        answer = vst[n - 1][m - 1];
        
        return answer;
    }
}