/*251proj3chasty2.c*/

//
// Binary Search Tree ADT implementation file.
//
// Cody Hasty
// U. of Illinois, Chicago
// CS251, Spring 2017
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "251proj3chasty2.h"


//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
  BST *tree;

  tree = (BST *)malloc(sizeof(BST));
  tree->Root = NULL;
  tree->Count = 0;

  return tree;
}

BST *BSTReadInValues(BST *tree, char* filename)
{
    //open file-containing values, exit if unable to open
    FILE *infile;
    char  line[512];
    int   linesize = sizeof(line) / sizeof(line[0]);

    //declare variables
    BST *inputTree = tree;
    BSTKey key = '\0';
    BSTValue value;
    value.weight = (long long)malloc(sizeof(long long));

    infile = fopen(filename, "r");
    if (infile == NULL)
    {
        printf("**Error: unable to open '%s'\n\n", filename);
        exit(-1);
    }

    //first fscanf
    fscanf(infile, "%lld", &value.weight);

    //while loop inserts nodes
    while(!feof(infile))
    {
        //read in key of next node
        fgets(line, linesize, infile);
        line[strcspn(line, "\r\n")] = '\0';  // strip EOL char(s)

        //move past whitespace at beginning of input
        char *cp = line;
        while(*cp == ' ' || *cp == '\t'){
            cp++;
        }

        //input cp into key and BSTValue
        value.text = (char *)malloc((strlen(cp) + 1) * sizeof(char));
        strcpy(value.text, cp);
        key = cp;

        //insert values into BST
        BSTInsert(inputTree, key, value);

        //fscanf next weight
        fscanf(infile, "%lld", &value.weight);
    }
    fclose(infile);

    return inputTree;
}

//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
  if (strcmp(key1, key2) < 0)
    return -1;
  else if (strcmp(key1, key2) == 0)
    return 0;
  else
    return 1;
}


//
// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned,
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
  BSTNode *cur = tree->Root;

  //
  // search the tree to see if it contains a matching key:
  //
  while (cur != NULL)
  {
    if (BSTCompareKeys(key, cur->Key) == 0)  // found!
      return cur;
    else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
    {
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      cur = cur->Right;
    }
  }

  // if we get here, we fell out of the tree, and didn't find it:
  return NULL;
}
//BSTSugSearch is like BSTSearch, except it uses strncmp to compare the
//prefix to the first characters of the BSTNode key == strlen(prefix)
BSTNode *BSTSugSearch(BST *tree, BSTKey prefix)
{
    BSTNode *cur = tree->Root;

  //
  // search the tree to see if it contains a matching key:
  //
  while (cur != NULL)
  {
    if (strncmp(cur->Key, prefix, (strlen(prefix)-1)) == 0)  // found!
      return cur;
    else if (strncmp(cur->Key, prefix, (strlen(prefix)-1)) < 0)  // smaller, go left:
    {
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      cur = cur->Right;
    }
  }

  // if we get here, we fell out of the tree, and didn't find it:
  return NULL;
}

//
// BSTSearchDepth: searches the binary search tree for a node containing the
// same key, returning the depth of that node if found.  The root node is
// considered depth 0, the next level down is a depth of 1, and so forth.
// If a matching key is not found, the function returns a depth of -1.
//
int BSTSearchDepth(BST *tree, BSTKey key)
{
  BSTNode *cur = tree->Root;
  int depth = 0;

  //
  // search the tree to see if it contains a matching key:
  //
  while (cur != NULL)
  {
    if (BSTCompareKeys(key, cur->Key) == 0)  // found!
      return depth;
    else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
    {
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      cur = cur->Right;
    }

    depth++;
  }

  // if we get here, we fell out of the tree, and didn't find it:
  return -1;
}


//
// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
  BSTNode *prev = NULL;
  BSTNode *cur = tree->Root;

  //
  // first we search the tree to see if it already contains key:
  //
  while (cur != NULL)
  {
    if (BSTCompareKeys(key, cur->Key) == 0)  // already in tree, failed:
      return 0;
    else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
    {
      prev = cur;
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      prev = cur;
      cur = cur->Right;
    }
  }

  //
  // If we get here, tree does not contain key, so insert new node
  // where we fell out of tree:
  //
  BSTNode *T = (BSTNode *)malloc(sizeof(BSTNode));
  T->Key = (BSTKey*)malloc((strlen(key)*sizeof(char) + 1));
  strcpy(T->Key, key);
  T->Value = value;
  T->Left = NULL;
  T->Right = NULL;

  //
  // link T where we fell out of tree -- after prev:
  //
  if (prev == NULL)  // tree is empty, insert @ root:
  {
    tree->Root = T;
  }
  else if (BSTCompareKeys(key, prev->Key) < 0)  // smaller, insert to left:
  {
    prev->Left = T;
  }
  else  // larger, insert to right:
  {
    prev->Right = T;
  }

  tree->Count++;

  return 1;  // success:
}

//
// BSTPrintInorder: prints the nodes of the given binary search
// tree inorder to the console.
//
// NOTE: "pf" is a print function that must be declared like this
// (though the name "pf" doesn't really matter):
//
//  void pf(BSTNode *cur)
//  { ...}
//
// When you call, pass pf and then you'll be able to control
// what gets printed when a node is "visited".
//
void _BSTPrintInorder(BSTNode *root, void (*pf)(BSTNode*))
{
  if (root == NULL)  // base case: empty tree
    return;
  else  // recursive case: non-empty tree
  {
    _BSTPrintInorder(root->Left, pf);
    pf(root);
    _BSTPrintInorder(root->Right, pf);
  }
}

