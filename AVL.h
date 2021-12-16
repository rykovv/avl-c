#ifndef __AVL_H__
#define __AVL_H__

typedef struct Node * Tree;
typedef struct Node {
	int k;
	int h; //hight
	Tree lt;
	Tree rt;
} Node;

typedef struct AVL{
	Tree root;
	int size;
} AVL;

AVL createAVL();
Tree createTree(int k);
int isEmpty(AVL tree);
void destroy(AVL* tree);
void destroyRec(Tree* tree);
int height(Tree tree); //hight of new node
int insert(AVL* tree, int x);
//Item search(AVL tree, int x);
int isElem(AVL tree, int x);
void deleteElem(AVL* tree, int x);
void deleteRec(Tree* tree, int x);
Tree * sptitTree(Tree* rTree, Tree* tree);
int minim(AVL tree);
int maxim(AVL tree);

void rotR(Tree* tree);
void rotL(Tree* tree);
int rightLeaning(Tree tree);
int leftLeaning(Tree tree);
void balance(Tree* tree);
void setHeight(Tree* tree);
void show(AVL tree);
void showTree(Tree tree);

#endif
