#include "red_black_tree.h"
#include <cstring>

//Function to create tree that will be maintained for rest of the functions

rb_red_blk_tree* RBTreeCreate( int (*CompFunc) (const void*,const void*),
			      void (*DestFunc) (void*), void(*InfoDestFunc) (void*),			      
			      void (*PrintFunc) (const void*), void(*PrintInfo)(void*))
			       
{
  rb_red_blk_tree* newTree;
  rb_red_blk_node* temp;

  newTree=(rb_red_blk_tree*) malloc(sizeof(rb_red_blk_tree));
  newTree->Compare=  CompFunc;
  newTree->DestroyKey= DestFunc;
  newTree->PrintKey= PrintFunc;
  newTree->PrintInfo= PrintInfo;
  newTree->DestroyInfo= InfoDestFunc;

  //Allocating dummy root and nil node
  temp=newTree->nil= (rb_red_blk_node*) malloc(sizeof(rb_red_blk_node));
  temp->parent=temp->left=temp->right=temp;
  temp->color=0;
  temp->ID=0;
  temp->count = 0;
  temp=newTree->root= (rb_red_blk_node*) malloc(sizeof(rb_red_blk_node));
  temp->parent=temp->left=temp->right=newTree->nil;
  temp->ID=0;
  temp->count = 0;
  temp->color=0;
  return(newTree);
}

//Read text file for the values of node pair and populate tree
void RBPopulateTree(rb_red_blk_tree* tree, char* filename)
{
	//Opening the file
	FILE *fp;
	fp = fopen(filename, "r");

	if (!fp)
		printf("Error opening file");

	char buf[30];

	//Get the valuesfor number of entries in file
	fscanf(fp, "%s", buf);
	int n = atoi(buf);
	memset(buf, 0, sizeof(buf));
	int ID, count;
	int *newInt, *newCount;

	//Loop over the filea and insert nodes into the file
	for (int i = 0; i < n || !EOF; i++)
	{
		fscanf(fp, "%s", buf);
		ID = atoi(buf);
		memset(buf, 0, sizeof(buf));
		fscanf(fp, "%s", buf);
		count = atoi(buf);
		memset(buf, 0, sizeof(buf));
		newInt = (int*)malloc(sizeof(int));
		newCount = (int*)malloc(sizeof(int));
		*newInt = ID;
		*newCount = count;
		RBTreeInsert(tree, newInt, newCount);
	}
}

//Left rotates the tree at given node

void LeftRotate(rb_red_blk_tree* tree, rb_red_blk_node* x) {
  rb_red_blk_node* y;
  rb_red_blk_node* nil=tree->nil;

  y=x->right;
  x->right=y->left;

  if (y->left != nil)
	  y->left->parent=x; 
  
  y->parent=x->parent;   
  
  if( x == x->parent->left) {
    x->parent->left=y;
  } else {
    x->parent->right=y;
  }
  y->left=x;
  x->parent=y;
}


//Right rotates the tree at given node

void RightRotate(rb_red_blk_tree* tree, rb_red_blk_node* y) {
  rb_red_blk_node* x;
  rb_red_blk_node* nil=tree->nil;

  x=y->left;
  y->left=x->right;

  if (nil != x->right)  
	  x->right->parent=y; 

  x->parent=y->parent;
  if( y == y->parent->left) {
    y->parent->left=x;
  } else {
    y->parent->right=x;
  }
  x->right=y;
  y->parent=x;

}

// To fix up the color tree at given node when two consecutive red nodes are found

void TreeInsertHelp(rb_red_blk_tree* tree, rb_red_blk_node* z) {
  rb_red_blk_node* x;
  rb_red_blk_node* y;
  rb_red_blk_node* nil=tree->nil;
  
  z->left=z->right=nil;
  y=tree->root;
  x=tree->root->left;
  while( x != nil) {
    y=x;
    if (1 == tree->Compare(x->ID,z->ID)) { /* x.key > z.key */
      x=x->left;
    } else { /* x,key <= z.key */
      x=x->right;
    }
  }
  z->parent=y;
  if ( (y == tree->root) ||
       (1 == tree->Compare(y->ID,z->ID))) { /* y.key > z.key */
    y->left=z;
  } else {
    y->right=z;
  }


}

