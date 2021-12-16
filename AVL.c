#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main(int argc, char ** argv){
	AVL t = createAVL();
	printf("tree is created\n");
	//show(t);
	insert(&t, 8);
	//show(t);
	insert(&t, 4);
	//show(t);
	insert(&t, 12);
	//show(t);
	insert(&t, 2);
	//show(t);
	insert(&t, 6);
	insert(&t, 10);
	insert(&t, 14);
	insert(&t, 1);
	insert(&t, 3);
	insert(&t, 5);
	insert(&t, 7);
	insert(&t, 9);
	insert(&t, 11);
	insert(&t, 13);
	insert(&t, 15);
	//show(t);
	//printf("isElem 25 = %d\n",  isElem(t, 25));
	//printf("minim of tree is %d\n", minim(t));
	//printf("maxim of tree is %d\n", maxim(t));
	printf("now we insert 10\n");
	//rotL(&(t.root));
	//insert(&t, 10);
	//rotL(&(t.root));
	show(t);
	printf("\n");
	deleteElem(&t, 4);
	show(t);
	return 0;
}

AVL createAVL(){
	AVL tree;
	tree.root = (Tree)malloc(sizeof(Node));
	tree.root = NULL;
	tree.size = 0;

	return tree;
}

Tree createTree(int x){
	Tree tree = (Tree)malloc(sizeof(Node));
	tree -> k = x;
	tree -> h = 1;
	tree -> lt = NULL;
	tree -> rt = NULL;
	
	return tree;
}

int isEmpty(AVL tree){
	return tree.root == NULL && tree.size == 0;
}

void destroy(AVL* tree){
	Tree root = (*tree).root;
	Tree lt = root -> lt;
	Tree rt = root -> rt;
	free(root);
	destroyRec(&lt);
	destroyRec(&rt);
}
void destroyRec(Tree* tree){
	if(*tree == NULL)
		return;
	Tree lt = (*tree) -> lt;
	Tree rt = (*tree) -> rt;
	free(tree);
	destroyRec(&lt);
	destroyRec(&rt);
}

int height(Tree tree){
	return tree == NULL ? 0 : tree -> h;
}

int insert(AVL* tree, int x){
	int ret = -1;
	//if the tree is empty
	if(isEmpty(*tree)){
		*tree = createAVL();
		(*tree).root = createTree(x);
		balance(&((*tree).root));
		(*tree).size += 1;
	} else { //in any other case
		Tree ptrTree = (*tree).root;
		if(ptrTree -> k > x){
			ret = insertRec(&(ptrTree -> lt), x);
			balance(&((*tree).root));
		} else if(ptrTree -> k < x){
			ret = insertRec(&(ptrTree -> rt), x);
			balance(&ptrTree);
		} 
	}
	if(ret == x)
		(*tree).size += 1;

	return ret;
}

int insertRec(Tree* tree, int x){
	if(*tree == NULL){
		*tree = createTree(x);
		balance(tree);
		return x;
	} else if((*tree) -> k > x){
		insertRec(&((*tree) -> lt), x);
		balance(tree);
		return x;
	} else if((*tree) -> k < x){
		insertRec(&((*tree) -> rt), x);
		balance(tree);
		return x;
	} else { 
		return 1;
	}
}

void show(AVL tree){
	if(isEmpty(tree))
		printf("Empty tree\n");
	else {
		Tree ptrRoot = tree.root;
		showTree(ptrRoot);
		printf("\n");
	}
}

void showTree(Tree tree){
	if(tree == NULL){
		printf("x");
		return;
	}
	printf("Node <");
	showTree(tree -> lt);
	printf(">");
	printf(" %d", tree -> k);	
	printf("-%d ", tree -> h);
	showTree(tree -> rt);
	printf("> ");
}

int isElem(AVL tree, int x){
	printf("entered isElem\n");
	if(isEmpty(tree))
		return 0;
	Tree ptrTree = tree.root;
	int ret = 0;
	while(ptrTree != NULL && !ret){
		if(ptrTree -> k == x)
			ret = 1;
		printf("%d, ", ptrTree -> k);
		if(ptrTree -> k > x)
			ptrTree = ptrTree -> lt;
		else if(ptrTree -> k < x)
			ptrTree = ptrTree -> rt;
	}
	return ret;
}

