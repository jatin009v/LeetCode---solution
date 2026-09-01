// 3568. Minimum Moves to Clean the Classroom

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc;
        vector<pair<int, int>> litter;

        // Find S and all L
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } 
                else if (classroom[r][c] == 'L') {
                    litter.push_back({r, c});
                }
            }
        }

        int k = litter.size();
        int fullMask = (1 << k) - 1;

        // Assign a bit to every litter cell
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            auto [r, c] = litter[i];
            id[r][c] = i;
        }

        /*
            best[r][c][mask] =
            maximum energy with which we have reached
            (r,c) after collecting 'mask'.

            -1 means this state has never been visited.
        */
        vector<vector<vector<signed char>>> best(
            m,
            vector<vector<signed char>>(
                n,
                vector<signed char>(1 << k, -1)
            )
        );

        // r, c, mask, energy
        queue<array<unsigned char, 4>> q;

        best[sr][sc][0] = energy;

        q.push({
            (unsigned char)sr,
            (unsigned char)sc,
            (unsigned char)0,
            (unsigned char)energy
        });

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == fullMask) {
                    return moves;
                }

                // Can't make another move without energy
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    /*
                        If we've already reached this
                        position + mask with MORE energy,
                        this state is useless.
                    */
                    if (best[nr][nc][nmask] >= ne)
                        continue;

                    best[nr][nc][nmask] = ne;

                    q.push({
                        (unsigned char)nr,
                        (unsigned char)nc,
                        (unsigned char)nmask,
                        (unsigned char)ne
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};
