// 3505. Minimum Operations to Make Elements Within K Subarrays Equal
class Solution {
    public long minOperations(int[] nums, int x, int k) {
        int n = nums.length;

        long[] cost = new long[n - x + 1];

        // Calculate minimum cost for every window of size x
        TreeMap<Integer, Integer> left = new TreeMap<>();
        TreeMap<Integer, Integer> right = new TreeMap<>();

        long leftSum = 0, rightSum = 0;

        for (int i = 0; i < x; i++) {
            add(nums[i], left, right, leftSum, rightSum);
        }

        // Rebuild initial window using a helper structure
        MedianWindow window = new MedianWindow();

        for (int i = 0; i < x; i++) {
            window.add(nums[i]);
        }

        cost[0] = window.getCost();

        for (int i = x; i < n; i++) {
            window.remove(nums[i - x]);
            window.add(nums[i]);
            cost[i - x + 1] = window.getCost();
        }

        // DP: dp[j] = minimum operations using j non-overlapping windows
        long INF = Long.MAX_VALUE / 4;
        long[][] dp = new long[k + 1][n + 1];

        for (int j = 0; j <= k; j++) {
            Arrays.fill(dp[j], INF);
        }

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {
                dp[j][i] = dp[j][i - 1];

                if (i >= x) {
                    int start = i - x;
                    if (dp[j - 1][start] != INF) {
                        dp[j][i] = Math.min(
                            dp[j][i],
                            dp[j - 1][start] + cost[start]
                        );
                    }
                }
            }
        }

        return dp[k][n];
    }

    static void add(int val, TreeMap<Integer, Integer> a,
                    TreeMap<Integer, Integer> b,
                    long s1, long s2) {
        // Not used
    }

    static class MedianWindow {
        TreeMap<Integer, Integer> low = new TreeMap<>();
        TreeMap<Integer, Integer> high = new TreeMap<>();

        long lowSum = 0, highSum = 0;
        int lowSize = 0, highSize = 0;

        void addMap(TreeMap<Integer, Integer> map, int val) {
            map.put(val, map.getOrDefault(val, 0) + 1);
        }

        void removeMap(TreeMap<Integer, Integer> map, int val) {
            int count = map.get(val);
            if (count == 1) map.remove(val);
            else map.put(val, count - 1);
        }

        void add(int val) {
            if (lowSize == 0 || val <= low.lastKey()) {
                addMap(low, val);
                lowSum += val;
                lowSize++;
            } else {
                addMap(high, val);
                highSum += val;
                highSize++;
            }
            balance();
        }

        void remove(int val) {
            if (low.containsKey(val)) {
                removeMap(low, val);
                lowSum -= val;
                lowSize--;
            } else {
                removeMap(high, val);
                highSum -= val;
                highSize--;
            }
            balance();
        }

        void balance() {
            while (lowSize > highSize + 1) {
                int val = low.lastKey();
                removeMap(low, val);
                lowSum -= val;
                lowSize--;

                addMap(high, val);
                highSum += val;
                highSize++;
            }

            while (lowSize < highSize) {
                int val = high.firstKey();
                removeMap(high, val);
                highSum -= val;
                highSize--;

                addMap(low, val);
                lowSum += val;
                lowSize++;
            }
        }

        long getCost() {
            long median = low.lastKey();
            return median * lowSize - lowSum
                    + highSum - median * highSize;
        }
    }
}
