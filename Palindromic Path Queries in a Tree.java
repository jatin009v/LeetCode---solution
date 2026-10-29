// 3841. Palindromic Path Queries in a Tree

import java.util.*;

class Solution {
    private int n, timer, LOG;
    private int[] tin, depth;
    private int[][] up;
    private int[] bit;
    private int[] head, to, next;
    private char[] chars;
    private int edgeCount;

    public List<Boolean> palindromePath(int n, int[][] edges,
                                        String s, String[] queries) {
        this.n = n;
        this.chars = s.toCharArray();
        this.timer = 0;

        LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }

        tin = new int[n];
        depth = new int[n];
        up = new int[LOG][n];
        bit = new int[n + 2];

        head = new int[n];
        Arrays.fill(head, -1);

        to = new int[2 * (n - 1)];
        next = new int[2 * (n - 1)];
        edgeCount = 0;

        for (int[] e : edges) {
            addEdge(e[0], e[1]);
            addEdge(e[1], e[0]);
        }

        buildTree();

        for (int i = 0; i < n; i++) {
            updateBit(tin[i], 1 << (chars[i] - 'a'));
        }

        List<Boolean> answer = new ArrayList<>();

        for (String q : queries) {
            String[] parts = q.split(" ");
            int u = Integer.parseInt(parts[1]);

            if (parts[0].equals("update")) {
                char c = parts[2].charAt(0);

                if (chars[u] != c) {
                    updateBit(tin[u], 1 << (chars[u] - 'a'));
                    updateBit(tin[u], 1 << (c - 'a'));
                    chars[u] = c;
                }
            } else {
                int v = Integer.parseInt(parts[2]);
                int lca = getLCA(u, v);

                int maskU = queryBit(tin[u]);
                int maskV = queryBit(tin[v]);
                int maskL = queryBit(tin[lca]);

                int pathMask = maskU ^ maskV ^ maskL
                        ^ (1 << (chars[lca] - 'a'));

                answer.add((pathMask & (pathMask - 1)) == 0);
            }
        }

        return answer;
    }

    private void addEdge(int u, int v) {
        to[edgeCount] = v;
        next[edgeCount] = head[u];
        head[u] = edgeCount++;
    }

    private void buildTree() {
        int[] parent = new int[n];
        int[] iter = new int[n];
        int[] stack = new int[n];

        Arrays.fill(parent, -1);

        int top = 0;
        stack[top++] = 0;
        parent[0] = 0;

        while (top > 0) {
            int u = stack[top - 1];

            if (iter[u] == 0) {
                tin[u] = ++timer;
                up[0][u] = parent[u];

                for (int j = 1; j < LOG; j++) {
                    up[j][u] = up[j - 1][up[j - 1][u]];
                }

                iter[u] = head[u] + 1;
            }

            int edge = iter[u] - 1;

            if (edge == -1) {
                top--;
                continue;
            }

            iter[u] = next[edge] + 1;
            int v = to[edge];

            if (v == parent[u]) {
                continue;
            }

            parent[v] = u;
            depth[v] = depth[u] + 1;
            stack[top++] = v;
        }
    }

    private void updateBit(int index, int mask) {
        for (int i = index; i <= n; i += i & -i) {
            bit[i] ^= mask;
        }
    }

    private int queryBit(int index) {
        int mask = 0;

        for (int i = index; i > 0; i -= i & -i) {
            mask ^= bit[i];
        }

        return mask;
    }

    private int getLCA(int u, int v) {
        if (depth[u] < depth[v]) {
            int temp = u;
            u = v;
            v = temp;
        }

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if ((diff & (1 << j)) != 0) {
                u = up[j][u];
            }
        }

        if (u == v) {
            return u;
        }

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }
}
