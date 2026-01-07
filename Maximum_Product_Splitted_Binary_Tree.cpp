// 1339 – Maximum Product of Splitted Binary Tree

class Solution {
public:
    static const int MOD = 1e9 + 7;
    long long maxProductValue = 0;
    long long totalSum = 0;

    // First DFS: Calculate total sum of tree
    long long getTotalSum(TreeNode* root) {
        if (!root) return 0;
        return root->val + getTotalSum(root->left) + getTotalSum(root->right);
    }

    // Second DFS: Try splitting at every node
    long long dfs(TreeNode* root) {
        if (!root) return 0;

        long long leftSum = dfs(root->left);
        long long rightSum = dfs(root->right);

        long long subtreeSum = root->val + leftSum + rightSum;

        // Calculate product by splitting here
        long long product = subtreeSum * (totalSum - subtreeSum);
        maxProductValue = max(maxProductValue, product);

        return subtreeSum;
    }

    int maxProduct(TreeNode* root) {
        totalSum = getTotalSum(root);
        dfs(root);
        return maxProductValue % MOD;
    }
};
