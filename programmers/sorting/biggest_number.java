import java.util.*;

class Solution {
    public String solution(int[] numbers) {        
        ArrayList<String> num = new ArrayList<>();
        for (int x: numbers) {
            num.add(String.valueOf(x));
        }
        
        Collections.sort(num, (s1, s2) -> {
            StringBuilder sb1 = new StringBuilder(s1);
            sb1.append(s2);
            StringBuilder sb2 = new StringBuilder(s2);
            sb2.append(s1);
            return sb2.compareTo(sb1);
        });
        
        StringBuilder res = new StringBuilder();
        for (String x: num) {
            res.append(x);
        }
        
        String answer = res.toString();
        if (answer.charAt(0) == '0') answer = "0";
        
        return answer;
    }
}