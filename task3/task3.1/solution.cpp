#include <algorithm>
#include <vector>

using namespace std;

//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    // Можно жить и без этого метода, но тогда у нас будет много
    // пересекающихся деревьев в конце и будет сложно потом очищать память.
    //
    // Можно не копировать деревья (использовать реализацию copyTree ниже),
    // будем быстрее работать (константа, не асимптотика), но будут траблы с памятью!!!
    TreeNode* copyTree(TreeNode* tree) {
        // return tree;
        if (tree == nullptr) {
            return tree;
        }
        return new TreeNode(tree->val, copyTree(tree->left), copyTree(tree->right));
    }

    // TreeNode* copyTree(TreeNode* tree) {
    //     return tree;
    // }
    
    vector<TreeNode*> generateTrees(int left, int right) {
        vector<TreeNode*> answer;
        if (left > right) {
            answer.push_back(nullptr);
            return answer;
        }
        
        for (int root_val = left; root_val <= right; ++root_val) {
            auto left_sons = generateTrees(left, root_val - 1);
            auto right_sons = generateTrees(root_val + 1, right);
            
            for (auto left_son : left_sons) {
                for (auto right_son : right_sons) {
                    answer.push_back(new TreeNode(root_val, copyTree(left_son), copyTree(right_son)));
                }
            }
        }                    
        return answer;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(1, n);
    }
};