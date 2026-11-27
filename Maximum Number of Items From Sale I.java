// 3946. Maximum Number of Items From Sale I

class Solution {
    public int maximumSaleItems(int[][] items, int budget) {
        int[] f = new int[budget + 1];
        int mn = Integer.MAX_VALUE;

        for (int[] item : items) {
            int factor = item[0];
            int price = item[1];
            mn = Math.min(mn, price);

            // cnt = number of items whose factor is divisible by this factor
            // (includes itself). Buying first copy gives exactly 'cnt' items
            // (1 purchased + free copies of all multiples).
            int cnt = 0;
            for (int[] other : items) {
                if (other[0] % factor == 0) {
                    cnt++;
                }
            }

            // 0-1 Knapsack: decide whether to buy the first copy of this item
            for (int j = budget; j >= price; j--) {
                f[j] = Math.max(f[j], f[j - price] + cnt);
            }
        }

        // After first purchases, spend remaining budget on the cheapest item
        // (each extra copy gives only +1 item)
        int ans = 0;
        for (int i = 0; i <= budget; i++) {
            ans = Math.max(ans, f[i] + (budget - i) / mn);
        }
        return ans;
    }
}
