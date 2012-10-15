/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 *
{}	[]	[]	
   
{1}	[1]	[1]	
   
{1,2}	[2,1]	[2,1]	
   
{1,#,2}	[1,2]	[1,2]	
   
{2,3,#,1}	[1,3,2]	[1,3,2]	
   
{3,1,2}	[1,3,2]	[1,3,2]	
   
{3,1,#,#,2}	[1,2,3]	[1,2,3]	
   
{3,#,1,2}	[3,2,1]	[3,2,1]	
   
{2,#,3,#,1}	[2,3,1]	[2,3,1]	
   
{4,1,#,2,#,3}	[3,2,1,4]	[3,2,1,4]	
   
{1,4,3,2}	[2,4,1,3]	[2,4,1,3]	
   
{4,2,#,1,3}	[1,2,3,4]	[1,2,3,4]	
   
{3,1,#,2,#,#,4}	[2,4,1,3]	[2,4,1,3]	
   
{3,2,4,#,#,1}	[2,3,1,4]	[2,3,1,4]	
   
{1,4,3,#,#,#,2}	[4,1,3,2]	[4,1,3,2]	
   
{3,2,#,#,4,1}	[2,1,4,3]	[2,1,4,3]	
   
{2,1,3,#,4}	[1,4,2,3]	[1,4,2,3]	
   
{3,4,#,#,2,#,1}	[4,2,1,3]	[4,2,1,3]	
   
{2,#,3,4,#,1}	[2,1,4,3]	[2,1,4,3]	
   
{3,#,2,1,4}	[3,1,2,4]	[3,1,2,4]	
   
{1,#,4,3,#,#,2}	[1,3,2,4]	[1,3,2,4]	
   
{4,#,3,#,1,2}	[4,3,2,1]	[4,3,2,1]	
   
{3,#,4,#,1,#,2}	[3,4,1,2]	[3,4,1,2]	
   
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> r;
        stack<TreeNode*> s;
        TreeNode *n = root;
        
        do {
            if (n) {
                s.push(n); 
                n = n->left;
            } else if (!s.empty()) {
                n = s.top();
                s.pop();
                r.push_back(n->val);
                n = n->right;
            }
        } while (!s.empty() || n);
        
        return r;
    }
};