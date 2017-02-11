#include"red_black_tree.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>


/*  File to read commands and query functions accordingly */

void IntDest(void* a) {
  free((int*)a);
}

int IntComp(const void* a,const void* b) {
  if( *(int*)a > *(int*)b) return(1);
  if( *(int*)a < *(int*)b) return(-1);
  return(0);
}

void IntPrint(const void* a) {
  printf("%i",*(int*)a);
}

void InfoPrint(void* a) {
  ;
}

void InfoDest(void *a){
  ;
}

int main(int argc, char** argv) 
{
  stk_stack* enumResult;
  int len = strlen(argv[1]) + 1;
  char filename[30];
  strncpy(filename, argv[1], len);

  int quit=0;
  int newKey, newInfo, newKey2;
  int *newInt,*newCount;
  rb_red_blk_node* newNode;
  rb_red_blk_tree* tree;
  char command[10];

  tree=RBTreeCreate(IntComp,IntDest,InfoDest,IntPrint,InfoPrint);
  RBPopulateTree(tree, filename);
  while(!quit) {
   
	fscanf(stdin, "%s", command);
	if (!strncmp(command,"increase",strlen("increase")))
	{
		scanf("%i %i", &newKey, &newInfo);
		if ((newNode = RBFindCount(tree, &newKey)))
		{
			int newCounter = *(int*)newNode->count + newInfo;
			RBUpdateCount(tree, newNode, &newCounter);
			printf("%i\n", newCounter);
		}
		else
		{
			newInt = (int*)malloc(sizeof(int));
			newCount = (int*)malloc(sizeof(int));
			*newInt = newKey;
			*newCount = newInfo;
			RBTreeInsert(tree, newInt, newCount);
			printf("%i\n", newInfo);
		}
	}
	else if (!strncmp(command, "reduce", strlen("reduce")))
	{
		scanf("%i %i", &newKey, &newInfo);
		if ((newNode = RBFindCount(tree, &newKey)))
		{
			int newCounter = *(int*)newNode->count - newInfo;
			if (newCounter <= 0)
			{
				RBDeleteNode(tree, newNode);
				printf("0\n");
			}
			else
			{
				RBUpdateCount(tree, newNode, &newCounter);
				printf("%i\n", newCounter);
			}
		}
		else printf("0\n");
	}
	else if (!strncmp(command, "count", strlen("count")))
	{
		scanf("%i", &newKey);
		if ((newNode = RBFindCount(tree, &newKey))) {
			printf("%i\n", *(int*)newNode->count);
		}
		else {
			printf("0\n");
		}
	}
	else if (!strncmp(command, "previous", strlen("previous")))
	{
		scanf("%i", &newKey);
		if ((newNode = RBFindCount(tree, &newKey))) {
			newNode = TreePredecessor(tree, newNode);
			if (tree->nil == newNode) {
				printf("0 0\n");
			}
			else {
				printf("%i %i\n", *(int*)newNode->ID, *(int*)newNode->count);
			}
		}
		else {
			printf("0 0\n");
		}
	}
	else if (!strncmp(command, "next", strlen("next")))
	{
		scanf("%i", &newKey);
		if ((newNode = RBFindCount(tree, &newKey))) {
			newNode = TreeSuccessor(tree, newNode);
			if (tree->nil == newNode) {
				printf("0 0\n");
			}
			else {
				printf("%i %i\n", *(int*)newNode->ID, *(int*)newNode->count);
			}
		}
		else {
			printf("0 0\n");
		}
	}
	else if (!strncmp(command, "inrange", strlen("inrange")))
	{
		scanf("%i %i", &newKey, &newKey2);
		enumResult = RBInrange(tree, &newKey, &newKey2);
		int counter = 0;
		while ((newNode = (rb_red_blk_node *)StackPop(enumResult))) {
			counter += *(int*)newNode->count;
		}
		printf("%i\n", counter);
		free(enumResult);
	}
	else if (!strncmp(command, "quit", strlen("quit")))
	{
		RBTreeDestroy(tree);
		quit = 1;
		return 0;
	}
	else
		printf("Invalid input; Please try again.\n"); 
	
	memset(command, 0, sizeof(command));

  }
  return 0;
}




