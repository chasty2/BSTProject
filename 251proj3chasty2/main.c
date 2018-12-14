/*main.c*/

//
// Project 3: Auto-Complete
//            Creates BST
//            stats: overall info of BST
//            find: search BST
//            add: Add Nodes
//            suggest: Receive suggestions with auto-complete
// Cody Hasty
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #02
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "251proj3chasty2.h"

//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
  char restOfLine[256];
  int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

  fgets(restOfLine, rolLength, stream);
}


//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);

  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fclose(infile);

  // duplicate and return filename:
  char *s = (char*)malloc(strlen(filename)*sizeof(char)+1);
  strcpy(s, filename);

  return s;
}
void PrintOneNode(BSTNode *cur)
{
  printf("%s: %lld\n", cur->Value.text, cur->Value.weight);
}

int main()
{
    //obtain file, print opening lines
    printf("** Starting Autocomplete **\n");
    char* filename = getFileName();
    printf("** %s **\n", filename);


    //create BST, print "Ready" if successful
    BST *tree = BSTCreate();
    tree = BSTReadInValues(tree, filename);
    printf("** Ready **\n");

    //declare strings to hold commands
    char cmd[64];
    char text[512];

    BSTPrintInorder(tree, PrintOneNode);

    //while loop accepts commands from stdin
    //while input != exit. ifelse statements
    //correspond inputs to respective commands

    printf("** Ready **\n");

  scanf("%s", cmd);

  while (strcmp(cmd, "exit") != 0)
  {

    if (strcmp(cmd, "stats") == 0)
    {
        //count number of leaves and print
        long long leafCount = BSTCountLeaves(tree);
        printf("**Tree count: %lld\n", leafCount);
        //calculate height of tree and print
        int treeHeight = BSTHeight(tree);
        printf("**Tree Height: %d\n", treeHeight);
    }
    else if (strcmp(cmd, "add") == 0)
    {
      long long weight;
      char      part2[512];
      int       part2size = sizeof(part2) / sizeof(part2[0]);

      //
      // add weight text
      //
      scanf("%lld %s", &weight, text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);

      BSTKey addKey = text;
      BSTValue addValue;
      addValue.text = (char *)malloc((strlen(text) + 1) * sizeof(char));
      addValue.text = text;
      addValue.weight = (long long)malloc(sizeof(long long));
      addValue.weight = weight;
      int addCheck = BSTInsert(tree, addKey, addValue);

      //print success or failure of add based on addCheck
      //successful add
      if (addCheck == 1){
        printf("**Added\n");
      }
      else{
        printf("**Not added...\n");
      }

    }
    else if (strcmp(cmd, "find") == 0)
    {
      char part2[512];
      int  part2size = sizeof(part2) / sizeof(part2[0]);

      //
      // find text
      //
      scanf("%s", text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);

      //declare BSTKey and BSTNode to search for
      BSTKey findKey = text;
      BSTNode *findNode = (BSTNode *)malloc(sizeof(BSTNode));
      findNode = BSTSearch(tree, findKey);

      //print info of node if found, not found if not found
      if(findNode != NULL){
        printf("**Phrase: %s\n", findNode->Key);
        printf("**Weight: %lld\n", findNode->Value);
      }
      else{
        printf("**Not found...");
      }
    }
    else if (strcmp(cmd, "suggest") == 0)
    {
      int  k;
      char part2[512];
      int  part2size = sizeof(part2) / sizeof(part2[0]);

      //
      // suggest k text
      //
      scanf("%d %s", &k, text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);

      //declare key and sugNode
      BSTKey sugKey = text;
      BSTNode *sugNode = (BSTNode *)malloc(sizeof(BSTNode));
      //use BSTSugSearch to find Sub-tree root
      sugNode = BSTSugSearch(tree, text);

      //create array of BSTValues to sort if sub-tree root is found


    }
    else
    {
      printf("**unknown cmd, try again...\n");
    }

    scanf("%s", cmd);
  }

  printf("** Done **\n");

  return 0;

}