void BSTPrintInorder(BST *tree, void(*pf)(BSTNode*))
{
  printf(">>Inorder: %lld node(s)\n", tree->Count);

  _BSTPrintInorder(tree->Root, pf);

  printf(">><<\n");
}


//
// BSTPrintPreorder: prints the nodes of the given binary search
// tree pre-order to the console.
//
// NOTE: "pf" is a print function that must be declared like this
// (though the name "pf" doesn't really matter):
//
//  void pf(BSTNode *cur)
//  { ...}
//
// When you call, pass pf and then you'll be able to control
// what gets printed when a node is "visited".
//
void _BSTPrintPreorder(BSTNode *root, void(*pf)(BSTNode*))
{
  if (root == NULL)  // base case: empty tree
    return;
  else  // recursive case: non-empty tree
  {
    pf(root);
    _BSTPrintPreorder(root->Left, pf);
    _BSTPrintPreorder(root->Right, pf);
  }
}

void BSTPrintPreorder(BST *tree, void(*pf)(BSTNode*))
{
  printf(">>Preorder: %d node(s)\n", tree->Count);

  _BSTPrintPreorder(tree->Root, pf);

  printf(">><<\n");
}

//
// BSTCount: returns # of nodes in the tree.
//
long long BSTCount(BST *tree)
{
  return tree->Count;
}
//BSTSort helper function _BSTSort takes in a root, the values array,
// and a counter i. The function recursively finds the lowest key
// (character) and sets that to values[0], then increments i and
//travels back up through the tree, filling in the values array.

BSTValue *_BSTSort(BSTNode *root, BSTValue *values, int *i){
   //base case: empty root
   if(root == NULL){
      return values;
   }
   //recursive case: traverse left, add values, then traverse right
   else{
      _BSTSort(root->Left, values, i);

      //assign root->value and increment i
      values[*i] = root->Value;
      *i+= 1;

      _BSTSort(root->Right, values, i);
   }
   return values;
}

//
// BSTSort: traverses the tree inorder so as to yield the (key, value)
// pairs in sorted order by key.  Returns a dynamically-allocated array
// of size N, containing a copy of the value in each tree node.  The
// value N can be obtained by calling BSTCount().
//
// NOTE: the caller is responsible for freeing the returning array.
//
BSTValue *BSTSort(BST *tree)
{
   //declare variables
  BSTValue *values = (BSTValue *)malloc(tree->Count * sizeof(BSTValue));
  BSTNode *treeRoot = tree->Root;
  int counter = 0;

  //call helper function to fill array
  values = _BSTSort(treeRoot, values, &counter);

  return values;
}


//_BSTMaxValue is the recursive helper function of BSTMaxValue.
//It takes the BST's root and a BSTValue variable as parameters
//and traverses the whole tree, updating maxSoFar with the
//greatest value encountered

//max returns the greater value of the two input

BSTValue max(BSTValue v1, BSTValue v2)
{
   return (v1.weight > v2.weight) ? v1: v2;
}

BSTValue _BSTMaxValue(BSTNode *root, BSTValue maxSoFar)
{
   //base case: empty root
   if(root == NULL){
      return maxSoFar;
   }
   //recursive case
   else {
      maxSoFar = max(root->Value, maxSoFar);

      maxSoFar = _BSTMaxValue(root->Left, maxSoFar);
      maxSoFar = _BSTMaxValue(root->Right, maxSoFar);

      return maxSoFar;
   }
}

//
// BSTMaxValue: returns the BSTValue denoting the largest value
// in the tree.  The tree is assumed to contain at least one node,
// i.e. N>0; the function's behavior is undefined if the tree is
// empty, and may crash.
//
BSTValue BSTMaxValue(BST *tree)
{
  BSTNode *searchRoot = tree->Root;

  BSTValue maxSoFar;

  maxSoFar.text = tree->Root->Value.text;
  maxSoFar.weight = tree->Root->Value.weight;

  BSTValue result = _BSTMaxValue(searchRoot, maxSoFar);

  return result;
}

//recursive helper function for BSTCountLeaves.
//It takes in a BSTNode and returns the number
//of leaves, taking the input node as the root.
long long _BSTCountLeaves(BSTNode *Root){
   //base case
   if (Root == NULL){
      return 0;
   }
   else if ((Root->Left == NULL) && (Root->Right == NULL)){
      return 1;
   }
   //recursive case

   long long countL = _BSTCountLeaves(Root->Left);
   long long countR = _BSTCountLeaves(Root->Right);

   return (1 +countL + countR);
}
//BSTCountLeaves takes in a BST and
//uses the recursive helper function
//to return the number of leaves in the tree
long long BSTCountLeaves(BST *tree)
{
    return _BSTCountLeaves(tree->Root);
}

//max2 returns the greater of two integers
//it will be used to return the height of
//a BST
int _max2(int x, int y)
{
    return (x > y) ? x : y;
}

//BSTHeight is like BSTCountLeaves, except
//instead of counting up all the leaves, it
//uses max to return the number corresponding
//to the node with the largest height.
//this is the recursive helper function
int _BSTHeight(BSTNode *root)
{
    //base case
    if(root == NULL){
        return -1;
    }
    else{
        return 1 + _max2(_BSTHeight(root->Left), _BSTHeight(root->Right));
    }
}

//BSTHeight takes in a BST, and uses the helper function
//_BSTHeight to return the max height of the tree

int BSTHeight(BST *tree)
{
    return _BSTHeight(tree->Root);
}
