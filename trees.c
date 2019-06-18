#include <stdio.h>
#include <stdlib.h>

/* Makes a tree */
typedef struct trees {
	int value;
	struct trees* left;
	struct trees* right;
} tree ;

/* Gets the total nodes */
int totalNodes(tree* aTree) {
	if (aTree) {
		return 1 + totalNodes((*aTree).left) + totalNodes((*aTree).right);
	}
	return 0;
}

/* Makes a tree with the given values */
void makeTree(tree* aTree, int val) {
	(*aTree).value = val;
	aTree->left = NULL;
	aTree->right = NULL;
}

/* Gets the maximum of two numbers */
int maximum(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	} else {
		return val2;
	}
}

/* Gets the max value using an accumulator */
int maxAcc(tree* aTree, int val) {
	if (aTree) {
		tree this = *aTree;
		return maxAcc(this.left, maxAcc(this.right, maximum(val, this.value)));
	}
	return val;
}

/* Gets the max value from a tree. Returns 0 if there is no value*/
int max(tree* aTree) {
	if (aTree) {
		tree this = *aTree;
		return maxAcc(this.left, maxAcc(this.right, this.value));
	}
	return 0;
}

/* Inserts a given value into a Binary Search Tree */
tree * insertIntoTree(tree* aTree, int val) {
	if (aTree) {
		if (aTree->value < val) {
			aTree->right = insertIntoTree(aTree->right, val);
		} else {
			aTree->left = insertIntoTree(aTree->left, val);
		}
		return aTree;
	}
	else {
		aTree = (tree *) malloc(sizeof(tree));
		aTree->value = val;
		aTree->left = NULL;
		aTree->right = NULL;
		return aTree;
	}
}

/* Accumulates depth data */
int getDepthAcc(tree* aTree, int val, int depth) {
	if (aTree) {
		if (aTree->value == val) {
			return depth;
		} else if (aTree->value > val) {
			return getDepthAcc(aTree->right, val, depth + 1);
		} else {
			return getDepthAcc(aTree->left, val, depth + 1);
		}
	}
	return -1;
}

/*Gets the depth of a number*/
int getDepth(tree* aTree, int val) {
	return getDepthAcc(aTree, val, 0);
}

/*Inserts a value into a binary search tree*/
void insertMutate(tree** aTree, int val) {
	if (*aTree) {
		if ((*aTree)->value > val) {
			insertMutate(&((*aTree)->left), val);
		} else {
			insertMutate(&((*aTree)->right), val);
		}
	} else {
		*aTree = (tree *)malloc(sizeof(tree));
		makeTree(*aTree, val);
	}
}

int getDepthOfTree(tree* aTree) {
	if (aTree) {
		return 1 + maximum(getDepthOfTree(aTree->left), getDepthOfTree(aTree->right));
	}
	return 0;
}

/*Frees all data within a tree*/
void freeTree(tree* aTree) {
	if (aTree) {
		freeTree(aTree->right);
		freeTree(aTree->left);
		free(aTree);
	}
}

/*Finds a ppath within a tree, while not overwriting memory*/
void findPathWithValidDistance(char** path, tree* aTree, int val, int depth) {
	if (aTree) {
		if (aTree->value == val) {
			*((*path) + depth) = 'h';
			*((*path) + depth + 1) = '\0';
		} else if (aTree->value > val) {
			*((*path) + depth) = 'l';
			findPathWithValidDistance(path, aTree->left, val, depth + 1);
		} else {
			*((*path) + depth) = 'r';
			findPathWithValidDistance(path, aTree->right, val, depth + 1);
		}
	}
	else {
		**path = 'f';
		*((*path) + 1) = '\0';
	}

}

/*Finds a path within a tree*/
void findPath(char** path, tree* aTree, int val) {
	if (aTree) {
		*path = (char*)malloc(sizeof(char) * (getDepthOfTree(aTree) + 1));
		findPathWithValidDistance(path, aTree, val, 0);
	}
	else {
		*path = (char*)malloc(sizeof(char) * 2);
		**path = 'f';
		*((*path) + 1) = '\0';
	}
}
/* Main method */
int main() {
	printf("There are %d nodes in null\n", totalNodes(NULL));
	tree tree1;
	makeTree(&tree1, 7);

	tree tree2;
	makeTree(&tree2, 9);
	tree2.left = &tree1;
	printf("There are %d nodes in  7 -> null -> null\n", totalNodes(&tree1));
	printf("The max is %d\n", max(&tree2));	
	printf("The max of null is %d\n", max(NULL));

	tree tree3;
	makeTree(&tree3, -4);
	tree tree4;
	makeTree(&tree4, -100);
	tree3.right = &tree4;

	printf("The max should be -4, it is %d\n", max(&tree3));
	tree* bst = NULL;

	bst = insertIntoTree(bst, 8);
	bst = insertIntoTree(bst, 100);
	bst = insertIntoTree(bst, 4);
	printf("The top is %d\n", bst->value);
	printf("The left is %d\n", bst->left->value);
	printf("The right is %d\n", bst->right->value);
	printf("The depth of 8 is %d\n", getDepth(bst, 8));
	printf("The depth of 100 is %d\n", getDepth(bst, 100));	
	printf("101 doesn't exist, so it will print out %d\n", getDepth(bst, 101));
	freeTree(bst);
	tree* bst2 = NULL;
	insertMutate(&bst2, 100);
	printf("The main value is %d\n", bst2->value);
	insertMutate(&bst2, 8);
	printf("The left value is %d\n", bst2->left->value);
	insertMutate(&bst2, 101);
	printf("The right value is %d\n", bst2->right->value);
	freeTree(bst2);	
	tree* bst3 = NULL;
	insertMutate(&bst3, 10);
       	insertMutate(&bst3, 100);
	insertMutate(&bst3, 101);
	insertMutate(&bst3, 99);
	insertMutate(&bst3, -9);
	insertMutate(&bst3, -100);
	insertMutate(&bst3, 0);
	printf("The top is %d\n", bst3->value);
	printf("The right is %d\n", bst3->right->value);
	printf("The left is %d\n", bst3->left->value);
	printf("The right right is %d\n", bst3->right->right->value);
	printf("The right left is %d\n", bst3->right->left->value);
	printf("The left right is %d\n", bst3->left->right->value);
	printf("The left left is %d\n", bst3->left->left->value);
	
	char* path = NULL;
	findPath(&path, bst3, 100);
	printf("%s", path);
	printf("\n");
	printf("This is not in the tree");
	printf(" ");
	findPath(&path, bst3, 1000);
	printf("%s", path);
	printf("\n");
	free(path);	
	freeTree(bst3);
	return 0;
}
