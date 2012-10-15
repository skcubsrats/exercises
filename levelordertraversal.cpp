/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 * input	output	expected	
{}	[]	[]	
   
{1}	[[1]]	[[1]]	
   
{1,2}	[[1],[2]]	[[1],[2]]	
   
{1,#,2}	[[1],[2]]	[[1],[2]]	
   
{1,2,3}	[[1],[2,3]]	[[1],[2,3]]	
   
{1,2,3,4,5}	[[1],[2,3],[4,5]]	[[1],[2,3],[4,5]]	
   
{1,2,3,4,#,#,5}	[[1],[2,3],[4,5]]	[[1],[2,3],[4,5]]	
   
{3,9,20,#,#,15,7}	[[3],[9,20],[15,7]]	[[3],[9,20],[15,7]]	
   
{1,2,#,3,#,4,#,5}	[[1],[2],[3],[4],[5]]	[[1],[2],[3],[4],[5]]	
   
{2,#,3,#,4,#,5,#,6}	[[2],[3],[4],[5],[6]]	[[2],[3],[4],[5],[6]]	
   
{0,2,4,1,#,3,-1,5,1,#,6,#,8}	[[0],[2,4],[1,3,-1],[5,1,6,8]]	[[0],[2,4],[1,3,-1],[5,1,6,8]]	
   
 */
class Solution {
public:
    void levelOrderRecursive(
        TreeNode *node,
        vector<vector<int> > & r,
        int level) {
        if (!node) {
            return;
        }
        
        if (level >= r.size()) {
            r.push_back(vector<int>());
        }
        
        r[level].push_back(node->val);
        
        if (node->left) {
            levelOrderRecursive(node->left, r, level + 1);
        }
        
        if (node->right) {
            levelOrderRecursive(node->right, r, level + 1);
        }
        
    }

    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > r;
        levelOrderRecursive(root, r, 0);
        return r;
    }
};