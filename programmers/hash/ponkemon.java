import java.util.*;

class Solution {
    public int solution(int[] nums) {
        int answer = 0;
        
        HashSet<Integer> set = new HashSet<>();
        for (int x: nums) set.add(x);
        
        answer = Math.min(nums.length / 2, set.size());
        
        return answer;
    }
}