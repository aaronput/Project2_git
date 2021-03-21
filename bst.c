#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


//root is the pointer to the pointer
//*root is the pointer to a node
//** root is the bst_node 
void add ( bst_node ** root, char * word ) {

	//base case of recursive
	if (*root == NULL){
		//C use malloc to allocate the memory for a node
		*root = (bst_node*)malloc(sizeof(bst_node));
		(*root)->data = word;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}

	//recursive case
	if (strcmp((*root)->data, word) > 0){ //recursive insert to left subtree
		add(&((*root)->left), word);
	}
	else if (strcmp((*root)->data, word) < 0){//recursive insert to right subtree
		add(&((*root)->right), word);
	}
}

 
void inorder (bst_node * root ) {
    inorderRec(root);
    //printf("\n");
}


/*
the recursive helper function
to inorder traversal in tree with root is [root]

inorder print the data in its line
in ascending order
*/
void inorderRec(bst_node* root){

	if (root != NULL){

		//visit left subtree
		inorderRec(root->left);

		//visit root
		printf("%s ", root->data);

		//visit right subtree
		inorderRec(root->right);
	}

}


/*
remove the smallest node

Case 0:
    tree has one node only (no parent)

    "1"


Case 1:
         
         10

       8    11

    6

Case 2:

         "10"

       "8"    "11"

    "6"

      7

 ==>


          10

       8    11

    7

case 3:
    "10"

        "11"
=>delete the root

The new root is "11"



The smallest node is the left-most node of the tree

*/
char * removeSmallest (  bst_node ** root ){
	return removeSmallestRec(NULL, root);
}

/*
recursive remove the smallest node
*/
char * removeSmallestRec(bst_node** parent,  bst_node **root ){

	if (*root != NULL){

		//this root is NOT the smallest node
		if ((*root)->left != NULL){
			return removeSmallestRec(root, &((*root)->left));
		}else
		{//this root node is the smallest node - it has NO left child

			char* data = (*root)->data;

			if ((*root)->right == NULL){//case 1: root has NO right node (leaf node)
				free (*root);
				*root = NULL;
			}else
			{//case 2: root has right child

				//printf ("case 2\n");

				if (*parent == NULL){//delete the root

					if ((*root)->right != NULL){//case 3: if root has right child
						bst_node* rightChild = (*root)->right;
						
						free (*root);
						*root = rightChild;
					}else{
						free (*root);
						*root = NULL;
					}
				}else{

					//printf("has parent %s\n", parent->data);
					bst_node* rightChild = (*root)->right;
					

					//printf("parent left: %s\n", parent->left->data);

					free(*root);
					*root = NULL;

					(*parent)->left = rightChild;
				}
			}

			return data;
		}

	}
    
    return NULL;
}

 
char * removeLargest (  bst_node ** root ){
    
    return removeLargestRec(NULL, root);
}

/*
recursive remove the largest node

Case 0:
    tree has one node only (no parent)

    "1"


Case 1:
         
         10

       8    11

               16

Case 2:

         "10"

       "8"    "11"

                  "16"

              "12"

 ==>


          10

       8    11

               12

case 3:
              "10"

        "9"
=>delete the root

The new root is "9"



The smallest node is the left-most node of the tree
*/
char * removeLargestRec(bst_node* parent,  bst_node **root ){

	if (*root != NULL){

		//this root is NOT the largest node
		if ((*root)->right != NULL){
			return removeLargestRec(*root, &((*root)->right));
		}else
		{//this root node is the largest node - it has NO right child

			char* data = (*root)->data;

			if ((*root)->left == NULL){//case 1: root has NO left node (leaf node)
				free (*root);
				*root = NULL;
			}else
			{//case 2: root has left child

				if (parent == NULL){//delete the root

					if ((*root)->left != NULL){//case 3: if root has left child
						bst_node* leftChild = (*root)->left;
						free (*root);
						*root = leftChild;
					}else{
						free (*root);
						*root = NULL;
					}
				}else{

					bst_node* leftChild = (*root)->left; //keep the left node
					
					free(*root);
					*root = NULL;

					parent->right = leftChild; //set the right child of parent to the left child of root (deleted node)
				}
			}

			return data;		
		}

	}
    
    return NULL;


}



