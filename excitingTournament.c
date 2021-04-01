#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
//testcase: 5 1 3 4 2 5 1 4 2 3             = 8 
//testcase2: 6 4 3 5 2 1 3 19 10 20 13 6    = 49

typedef struct Node Node; 
struct Node {
    int value; 
    int skill; 
    Node * left; 
    Node * right; 
};
//function declarations 
void preOrderPrint(Node * root);
void postOrderPrint(Node * root);
int nullNodeCounter(Node * root, int counter); 
int findExcitementValue(Node * root);
int findWinner(Node * root);
Node * insertTable(Node * root, int value);
Node * createNode(int value);
Node * insertPlayer(Node * root, int skill);

int main() { 
    int numOfNulls = 0; 
    Node * root; 
    int numPlayers, i;
    int counter;
    //printf("Input the number of players \n"); 
    scanf(" %d", &numPlayers); //scan in the number of players 
    int actOrder[numPlayers], skillLevels[numPlayers]; 

    //printf("input the table activation order\n"); 
    for (i = numPlayers - 2; i != -1 ; i--) //scanning the table activation order in reverse order 
        scanf(" %d", &actOrder[i]); 

    for (i = 0; i < numPlayers - 1; i++) { //inserting the tables into a bst
        int temp = actOrder[i]; 
        root = insertTable(root, temp); 
    }

    //input the skill values for the player and populate the tree
    //printf("input the skill of the players \n"); 
    for (i = 0; i < numPlayers; i++) {
        scanf(" %d", &skillLevels[i]); 
        root = insertPlayer(root, skillLevels[i]);
    }
    int excitement = findExcitementValue(root); 
    printf("The total excitement = %d ", excitement); 
    return excitement; 
}

Node * insertTable(Node * root, int value) { 
    Node * node = createNode(value); 
    if (root == NULL) {
        return node;
    }
    if (node->value == root->value) {
        return root; 
    } 
    if (node->value > root->value) {
        root->right = insertTable(root->right, value); 
   
    } else if (node->value < root->value) { 
        root->left = insertTable(root->left, value); 
    }
    return root; 
}

Node * insertPlayer(Node * root, int skill) {
    Node * player = createNode(0); //create the player and pass in 0 to make sure it is not recognized as a table 
    player->skill = skill; 

    if (root == NULL) 
        return player;
    
    if (root->skill != 0)  //if player return null 
        return NULL; 

    Node * resultL = insertPlayer(root->left, skill); 
     if (resultL == NULL) { //if there is a player to the left 
        Node * resultR = insertPlayer(root->right, skill); 
        if (resultR != NULL) { //if there isn't a player to the right
            root->right = resultR; 
        } else { //if there is a player to the right
            return NULL; 
        }
    } else { //if it passes all of those checks
        root->left = resultL; 
    }
    return root; 
}

Node * createNode(int value) { 
    Node * ret = calloc(1, sizeof(Node)); //create the node with the passed in value
    ret->value = value; 
    ret->left = NULL; 
    ret->right = NULL; 
    ret->skill = 0;  
    return ret; 
}

int findExcitementValue(Node * root) {
    int excitement = 0; 

    if (root->left->value != 0) //if there is a table to the left, go there 
        excitement += findExcitementValue(root->left); 

    if (root->right->value != 0) //if there is a table to the right, go there
        excitement += findExcitementValue(root->right); 
    
    if (root->left->skill != 0 && root->right->skill != 0) { //if both children are players, update the excitement value and the tree
           excitement += abs(root->left->skill - root->right->skill); 

           if (root->left->skill >= root->right->skill) { //update the tree
                root->skill = root->left->skill; 
                root->value = 0; 
                root->left = NULL; 
                root->right = NULL;   
            } else { 
                root->skill = root->right->skill; 
                root->value = 0; 
                root->left = NULL; 
                root->right = NULL; 
        }
    }
    return excitement; 
}

int nullNodeCounter(Node * root, int counter) {
    if (root == NULL) { 
        counter += 1; //if you find null, add 1 to the counter and return 
        return counter; 
    }
    //add the nulls of the left and right to the counter and return 
    counter += nullNodeCounter(root->left, counter); 
    counter += nullNodeCounter(root->right, counter); 
    return counter; 
}

void postOrderPrint(Node * root) { 
    if (root == NULL) //if there is null return, print the postOrder
        return; 
    postOrderPrint(root->left); 
    postOrderPrint(root->right); 
    printf("skill = %d and value = %d  ", root->skill, root->value); 
}

void preOrderPrint(Node * root) { 
    if (root == NULL)  //if there is NULL return, print the preOrder. 
        return; 

    printf("skill = %d and value = %d  ", root->skill, root->value); 
    postOrderPrint(root->left); 
    postOrderPrint(root->right); 
}

