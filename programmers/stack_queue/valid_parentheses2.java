import java.util.*;

class Solution {
    boolean solution(String s) {
        boolean answer = true;
        
        Deque<Integer> dq = new ArrayDeque<>();
        
        int sz = s.length();
        for (int i = 0; i < sz; i++) {
            if (s.charAt(i) == '(') {
                dq.push(1);
            } else {
                if (dq.size() != 0 && dq.peek() == 1) {
                    dq.pop();
                } else {
                    answer = false;
                    break;
                }
            }
        }
        if (dq.size() != 0) answer = false;

        return answer;
    }
}