int minim(AVL tree){
	if(isEmpty(tree)){
		printf("empty tree\n");
		exit(-1);
	}
	Tree ptrTree = tree.root;
	while(ptrTree -> lt != NULL)
		ptrTree = ptrTree -> lt;
	return ptrTree -> k;
}

int maxim(AVL tree){
	if(isEmpty(tree)){
		printf("empty tree\n");
		exit(-1);
	}
	Tree ptrTree = tree.root;
	while(ptrTree -> rt != NULL)
		ptrTree = ptrTree -> rt;
	return ptrTree -> k;
}

int max(int a, int b){
	return a > b ? a : b;
}

void setHeight(Tree* tree){
	if((*tree) -> lt == NULL && (*tree) -> rt == NULL)
		(*tree) -> h = 0;
	else if((*tree) -> lt == NULL)
		(*tree) -> h = 1 + (*tree) -> rt -> h;
	else if((*tree) -> rt == NULL)
		(*tree) -> h = 1 + (*tree) -> lt -> h;
	else
		(*tree) -> h = 1 + max((*tree) -> lt -> h, (*tree) -> rt -> h);
}

void rotR(Tree* tree){
	//first let's separate all elements we gonna working with
	Tree ptrTree = *tree;
	Tree LT = ptrTree -> lt;
	Tree LRT = ptrTree -> lt -> rt;

	//now we have everything we need to rotate the tree
	*tree = LT;
	(*tree) -> rt = ptrTree;
	ptrTree -> lt = LRT;
	setHeight(&ptrTree);
	setHeight(tree);
}

void rotL(Tree* tree){
	Tree ptrTree = *tree;
	Tree RT = ptrTree -> rt;
	Tree RLT = ptrTree -> rt -> lt;
	
	
	*tree = RT;
	(*tree) -> lt = ptrTree;
	ptrTree -> rt = RLT;
	setHeight(&ptrTree);
	setHeight(tree);
}

int rightLeaning(Tree tree){
	return height(tree -> lt) < height(tree -> rt);
}

int leftLeaning(Tree tree){
	return height(tree -> lt) > height(tree -> rt);
}

void balance(Tree* tree){
	if(*tree == NULL)
		return;
	Tree ptrTree = *tree;
	int hlt = height(ptrTree -> lt);
	int hrt = height(ptrTree -> rt);

	if(hlt - hrt > 1 && leftLeaning(ptrTree)){
		printf("leftLeaning\n");
		rotR(&ptrTree);
	} else if(hlt - hrt > 1){
		printf("rotL & rotR\n");
		rotL(&(ptrTree -> lt));
		rotR(&(ptrTree));
	} else if(hrt - hlt > 1 && rightLeaning(ptrTree)){
		printf("rightLeaning\n");
		rotL(&ptrTree);
	} else if(hrt - hlt > 1){
		printf("rotR & rotL\n");
		rotR(&(ptrTree -> rt));
		rotL(&ptrTree);
	} else {
		setHeight(&ptrTree);
	}
}

Tree * splitTree(Tree* rTree, Tree* tree){
	if((*rTree) -> lt == NULL){
		//min found
		(*tree) -> k = (*rTree) -> k;
		return &((*rTree) -> rt);
	} else {
		//remove min from left subtree
		Tree *r = splitTree(&(*rTree) -> lt, tree);
		Tree *lt = &((*rTree) -> lt);
		lt = r;
		free(*r);
		*r = NULL;
		balance(rTree);
		return rTree;
	}
}

void deleteElem(AVL* tree, int x){
	deleteRec(&((*tree).root), x);
	(*tree).size -= 1;
}

void deleteRec(Tree* tree, int x){
	if(*tree == NULL)
		return;
	if((*tree) -> k > x){
		deleteRec(&((*tree) -> lt), x);
		balance(tree);
	} else if((*tree) -> k < x){
		deleteRec(&((*tree) -> rt), x);
		balance(tree);
	} else {
		if((*tree) -> lt == NULL){
			Tree rt = (*tree) -> rt;
			*tree = (*tree) -> rt;
			free(rt);
		} else if((*tree) -> rt == NULL){
			Tree lt = (*tree) -> lt;
			*tree = (*tree) -> lt;
			free(lt);
		} else {
			Tree *rt = &((*tree) -> rt);
			Tree *r = splitTree(&((*tree) -> rt), tree);
			rt = r;
			free((*r) -> lt);
			(*r) -> lt = NULL;
			balance(tree);
		}
	}
}
