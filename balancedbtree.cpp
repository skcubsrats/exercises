/**
 * Balanced Binary Tree
 * Given a binary tree, determine if it is height-balanced.
 * For this problem, a height-balanced binary tree is defined as a binary tree
 * in which the depth of the two subtrees of every node never differ by more
 * than 1.
 *
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 * Small Test cases:
 * {}	true	true

  {1}	true	true	

  {1,2}	true	true	
     
  {1,#,2}	true	true	
     
  {1,#,2,#,3}	false	false	
     
  {1,#,3,2}	false	false	
     
  {2,1,3}	true	true	
     
  {3,1,#,#,2}	false	false	
     
  {3,2,#,1}	false	false	
     
  {1,2,2,3,#,#,3,4,#,#,4}	false	false	
     
  {1,2,2,3,3,#,#,4,4}	false	false	
     
  {1,2,2,3,3,3,3,4,4,4,4,4,4,#,#,5,5}	true	true	
     
  {1,2,3,4,5,#,6,7}	true	true	
     
  {1,2,3,4,5,#,6,7,#,#,#,#,8}	false	false	
     
  {2,1,3,0,7,9,1,2,#,1,0,#,#,8,8,#,#,#,#,7}	true	true	
     
  {3,9,20,#,#,15,7}	true	true	
     
  {1,2,#,3,#,4,#,5}	false	false	
     
  {2,#,3,#,4,#,5,#,6}	false	false	
     
  {0,2,4,1,#,3,-1,5,1,#,6,#,8}	false	false	
     
  {7,-10,2,-4,3,-8,#,#,#,#,-1,11}	false	false	
     
 */
class Solution {
public:
    void minMaxHeight(TreeNode *node, int *min, int *max) {
        if (!node) {
            return;
        }
        
        int lmin, rmin, lmax, rmax;
        lmin = rmin = lmax = rmax = 0;
        
        minMaxHeight(node->left, &lmin, &lmax);
        minMaxHeight(node->right, &rmin, &rmax);
        
        *min = lmin < rmin? lmin + 1 : rmin + 1;
        *max = lmax > rmax? lmax + 1 : rmax + 1;
    }
    
    bool isBalancedSubTree(TreeNode *subroot, int *depth) {
        if (!subroot) {
            return true;
        }
        
        int ldepth, rdepth;
        ldepth = rdepth = 0;
        
        if (!isBalancedSubTree(subroot->left, &ldepth))
            return false;
        
        if (!isBalancedSubTree(subroot->right, &rdepth))
            return false;
        
        int diff = abs(ldepth - rdepth);
        
        if (diff > 1) {
            return false;
        } else {
            *depth = max(ldepth, rdepth) + 1;
            return true;
        }
    }
    
    bool isBalanced(TreeNode *root) {
        int depth = 0;
        return isBalancedSubTree(root, &depth);
    }
};
