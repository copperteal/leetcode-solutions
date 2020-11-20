/* binary tree
 * 232 ms
 * 5.13%
 * 12.82%
 */
#include <stdlib.h>
#define min(X,Y) ((X) < (Y) ? (X) : (Y))


struct tree_node {
  int val;
  int freq;
  struct tree_node *left;
  struct tree_node *right;
};

typedef struct tree_node *NodePtr;
NodePtr makeNode(int val);
void freeTree(NodePtr root);
int binary_search(NodePtr *root, int val);
int shortestSub(int *nums, int numsSize, NodePtr root, int freq);


int
findShortestSubArray(int* nums, int numsSize)
{
  if (numsSize < 2) {
    return numsSize;
  }

  int maxfreq = 1;
  int val = nums[0];
  int i;
  int freq = 0;
  NodePtr root = NULL;
  /* find max freq and fill in tree */
  for (i = 0; i < numsSize; i++) {
    freq = binary_search(&root, nums[i]);
    if (freq > maxfreq) {
      maxfreq = freq;
    }
  }
  /* get shortest subarray with max freq */
  int len = shortestSub(nums, numsSize, root, maxfreq);
  freeTree(root);
  return len;
}


NodePtr
makeNode(int val)
{
  NodePtr nd = (NodePtr) malloc(sizeof(struct tree_node));
  nd->val = val;
  nd->freq = 1;
  nd->left = NULL;
  nd->right = NULL;
  return nd;
}


void
freeTree(NodePtr root)
{
  if (root == NULL) {
    return;
  }
  if (root->left) {
    freeTree(root->left);
  }
  if (root->right) {
    freeTree(root->right);
  }
  free(root);
}


int
binary_search(NodePtr *root, int val)
{
  if (*root == NULL) {
    *root = makeNode(val);
    return 1;
  }
  if ((*root)->val > val) {
    if ((*root)->left) {
      return binary_search(&((*root)->left), val);
    } else {
      (*root)->left = makeNode(val);
      return 1;
    }
  } else if ((*root)->val < val) {
    if ((*root)->right) {
      return binary_search(&((*root)->right), val);
    } else {
      (*root)->right = makeNode(val);
      return 1;
    }
  } else {
    ((*root)->freq)++;
    return (*root)->freq;
  }
}


int
shortestSub(int *nums, int numsSize, NodePtr root, int freq)
{
  int len = numsSize;
  if (root->left && root->right) {
    len = min(shortestSub(nums, numsSize, root->left, freq),
    shortestSub(nums, numsSize, root->right, freq));
  } else if (root->left) {
    len = shortestSub(nums, numsSize, root->left, freq);
  } else if (root->right) {
    len = shortestSub(nums, numsSize, root->right, freq);
  }

  if (root->freq == freq) {
    int val = root->val;
    int i, j;
    for (i = 0; i < numsSize && nums[i] != val; i++)
      ;
    for (j = numsSize-1; j >=0 && nums[j] != val; j--)
      ;
    if (j+1 < i+len) {
      len = j-i+1;
    }
  }
  return len;
}
