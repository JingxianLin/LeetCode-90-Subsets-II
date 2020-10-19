# LeetCode-90-Subsets-II

Compared to LeetCode#78 Subsets, here the collections of integers might contain duplicates, but the solution set must not contain duplicate subsets, which makes this problem a little more complicated than before.

Therefore, first, let's recall how to tackle the case with all distinct intergers.  The following code uses the DFS + Backtracking approach:
```
class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> cur;
    for (int i = 0; i <= nums.size(); ++i)
      dfs(nums, i, 0, cur, ans);
    return ans;
  }

private:  
  void dfs(const vector<int>& nums, int n, int s, 
           vector<int>& cur, vector<vector<int>>& ans) {
    if (n == cur.size()) {
      ans.push_back(cur);
      return;
    }
    for (int i = s; i < nums.size(); ++i) {
      cur.push_back(nums[i]);
      dfs(nums, n, i + 1, cur, ans);
      cur.pop_back();
    }
  }
};
```

The key to the current problem is how to avoid duplicates efficiently.  After sorting the collections of integers, duplicates are next to each other, so to remove duplicate subsets in the solution set, when calling DFS, for the same depth, among the same numbers, only the first number can be used.
```
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
```

Runtime complexity analysis: O(N * 2 ^ N), because there are at most 2 ^ N subsets, we will not be able to do better than that; the time complexity for sorting is O(N * log N), but much less the leading term.

Space complexity analysis: O(2 ^ N) if taking space for the solution set into account; otherwise, O(N) due to stack space when calling DFS function.
