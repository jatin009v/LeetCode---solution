// 3296. Minimum Number of Seconds to Make Mountain Height Zero

class Solution {
public:
    
    bool possible(long long time, int mountainHeight, vector<int>& workerTimes){
        long long reduced = 0;

        for(long long t : workerTimes){
            
            long long left = 0, right = 100000, best = 0;

            while(left <= right){
                long long mid = (left + right) / 2;

                long long req = t * (mid * (mid + 1) / 2);

                if(req <= time){
                    best = mid;
                    left = mid + 1;
                }
                else right = mid - 1;
            }

            reduced += best;

            if(reduced >= mountainHeight)
                return true;
        }

        return false;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {

        long long left = 1, right = 1e18, ans = right;

        while(left <= right){
            long long mid = (left + right) / 2;

            if(possible(mid, mountainHeight, workerTimes)){
                ans = mid;
                right = mid - 1;
            }
            else left = mid + 1;
        }

        return ans;
    }
};
