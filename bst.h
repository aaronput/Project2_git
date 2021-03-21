#ifndef BST_H_
#define BST_H_ 

/* A node structure for use with the 
 * binary search tree.
 */
typedef struct  bst_node {
    char * data;
    struct bst_node * right;
    struct bst_node * left;
} bst_node ;


/* Adds a value to the binary search tree. 
 * Parameters: 
 *  root - the pointer to the root of the tree
 * Return value:
 *  none 
 */ 
void add ( bst_node ** root, char * word );


/* Prints the values stored in the bst according to
 * the inorder traversal. The values should be separated 
 * by a single space. 
 * Parameters: 
 *  root - the root of the tree
 * Return value:
 *  none
 */ 
void inorder ( bst_node * root ) ;

/* Removes the node with the smallest value
 * in the tree. 
 * Parameters: 
 *  root - the pointer to the root of the tree
 * Return value:
 *  the string from the removed node or 
 *  NULL if no node was removed. 
 */ 
char * removeSmallest (  bst_node ** root );

/* Removes the node with the largest value
 * in the tree. 
 * Parameters: 
 *  root - the pointer to the root of the tree
 * Return value:
 *  the string from the removed node or 
 *  NULL if no node was removed. 
 */ 
char * removeLargest (  bst_node ** root );



///////////////////////////////////
// Add other declarations below. //
///////////////////////////////////

/*
the recursive helper function
to inorder traversal in tree with root is [root]
*/
void inorderRec(bst_node* root);

/*
recursive remove the smallest node
*/
char * removeSmallestRec(bst_node** parent,  bst_node **root );

/*
recursive remove the largest node
*/
char * removeLargestRec(bst_node* parent,  bst_node **root );



#endif 
