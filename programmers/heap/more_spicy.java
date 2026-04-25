import java.util.*;

class Solution {
    public int solution(int[] scoville, int K) {
        int answer = 0;
        
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
        for (int s: scoville) {
            pq.offer(s);
        }

        while (true) {
            if (pq.size() == 0) {
                answer = -1;
                break;
            }
            
            int s1, s2;

            if (pq.peek() < K) {
                s1 = pq.poll();
            } else {
                break;
            }

            if (pq.size() == 0) {
                answer = -1;
                break;
            } else {
                s2 = pq.poll();
            }
            
            pq.offer(s1 + 2 * s2);
            answer++;
        }
        
        return answer;
    }
}