/*  Before calling Insert RBTree the node x should have its key set */

// Insert node into the tree for given key and info

rb_red_blk_node * RBTreeInsert(rb_red_blk_tree* tree, void* key, void* info) {
  rb_red_blk_node * y;
  rb_red_blk_node * x;
  rb_red_blk_node * newNode;

  x=(rb_red_blk_node*) malloc(sizeof(rb_red_blk_node));
  x->ID=key;
  x->count=info;

  TreeInsertHelp(tree,x);
  newNode=x;
  x->color=1;
  while(x->parent->color) { /* use sentinel instead of checking for root */
    if (x->parent == x->parent->parent->left) {
      y=x->parent->parent->right;
      if (y->color) {
	x->parent->color =0;
	y->color =0;
	x->parent->parent->color =1;
	x=x->parent->parent;
      } else {
	if (x == x->parent->right) {
	  x=x->parent;
	  LeftRotate(tree,x);
	}
	x->parent->color =0;
	x->parent->parent->color =1;
	RightRotate(tree,x->parent->parent);
      } 
    } else { 
      y=x->parent->parent->left;
      if (y->color) {
	x->parent->color =0;
	y->color =0;
	x->parent->parent->color =1;
	x=x->parent->parent;
      } else {
	if (x == x->parent->left) {
	  x=x->parent;
	  RightRotate(tree,x);
	}
	x->parent->color=0;
	x->parent->parent->color =1;
	LeftRotate(tree,x->parent->parent);
      } 
    }
  }
  tree->root->left->color =0;
  return(newNode);


}

//Determines next node in inorder travel tree of given node
  
rb_red_blk_node* TreeSuccessor(rb_red_blk_tree* tree,rb_red_blk_node* x) { 
  rb_red_blk_node* y;
  rb_red_blk_node* nil=tree->nil;
  rb_red_blk_node* root=tree->root;

  if (nil != (y = x->right)) { 
    while(y->left != nil) {
      y=y->left;
    }
    return(y);
  } else {
    y=x->parent;
    while(x == y->right) { 
      x=y;
      y=y->parent;
    }
    if (y == root) return(nil);
    return(y);
  }
}

//Determines previous node in inorder travel tree for given node
rb_red_blk_node* TreePredecessor(rb_red_blk_tree* tree, rb_red_blk_node* x) {
  rb_red_blk_node* y;
  rb_red_blk_node* nil=tree->nil;
  rb_red_blk_node* root=tree->root;

  if (nil != (y = x->left)) { /* assignment to y is intentional */
    while(y->right != nil) { /* returns the maximum of the left subtree of x */
      y=y->right;
    }
    return(y);
  } else {
    y=x->parent;
    while(x == y->left) { 
      if (y == root) return(nil); 
      x=y;
      y=y->parent;
    }
    return(y);
  }
}



//Destroy nodes of the tree

void TreeDestHelper(rb_red_blk_tree* tree, rb_red_blk_node* x) {
  rb_red_blk_node* nil=tree->nil;
  if (x != nil) {
    TreeDestHelper(tree,x->left);
    TreeDestHelper(tree,x->right);
    tree->DestroyKey(x->ID);
    tree->DestroyInfo(x->count);
    free(x);
  }
}

//Destroys the tree

void RBTreeDestroy(rb_red_blk_tree* tree) {
  TreeDestHelper(tree,tree->root->left);
  free(tree->root);
  free(tree->nil);
  free(tree);
}

//To determine the count corresponding to given ID
rb_red_blk_node* RBFindCount(rb_red_blk_tree* tree, void* q) {
  rb_red_blk_node* x=tree->root->left;
  rb_red_blk_node* nil=tree->nil;
  int compVal;
  if (x == nil) return(0);
  compVal=tree->Compare(x->ID,(int*) q);
  while(0 != compVal) {
    if (1 == compVal) { 
      x=x->left;
    } else {
      x=x->right;
    }
    if ( x == nil) return(0);
    compVal=tree->Compare(x->ID,(int*) q);
  }
  return(x);
}

