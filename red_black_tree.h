#ifdef DMALLOC
#include <dmalloc.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

typedef struct rb_red_blk_node {
  void* ID;
  void* count;
  int color; /* 0 for black and 1 for red*/
  struct rb_red_blk_node* left;
  struct rb_red_blk_node* right;
  struct rb_red_blk_node* parent;
} rb_red_blk_node;


typedef struct rb_red_blk_tree {
  int (*Compare)(const void* a, const void* b); 
  void (*DestroyKey)(void* a);
  void (*DestroyInfo)(void* a);
  void (*PrintKey)(const void* a);
  void (*PrintInfo)(void* a);

  //To avoid special cases nil will always be maintained in tree
  //nil points to a node which should always be black but has dummy children and parent
  rb_red_blk_node* root;             
  rb_red_blk_node* nil;              
} rb_red_blk_tree;

rb_red_blk_tree* RBTreeCreate(int  (*CompFunc)(const void*, const void*),
			     void (*DestFunc)(void*), 
			     void (*InfoDestFunc)(void*), 
			     void (*PrintFunc)(const void*),
			     void (*PrintInfo)(void*));
void RBPopulateTree(rb_red_blk_tree* tree, char* filename);
rb_red_blk_node * RBTreeInsert(rb_red_blk_tree*, void* key, void* info);

void RBDeleteNode(rb_red_blk_tree* , rb_red_blk_node* );
void RBTreeDestroy(rb_red_blk_tree*);
rb_red_blk_node* TreePredecessor(rb_red_blk_tree*,rb_red_blk_node*);
rb_red_blk_node* TreeSuccessor(rb_red_blk_tree*,rb_red_blk_node*);
rb_red_blk_node* RBFindCount(rb_red_blk_tree*, void*);

void RBUpdateCount(rb_red_blk_tree*, rb_red_blk_node*, void *);
stk_stack * RBInrange(rb_red_blk_tree* tree,void* low, void* high);

