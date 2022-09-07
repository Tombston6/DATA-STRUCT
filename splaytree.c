#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct tnode
{
	int key;
	struct tnode* left;
	struct tnode* right;
}Tnode;
typedef Tnode* ptnode;

ptnode init(void)
{
	return NULL;
}

ptnode find(ptnode *tree, int num)
{
	ptnode f = *tree;
	ptnode fin = NULL;

	while (f && num != f->key)
	{
		if (f->key > num)
			f = f->left;
		else
			f = f->right;
	}
	if (f && num == f->key)
	{
		fin = f;
		AVL(tree, fin);
	}

	return fin;
}

int findmin(ptnode tree)
{
	ptnode ff = tree;

	if (ff == NULL)
		exit(-1);
	while (ff->left)
		ff = ff->left;
	return ff->key;
}

int high_tree(ptnode tree)
{
	int max = 0;
	int child = 0;
	ptnode queue[100];
	int front = -1;
	int rear = -1;
	ptnode temp = tree;

	if (tree != NULL)
	{
		queue[++rear] = temp;
		while (rear > front)
		{
			if (temp->left)
			{
				queue[++rear] = temp->left;
				child++;
			}
			if (temp->right)
			{
				queue[++rear] = temp->right;
				child++;
			}
			temp = queue[++front];
			if (child == (rear - front))
			{
				max++;
				child = 0;
			}
		}
	}
	return max;
}

int findmax(ptnode tree)
{
	ptnode ff = tree;

	if (ff == NULL)
		exit(-1);
	while (ff->right)
		ff = ff->right;
	return ff->key;
}

AVL(ptnode* tree, ptnode aim)
{
	ptnode move = *tree;
	ptnode save = move;
	ptnode head = NULL;
	ptnode midl = NULL;
	ptnode midr = NULL;
	ptnode first = NULL;

	while ((*tree)->key != aim->key)
	{
		move = *tree;
		save = move;
		head = NULL;
		first = NULL;
		while (move->key != aim->key)
		{
			first = head;
			head = save;
			save = move;
			if (save == *tree)
				head = NULL;
			if (head == *tree)
				first = NULL;
			if (move->key > aim->key)
				move = move->left;
			else
				move = move->right;
		}

		if (head == NULL)
		{
			if (save->key > move->key)
			{
				midr = move->right;
				move->right = save;
				save->left = midr;
			}
			else
			{
				midl = move->left;
				move->left = save;
				save->right = midl;
			}
			*tree = move;	
		}
		else
		{
			if (first)
			{
				if (first->key > head->key)
					first->left = move;
				else
					first->right = move;
			}
			if (head->key > save->key && save->key > move->key)
			{
				midr = move->right;
				move->right = head;
				save->left = midr;
			}
			if (head->key > save->key && save->key < move->key)
			{
				midl = move->left;
				midr = move->right;
				move->right = head;
				move->left = save;
				head->left = midr;
				save->right = midl;
			}
			if (head->key < save->key && save->key < move->key)
			{
				midl = move->left;
				move->left = head;
				save->right = midl;
			}
			if (head->key < save->key && save->key > move->key)
			{
				midl = move->left;
				midr = move->right;
				move->left = head;
				move->right = save;
				head->right = midl;
				save->left = midr;
			}
		}
	}
}

void insert(int num, ptnode* tree)
{
	ptnode temp = *tree;
	ptnode save = NULL;
	ptnode change = *tree;

	while (temp && temp->key != num)
	{
		save = temp;
		if (temp->key > num)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (temp == NULL)
	{
		temp = (ptnode)malloc(sizeof(Tnode));
		temp->key = num;
		temp->left = NULL;
		temp->right = NULL;
		if (save != NULL)
		{
			if (temp->key > save->key)
				save->right = temp;
			else
				save->left = temp;
		}
		else
			*tree = temp;
		change = *tree;
	}
}

void delete(int num, ptnode* tree)
{
	if (*tree == NULL)
		exit(-1);
	ptnode tf = find(tree, num);
	ptnode fre = *tree;
	ptnode temp = NULL;
	int max;

	if ((*tree)->left == NULL && (*tree)->right == NULL)
		free(*tree);
	if ((*tree)->left == NULL && (*tree)->right != NULL)
	{
		temp = (*tree)->right;
		*tree = temp;
		free(fre);
	}
	if ((*tree)->left && (*tree)->right)
	{
		max = findmax((*tree)->left);
		AVL(&((*tree)->left), max);
		(*tree)->left->right = (*tree)->right;
		temp = (*tree)->left;
		*tree = temp;
		free(fre);
	}
}

int main(void)
{
	ptnode tree = init();

	insert(50, &tree);
	insert(100, &tree);
	insert(200, &tree);
	insert(150, &tree);
	insert(300, &tree);
	insert(180, &tree);
	find(&tree, 150);
	fprintf(stdout, "%d\n", tree->key);
	fprintf(stdout, "%d\n", tree->right->key);
	return 0;
}
