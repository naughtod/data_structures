class Solution {
    public int[] twoSum(int[] nums, int target) {
        int i,j;
        int n = nums.length;
        int[] r = new int[2];
        for (i=0;i<n-1;i++) {
            for (j=i+1;j<n;j++) {
                if (nums[i]+nums[j]==target) {
                    r[0] = i;
                    r[1] = j;
                    return r;
                }
            } 
        }
        return null;
    }
}
