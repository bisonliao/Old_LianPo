#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <deque>
#include <list>
#include <stack>
#include <assert.h>

struct node
{
    int value;
    struct node * left;
    struct node * right;
    node(int v)
    {
        this->value = v;
        this->left = NULL;
        this->right = NULL;
    }
};
typedef struct node node_t;

//根据数组arr，创建一个棵树，值为empty_val的位置表示是空
int construct_tree(node_t * root, int arr[], int arr_len, int empty_val = -1)
{
    if (arr == NULL || root == NULL || arr_len < 1)
    {
        return -1;
    }
    std::deque<node * > parent;
    root->value = arr[0];
    root->left = NULL;
    root->right = NULL;
    parent.push_back(root);
    for (int i = 1; i < arr_len; i+=2)
    {
        node_t * p = parent.front();
        parent.pop_front();

        if (i<arr_len && arr[i] != empty_val)
        {
            assert(p!=NULL);
            node_t * n = new node_t(arr[i]);
            if (n == NULL)
            {
                fprintf(stderr, "fatal error! new an instance failed at %d\n", __LINE__);
                return -1;
            }
            p->left = n;
            parent.push_back(n);
        }
        else //这个节点是空的，也要压入一个节点来占位置，因为空的节点可能有两个空的孩子
        {
            parent.push_back(NULL);
        }

        if (i+1<arr_len && arr[i+1] != empty_val)
        {
            assert(p!=NULL);
            node_t * n = new node_t(arr[i+1]);
            if (n == NULL)
            {
                fprintf(stderr, "fatal error! new an instance failed at %d\n", __LINE__);
                return -1;
            }
            p->right = n;
            parent.push_back(n);
        }
        else //这个节点是空的，也要压入一个节点来占位置，因为空的节点可能有两个空的孩子
        {
            parent.push_back(NULL);
        }
    }
    return 0;
}

//先序遍历二叉树
int scan_tree_root_first(node_t * root, std::list<node_t> &result)
{
    if (root == NULL) {return 0;}
    std::stack<node_t *> nodes;
    nodes.push(root);

    while (nodes.size() > 0)
    {
        node_t * current = nodes.top();
        nodes.pop();
        result.push_back(*current);

        if (current->right) nodes.push(current->right);
        if (current->left) nodes.push(current->left);
    }
    return 0;

}
// 后续遍历二叉树
int scan_tree_root_last(node_t *root, std::list<node_t> &result)
{
    if (root == NULL) {return 0;}
    std::stack<node_t *> s1, s2;
    s1.push(root);

    while (s1.size() > 0)
    {
        node_t *current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) {s1.push(current->left);}
        if (current->right) {s1.push(current->right);}
    }
    while (s2.size() > 0)
    {
        node_t *current = s2.top();
        s2.pop();
        result.push_back(*current);
    }
    return 0;
}
// 释放树
int free_btree(node_t *root, bool includeRoot = true)
{
    if (root == NULL) {return 0;}
    std::stack<node_t *> s1, s2;
    s1.push(root);

    while (s1.size() > 0)
    {
        node_t *current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) {s1.push(current->left);}
        if (current->right) {s1.push(current->right);}
    }
    while (s2.size() > 1)
    {
        node_t *current = s2.top();
        s2.pop();
        free(current);
    }
    if (includeRoot)
    {
        free(root);
    }
    
    return 0;
}
//中序遍历二叉树 
int scan_tree_root_middle(node_t *root, std::list<node_t> &result)
{
    if (root == NULL)
    {
        return 0; // 空树直接返回
    }

    std::stack<node_t *> stack;
    node_t *current = root;

    while (current != NULL || !stack.empty())
    {
        // 遍历到最左节点，沿途压栈
        while (current != NULL)
        {
            stack.push(current);
            current = current->left;
        }

        // 弹出栈顶节点并访问
        current = stack.top();
        stack.pop();
        result.push_back(*current);

        // 转向右子树
        current = current->right;
    }

    return 0;
}
// 二叉树广度优先遍历
int scan_tree_broad_first(node *root, std::list<node_t> &result)
{
    if (root == NULL) {return 0;}
    std::deque<node_t *> nodeList;
    nodeList.push_back(root);
    result.push_back(*root);
    while (nodeList.size() > 0)
    {
        node_t * current = nodeList.front();
        nodeList.pop_front();
    
        if (current->left)  {nodeList.push_back(current->left); result.push_back(*current->left);}
        if (current->right) {nodeList.push_back(current->right);result.push_back(*current->right);}
    }
    return 0;
}
//二叉树深度优先遍历，采取后根遍历
int scan_tree_depth_first(node *root, std::list<node_t> &result)
{
    if (root == NULL) {return 0;}
    std::stack<node_t*> stack1, stack2;
    stack1.push(root);
    
    while (stack1.size()>0)
    {
        node_t * current = stack1.top();
        stack1.pop();
        stack2.push(current);
        if (current->left)
        {
            stack1.push(current->left);
        }
        if (current->right)
        {
            stack1.push(current->right);
        }
    }
    while (stack2.size() > 0)
    {
        node_t * current = stack2.top();
        stack2.pop();
        result.push_back(*current);
    }
    return 0;
}

