class Solution {
    int[][] dungeons;
    boolean[] vst;
    int answer = 0;
    int n;
    
    public int solution(int k, int[][] dungeons) {
        n = dungeons.length;
        this.dungeons = dungeons;
        vst = new boolean[n];
        
        dfs(k, 0);
        
        return answer;
    }
    
    public void dfs(int cur, int cnt) {
        answer = Math.max(answer, cnt);
        for (int i = 0; i < n; i++) {
            if (!vst[i]) {
                if (cur < dungeons[i][0]) continue;
                vst[i] = true;
                dfs(cur - dungeons[i][1], cnt + 1);
                vst[i] = false;
            }
        }
    }
}