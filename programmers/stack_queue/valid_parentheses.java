import java.util.*;

class Solution {
    boolean solution(String s) {
        boolean answer = true;
        
        Stack<Integer> stk = new Stack<>();
        
        int sz = s.length();
        for (int i = 0; i < sz; i++) {
            if (s.charAt(i) == '(') {
                stk.push(1);
            } else {
                if (!stk.empty() && stk.peek() == 1) {
                    stk.pop();
                } else {
                    answer = false;
                    break;
                }
            }
        }
        if (!stk.empty()) answer = false;

        return answer;
    }
}