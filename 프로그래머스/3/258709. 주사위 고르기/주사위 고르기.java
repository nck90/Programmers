import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Solution {

    public static void main(String[] args) {
        // Example input
        int[][] dice = {
            {1, 2, 3},
            {4, 5, 6},
            {1, 1, 1},
            {6, 6, 6}
        };
        
        List<Integer> result = solution(dice);
        System.out.println(result);
    }

    public static List<Integer> solution(int[][] dice) {
        int n = dice.length;
        List<List<Integer>> A = new ArrayList<>();
        List<List<Integer>> combinations = getCombinations(n, n / 2);
        
        for (List<Integer> combination : combinations) {
            List<int[]> selectedDice = new ArrayList<>();
            for (int index : combination) {
                selectedDice.add(dice[index]);
            }
            List<Integer> sums = getSumOfProducts(selectedDice);
            Collections.sort(sums);
            A.add(sums);
        }
        
        int a = 0;
        List<Integer> result = new ArrayList<>();
        int p = A.size();
        
        for (int i = 0; i < p; i++) {
            List<Integer> B = A.get(p - i - 1);
            int temp = 0;
            for (int t : A.get(i)) {
                int count = binarySearch(B, t);
                temp += count;
            }
            if (a < temp) {
                a = temp;
                result = new ArrayList<>(combinations.get(i));
                for (int j = 0; j < result.size(); j++) {
                    result.set(j, result.get(j) + 1);
                }
            }
        }
        
        return result;
    }
    
    private static List<List<Integer>> getCombinations(int n, int k) {
        List<List<Integer>> combinations = new ArrayList<>();
        generateCombinations(combinations, new ArrayList<>(), 0, n, k);
        return combinations;
    }
    
    private static void generateCombinations(List<List<Integer>> combinations, List<Integer> current, int start, int n, int k) {
        if (current.size() == k) {
            combinations.add(new ArrayList<>(current));
            return;
        }
        for (int i = start; i < n; i++) {
            current.add(i);
            generateCombinations(combinations, current, i + 1, n, k);
            current.remove(current.size() - 1);
        }
    }
    
    private static List<Integer> getSumOfProducts(List<int[]> selectedDice) {
        List<Integer> result = new ArrayList<>();
        generateProducts(result, selectedDice, 0, 0);
        return result;
    }
    
    private static void generateProducts(List<Integer> result, List<int[]> selectedDice, int index, int currentSum) {
        if (index == selectedDice.size()) {
            result.add(currentSum);
            return;
        }
        for (int num : selectedDice.get(index)) {
            generateProducts(result, selectedDice, index + 1, currentSum + num);
        }
    }
    
    private static int binarySearch(List<Integer> B, int target) {
        int left = 0;
        int right = B.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (B.get(mid) < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
}
