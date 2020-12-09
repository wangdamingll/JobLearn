#include <iostream>
using namespace std;

/*
783. 二叉搜索树节点最小距离
给定一个二叉搜索树的根节点 root，返回树中任意两节点的差的最小值。

 

示例：

输入: root = [4,2,6,1,3,null,null]
输出: 1
解释:
注意，root是树节点对象(TreeNode object)，而不是数组。

给定的树 [4,2,6,1,3,null,null] 可表示为下图:

          4
        /   \
      2      6
     / \    
    1   3  

最小的差值是 1, 它是节点1和节点2的差值, 也是节点3和节点2的差值。
 

注意：

二叉树的大小范围在 2 到 100。
二叉树总是有效的，每个节点的值都是整数，且不重复。
本题与 530：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/ 相同
 * 
 */

 /**
  * Definition for a binary tree node.
  * struct TreeNode {
  *     int val;
  *     TreeNode *left;
  *     TreeNode *right;
  *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  * };
  */


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

//解决办法1
//这里是二叉树搜索树
//最挫的办法是遍历树，放到数组里面 排序后计算相邻元素的差值，取最小值, 但是显然不可取
//时间复杂度:O(N^2)
//空间复杂度:O(N)

//解决办法2
//二叉搜索树的特点是中序遍历按照顺序输出,记录前一个值，用当前值减去 求最小值
class Solution {
public:
    int pre{ 0 };
	
    int minDiffInBST(TreeNode* root) {
        int ans = 1 << 30;
        MinDiffInBST(root, ans);
        return ans;
    }

    /**
	 * \brief  calculate min
	 * \param root  tree root
	 * \param ans  min answer
	 */
	void  MinDiffInBST(TreeNode* root, int& ans) 
    {
        if (root == nullptr) return;
        MinDiffInBST(root->left, ans);
		if(pre!=0)
		{
            ans = std::min(ans, root->val - pre);
		}
        pre = root->val;
        MinDiffInBST(root->right, ans);
    }
	
    /**
	 * \brief   tree middle traverse
	 * \param root  tree root 
	 */
	void PrintTree(TreeNode* root)
    {
	    if(root==nullptr)
	    {
            return;
	    }
        PrintTree(root->left);
        std::cout << root->val << " ";
        PrintTree(root->right);
    }
};

int main () 
{
    Solution s;
	
    TreeNode* root = new TreeNode(4);
    TreeNode* node1 = new TreeNode(2);
    TreeNode* node2 = new TreeNode(6);
    TreeNode* node3 = new TreeNode(1);
    TreeNode* node4 = new TreeNode(3);
	
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;

    s.PrintTree(root);
    std::cout << std::endl;

	int num =  s.minDiffInBST(root);
    std::cout << "nums=" << num << std::endl;
	
	return 0;
}