int main()
{
 
    // 单元测试用例一：普通二叉树
    {
        int arr[] = {1, 2, 3, -1, 4, 5, 6, -1, -1, -1, -1, -1, -1, 7, -1};
        node_t tree(0);
        construct_tree(&tree, arr, sizeof(arr) / sizeof(int));
        std::list<node_t> result;
        scan_tree_depth_first(&tree, result);
        printf("Test Case 1 (普通二叉树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }

    // 单元测试用例二：完全二叉树
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7};
        node_t tree(0);
        construct_tree(&tree, arr, sizeof(arr) / sizeof(int));
        std::list<node_t> result;
        scan_tree_depth_first(&tree, result);
        printf("Test Case 2 (完全二叉树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }

    // 单元测试用例三：不完全二叉树
    {
        int arr[] = {1, 2, -1, 3, -1, -1, -1, 4, -1};
        node_t tree(0);
        construct_tree(&tree, arr, sizeof(arr) / sizeof(int));
        std::list<node_t> result;
        scan_tree_depth_first(&tree, result);
        printf("Test Case 3 (不完全二叉树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }

    // 单元测试用例四：单节点树
    {
        int arr[] = {1};
        node_t tree(0);
        construct_tree(&tree, arr, sizeof(arr) / sizeof(int));
        std::list<node_t> result;
        scan_tree_depth_first(&tree, result);
        printf("Test Case 4 (单节点树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }

    // 单元测试用例五：空树
    {
        int arr[] = {};
        node_t tree(0);
        construct_tree(&tree, arr, 0);
        std::list<node_t> result;
        scan_tree_depth_first(NULL, result);
        printf("Test Case 5 (空树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }

    // 单元测试用例六：只有左子树的二叉树
    {
        int arr[] = {1, 2, -1, 3, -1};
        node_t tree(0);
        construct_tree(&tree, arr, sizeof(arr) / sizeof(int));
        std::list<node_t> result;
        scan_tree_depth_first(&tree, result);
        printf("Test Case 6 (只有左子树的二叉树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }


    // 单元测试用例七：只有右子树的二叉树
    {
        int arr[] = {1, -1, 2, -1, -1, 3};
        node_t tree(0);
        construct_tree(&tree, arr, sizeof(arr) / sizeof(int));
        std::list<node_t> result;
        scan_tree_depth_first(&tree, result);
        printf("Test Case 7 (只有右子树的二叉树): ");
        for (std::list<node_t>::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            printf("%d ", it->value);
        }
        printf("\n");
    }

    return 0;
}
