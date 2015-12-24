#include <stdio.h>
#include <stdlib.h>

struct spisok{
	int count;
	struct spisok* next;
};

struct Node{
	int count;  
	int height;
	struct Node* left;
	struct Node* right;
};

int height(struct Node *derevo){
	if (derevo)
		return derevo->height;
	else
		return 0;
}

int bfactor(struct Node* derevo)
{
	return height(derevo->left) - height(derevo->right);
}

void fixheight(struct Node* derevo)
{
	int left = height(derevo->right);
	int right = height(derevo->left);
	if (left > right)
		derevo->height = left + 1;
	else
		derevo->height = right + 1;
}

struct Node* rotateleft(struct Node* derevo){
	struct Node* tree_new = derevo->right;
	derevo->right = tree_new->left;
	tree_new->left = derevo;
	fixheight(derevo);
	fixheight(tree_new);
	return tree_new;
}

struct Node* rotateright(struct Node* derevo) {
	struct Node* tree_new = derevo->left;
	derevo->left = tree_new->right;
	tree_new->right = derevo;
	fixheight(derevo);
	fixheight(tree_new);
	return tree_new;
}

struct Node* balance(struct Node* derevo){
	fixheight(derevo);
	if (bfactor(derevo) == 2){
		if (bfactor(derevo->left) < 0)
			derevo->left = rotateleft(derevo->left);
		return rotateright(derevo);
	}
	if (bfactor(derevo) == -2){
		if (bfactor(derevo->right) > 0)
			derevo->right = rotateright(derevo->right);
		return rotateleft(derevo);
	}
	return derevo; 
}

struct Node* new_Node(int count, int height){
	struct Node* newNode = calloc(1,sizeof(struct Node));
	newNode->count = count;
	newNode->height = height;
	return newNode;
}

struct Node* insert(struct Node* tree, int k){
	if (!tree) return new_Node(k,1);
	if (k < tree->count)
		tree->right = insert(tree->right, k);
	else
		tree->left = insert(tree->left, k);
	return balance(tree);
}
void add_element(struct spisok* stack, int count){
	while(stack->next != NULL)
		stack = stack->next;
	struct spisok* temp_spisok = calloc(1, sizeof(struct spisok));
	stack->next = temp_spisok;
	stack = stack->next;
	stack->next = NULL;
	stack->count = count;
}
void tree_cmd(struct Node* tree,int high){
	int i = 0;
	for(i = 0; i < high; i++)
		printf(" ");
	printf("%d\n",tree->count);
	if(tree->right != NULL)
		tree_cmd(tree->right, high+1);
	if(tree->left != NULL)
		tree_cmd(tree->left, high+1);
}
void spisok_run(struct Node* tree, struct spisok* stack){
	if(tree->right != NULL)
		spisok_run(tree->right, stack);
	add_element(stack, tree->count);
	if(tree->left != NULL)
		spisok_run(tree->left, stack);
}
void spisok_cmd(struct spisok* stack){
	while(stack->next != NULL){
		printf("%d ",stack->count);
		stack = stack->next;
	}
	printf("%d ",stack->count);
}

void main(int argc, char* argv[]){
	int i,n,tmp;
	struct Node* sosna = NULL;
	struct spisok* stack = NULL;

	FILE* input = fopen(argv[1], "r");
	fscanf(input,"%d", &tmp);
	while(!feof(input)){
		sosna = insert(sosna, tmp);
		fscanf(input,"%d", &tmp);
	}
	sosna = insert(sosna, tmp);
	tree_cmd(sosna,0);
	stack = calloc(1,sizeof(struct spisok));
	spisok_run(sosna,stack);
	stack = stack->next;
	spisok_cmd(stack);
	fclose(input);
}