/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
 
class Solution {
public:
    /**
     * @param A: Given an integer array with no duplicates.
     * @return: The root of max tree.
     */
    TreeNode* maxTree(vector<int> nums) {
        TreeNode *root = NULL;
        if (nums.empty())  return root;
        stack<TreeNode *> nodes;
        for (int i = 0; i < nums.size(); i++) {
            TreeNode *curNode = new TreeNode(nums[i]);
            while (!nodes.empty() && curNode->val > (nodes.top())->val) {
                curNode->left = nodes.top();
                nodes.pop();
            }
            if (!nodes.empty())
                (nodes.top())->right = curNode;
            nodes.push(curNode);
        }
        while (!nodes.empty()) {
            root = nodes.top();
            nodes.pop();
        }
        return root;
    }
};
