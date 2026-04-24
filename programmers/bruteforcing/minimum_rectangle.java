class Solution {
    public int solution(int[][] sizes) {
        int sz = sizes.length;
        for (int i = 0; i < sz; i++) {
            if (sizes[i][0] < sizes[i][1]) {
                int tmp = sizes[i][1];
                sizes[i][1] = sizes[i][0];
                sizes[i][0] = tmp;
            }
        }
        
        int maxw = 0;
        for (int i = 0; i < sz; i++) {
            maxw = Math.max(maxw, sizes[i][0]);
        }
        
        int maxh = 0;
        for (int i = 0; i < sz; i++) {
            maxh = Math.max(maxh, sizes[i][1]);
        }
        
        int answer = maxw * maxh;
        
        return answer;
    }
}