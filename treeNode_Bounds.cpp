/*
 * Eusebius Ngemera
 * EE2 Data Structures 2015
 * 
 * Binary tree (ascending order)
 * each node contains data (int), and upper and lower bounds for data in the tree with that node as root
 * included functions include maxDenisty(...) for finding the node with highest density
 *  (largest number of nodes in subtree per unit bound range)
 */

#include <iostream>
#include <assert.h>

using namespace std;

struct treeNode{
    int data;
    int lBound;
    int uBound;
    treeNode *left;
    treeNode *right;
};

typedef treeNode * tNodePtr;

int nodeCount(tNodePtr hdTree);                             // returns number of nodes in binary tree
int nodesInRange(tNodePtr hdTree, int LB, int UB);          // returns number of nodes with data within a range, in a binary tree
void insertNode(tNodePtr &hdTree, int data);                // inserts node with data into binary tree
void updateBounds(tNodePtr hdTree);                         // updates bounds in all nodes
void maxDensity(tNodePtr hdTree, tNodePtr &maxP, float &maxD);
    // provides (by reference) pointer and value of node with highest density

void printTree(tNodePtr hdTree, bool withBounds = true);    // prints entire binary tree, with bounds
void printNode(tNodePtr hdTree, bool withBounds = true);    // prints a node, with its bounds

void deleteTree(tNodePtr hdTree);                           // free up dynamic memory allocated to the binary tree

int main(){
    bool printBounds = true;        // print out bounds with each node?

    tNodePtr hdTree = NULL;
    tNodePtr maxDensity_ptr = NULL;
    float maxDensity_value = 0;
    
    // input test case into binary tree
    int input_nums[4] = {3, 0, 19, -21};
    for(int i=0; i<4; i++)
		insertNode(hdTree, input_nums[i]);
    cout << nodeCount(hdTree) << " node(s)" << endl;
    printTree(hdTree, printBounds);
    
    // maximum denisty node
    maxDensity(hdTree, maxDensity_ptr, maxDensity_value);
    assert(maxDensity_ptr != NULL);
    cout << "Highest density is " << maxDensity_value << ":" << endl;
    printNode(maxDensity_ptr, true);

    // free up dynamic memory
    deleteTree(hdTree);
    return 0;
}

int nodeCount(tNodePtr hdTree){
    if(hdTree == NULL)
        return 0;

    return nodeCount(hdTree->left) + nodeCount(hdTree->right) + 1;
}

int nodesInRange(tNodePtr hdTree, int LB, int UB){
    if(hdTree == NULL)
        return 0;

    int currNode = 0;

    if(hdTree->lBound >= LB && hdTree->uBound >= UB)    // include current node if its data is within range
        currNode = 1;

    return nodesInRange(hdTree->left, LB, UB) + nodesInRange(hdTree->right, LB, UB) + currNode;
}

void insertNode(tNodePtr &hdTree, int data){
    if(hdTree == NULL){
        tNodePtr temp;
        temp = new treeNode;    // has to use 'new', else local variable (treeNode temp) will be gone after function exit

        temp->data = data;
        temp->lBound = data;
        temp->uBound = data;
        temp->left = NULL;
        temp->right = NULL;

        hdTree = temp;
    }
    else if(data < hdTree->data){
        if(data < hdTree->lBound)
            hdTree->lBound = data;  // update bounds for this node if new data exceeds current bounds

        insertNode(hdTree->left, data);
    }
    else{
        if(data > hdTree->uBound)
            hdTree->uBound = data;

        insertNode(hdTree->right, data);
    }
}

void updateBounds(tNodePtr hdTree){
    if(hdTree != NULL){
        tNodePtr boundP = hdTree;

        // lower bound
        while(boundP->left != NULL)
            boundP = boundP->left;          // search for node with lowest data in this binary tree

        if(boundP->data < hdTree->lBound)
            hdTree->lBound = boundP->data;

        // upper bound
        boundP = hdTree;

        while(boundP->right != NULL)
            boundP = boundP->right;         // search for node with greatest data

        if(boundP->data > hdTree->uBound)
            hdTree->uBound = boundP->data;

        // recurse
        updateBounds(hdTree->left);
        updateBounds(hdTree->right);
    }
}

void maxDensity(tNodePtr hdTree, tNodePtr &maxP, float &maxD){
    if(hdTree != NULL){
        float currDensity = nodeCount(hdTree)/(hdTree->uBound - hdTree->lBound + 1.0);

        if(currDensity > maxD){
            maxD = currDensity;
            maxP = hdTree;
        }

        maxDensity(hdTree->left, maxP, maxD);
        maxDensity(hdTree->right, maxP, maxD);
    }
}

// latter additions

void printTree(tNodePtr hdTree, bool withBounds){
	if(hdTree != NULL){
		printTree(hdTree->left, withBounds);
		printNode(hdTree, withBounds);
		printTree(hdTree->right, withBounds);
	}
}

void printNode(tNodePtr hdTree, bool withBounds){
    if(hdTree != NULL){
        cout << hdTree->data;
        if(withBounds)
            cout << " (" << hdTree->lBound << "," << hdTree->uBound << ")";
        cout << endl;
    }
}

void deleteTree(tNodePtr hdTree){
    if(hdTree != NULL){
        deleteTree(hdTree->left);
        deleteTree(hdTree->right);
        delete hdTree;
    }
}
