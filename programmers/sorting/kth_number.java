import java.util.*;

class Solution {
    public int[] solution(int[] array, int[][] commands) {
        int[] answer = new int[commands.length];
        
        int n = commands.length;
        for (int i = 0; i < n; i++) {
            ArrayList<Integer> tmp = new ArrayList<>();
            for (int j = commands[i][0]; j <= commands[i][1]; j++) {
                tmp.add(array[j - 1]);
            }
            Collections.sort(tmp);
            answer[i] = tmp.get(commands[i][2] - 1);
        }

        return answer;
    }
}