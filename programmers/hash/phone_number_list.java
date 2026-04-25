import java.util.*;

class Solution {
    public boolean solution(String[] phone_book) {
        boolean answer = true;
        
        HashSet<String> set = new HashSet<>();
        for (String s: phone_book) {
            int n = s.length();
            for (int i = 1; i < n; i++) {
                set.add(s.substring(0, i));
            }
        }
        
        for (String s: phone_book) {
            if (set.contains(s)) {
                answer = false;
                break;
            }
        }
        
        return answer;
    }
}