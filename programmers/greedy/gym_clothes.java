class Solution {
    public int solution(int n, int[] lost, int[] reserve) {
        int answer = 0;
        
        int[] cnt = new int[n + 1];
        for (int i = 1; i < n + 1; i++) cnt[i] = 0;
        
        for (int x: lost) cnt[x]--;
        for (int x: reserve) cnt[x]++;
        
        for (int i = 1; i < n + 1; i++) {
            if (cnt[i] == -1) {
                if (i - 1 >= 1 && cnt[i - 1] == 1) {
                    cnt[i - 1]--;
                    cnt[i]++;
                    continue;
                }
                if (i + 1 < n + 1 && cnt[i + 1] == 1) {
                    cnt[i + 1]--;
                    cnt[i]++;
                    continue;
                }
            }
        }
        
        for (int i = 1; i < n + 1; i++) {
            if (cnt[i] >= 0) answer++;
        }
        
        return answer;
    }
}