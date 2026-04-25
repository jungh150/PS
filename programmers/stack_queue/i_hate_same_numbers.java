import java.util.*;

class Solution {
    public int[] solution(int []arr) {
        ArrayList<Integer> ans = new ArrayList<>();
        
        int sz = arr.length;
        int pre = -1;
        for (int i = 0; i < sz; i++) {
            if (arr[i] != pre) {
                pre = arr[i];
                ans.add(arr[i]);
            }
        }
        
        int n = ans.size();
        int[] answer = new int[n];
        for (int i = 0; i < n; i++) answer[i] = ans.get(i);

        return answer;
    }
}