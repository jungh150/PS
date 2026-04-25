class Solution {
    public long solution(int n, int[] times) {
        long answer = 0;
        
        long l = 0;
        long r = (long) 1e18;
        while (l < r) {
            long mid = (l + r) / 2;
            long cnt = 0;
            for (int x: times) {
                cnt += mid / x;
            }
            if (cnt >= (long) n) r = mid;
            else l = mid + 1;
        }
        
        answer = l;
        
        return answer;
    }
}