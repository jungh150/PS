import java.util.*;

class Solution {
    public String solution(String[] participant, String[] completion) {
        String answer = "";
        
        HashMap<String, Integer> mapp = new HashMap<String, Integer>();
        for (String name: participant) {
            if (mapp.containsKey(name)) mapp.put(name, mapp.get(name) + 1);
            else mapp.put(name, 1);
        }
            
        HashMap<String, Integer> mapc = new HashMap<String, Integer>();
        for (String name: completion) {
            if (mapc.containsKey(name)) mapc.put(name, mapc.get(name) + 1);
            else mapc.put(name, 1);
        }
        
        for (String name: mapp.keySet()) {
            if (!mapc.containsKey(name) || mapc.get(name) < mapp.get(name)) {
                answer = name;
                break;
            }
        }
        
        return answer;
    }
}