class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        const int n = nums.size();
        sort(begin(nums), end(nums));
        vector<vector<int>> ans;
        vector<int> cur;
   
        function<void(int)> dfs = [&](int s) {
          ans.push_back(cur);
          if (cur.size() == n)
            return;      
          for (int i = s; i < n; ++i) {
            if (i > s && nums[i] == nums[i - 1]) continue;
              cur.push_back(nums[i]);
            dfs(i + 1);
            cur.pop_back();
          }
        };

        dfs(0);
        return ans;
    }
};