//Update count corresponding to given ID
void RBUpdateCount(rb_red_blk_tree* tree, rb_red_blk_node* uNode, void *count)
{
	rb_red_blk_node* nil = tree->nil;
	if (uNode != nil) {
		uNode->count = count;
	}
}


// Performs recoloring and rotation at given node to maintain red black tree property after deletion
void RBDeleteFixUp(rb_red_blk_tree* tree, rb_red_blk_node* x) {
  rb_red_blk_node* root=tree->root->left;
  rb_red_blk_node* w;

  while( (!x->color) && (root != x)) {
    if (x == x->parent->left) {
      w=x->parent->right;
      if (w->color) {
	w->color=0;
	x->parent->color=1;
	LeftRotate(tree,x->parent);
	w=x->parent->right;
      }
      if ( (!w->right->color) && (!w->left->color) ) { 
	w->color=1;
	x=x->parent;
      } else {
	if (!w->right->color) {
	  w->left->color =0;
	  w->color =1;
	  RightRotate(tree,w);
	  w=x->parent->right;
	}
	w->color =x->parent->color;
	x->parent->color =0;
	w->right->color =0;
	LeftRotate(tree,x->parent);
	x=root; 
      }
    } else { /* the code below is has left and right switched from above */
      w=x->parent->left;
      if (w->color) {
	w->color =0;
	x->parent->color =1;
	RightRotate(tree,x->parent);
	w=x->parent->left;
      }
      if ( (!w->right->color) && (!w->left->color) ) {
	w->color =1;
	x=x->parent;
      } else {
	if (!w->left->color) {
	  w->right->color =0;
	  w->color =1;
	  LeftRotate(tree,w);
	  w=x->parent->left;
	}
	w->color =x->parent->color;
	x->parent->color =0;
	w->left->color =0;
	RightRotate(tree,x->parent);
	x=root; /* this is to exit while loop */
      }
    }
  }
  x->color =0;

}


//Deletes given node from the tree

void RBDeleteNode(rb_red_blk_tree* tree, rb_red_blk_node* z){
  rb_red_blk_node* y;
  rb_red_blk_node* x;
  rb_red_blk_node* nil=tree->nil;
  rb_red_blk_node* root=tree->root;

  y= ((z->left == nil) || (z->right == nil)) ? z : TreeSuccessor(tree,z);
  x= (y->left == nil) ? y->right : y->left;
  if (root == (x->parent = y->parent)) { 
    root->left=x;
  } else {
    if (y == y->parent->left) {
      y->parent->left=x;
    } else {
      y->parent->right=x;
    }
  }
  if (y != z) {
    if (!(y->color)) RBDeleteFixUp(tree,x);
  
    tree->DestroyKey(z->ID);
    tree->DestroyInfo(z->count);
    y->left=z->left;
    y->right=z->right;
    y->parent=z->parent;
    y->color=z->color;
    z->left->parent=z->right->parent=y;
    if (z == z->parent->left) {
      z->parent->left=y; 
    } else {
      z->parent->right=y;
    }
    free(z); 
  } else {
    tree->DestroyKey(y->ID);
    tree->DestroyInfo(y->count);
    if (!(y->color)) RBDeleteFixUp(tree,x);
    free(y);
  }

}


// Returns stack cotaines nodes in between given range

stk_stack* RBInrange(rb_red_blk_tree* tree, void* low, void* high) {
  stk_stack* enumResultStack;
  rb_red_blk_node* nil=tree->nil;
  rb_red_blk_node* x=tree->root->left;
  rb_red_blk_node* lastBest=nil;

  enumResultStack=StackCreate();
  while(nil != x) {
    if ( 1 == (tree->Compare(x->ID,high)) ) { 
      x=x->left;
    } else {
      lastBest=x;
      x=x->right;
    }
  }
  while ( (lastBest != nil) && (1 != tree->Compare(low,lastBest->ID))) {
    StackPush(enumResultStack,lastBest);
    lastBest=TreePredecessor(tree,lastBest);
  }
  return(enumResultStack);
}
      
    
  
  



