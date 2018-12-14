/*251proj3chasty2.h*/

//
// Binary Search Tree ADT header file.
//
// Cody Hasty
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// make sure this header file is #include exactly once:
#pragma once


//
// BST type declarations:
//
typedef char*  BSTKey;
typedef struct BSTValue
{
  char *text;
  long long weight;
} BSTValue;

typedef struct BSTNode
{
  BSTKey    Key;
  BSTValue  Value;
  struct BSTNode  *Left;
  struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
  BSTNode *Root;
  long long      Count;
} BST;


//
// BST API: function prototypes
//
BST *BSTCreate();
BST *BSTReadInValues(BST *tree, char *filename);
int  BSTCompareKeys(BSTKey key1, BSTKey key2);
BSTNode *BSTSearch(BST *tree, BSTKey key);
BSTNode *BSTSugSearch(BST *tree, BSTKey prefix);
int  BSTSearchDepth(BST *tree, BSTKey key);
int  BSTInsert(BST *tree, BSTKey key, BSTValue value);

void BSTPrintInorder(BST *tree, void(*pf)(BSTNode*));
void BSTPrintPreorder(BST *tree, void(*pf)(BSTNode*));

long long BSTCount(BST *tree);
BSTValue *BSTSort(BST *tree);

BSTValue BSTMaxValue(BST *tree);
long long BSTCountLeaves(BST *tree);
int BSTSugCountMatches(BST *tree);
int BSTHeight(BST *tree);


