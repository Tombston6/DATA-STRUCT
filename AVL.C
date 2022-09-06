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

ptnode find(ptnode tree, int num)
{
	ptnode f = tree;
	ptnode fin = NULL;

	while (f && num != f->key)
	{
		if (f->key > num)
			f = f->left;
		else
			f = f->right;
	}
	if (f && num == f->key)
		fin = f;
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

AVL(ptnode* tree)
{
	ptnode move = *tree;
	ptnode save = move;
	ptnode head = NULL;
	ptnode midl = NULL;
	ptnode midr = NULL;

	while (abs(high_tree(move->right) - high_tree(move->left)) > 1)
	{
		if (save != *tree)
			head = save;
		save = move;
		if (high_tree(move->right) > high_tree(move->left))
			move = move->right;
		else
			move = move->left;
	}
	if (high_tree(save->right) > high_tree(save->left) && high_tree(move->right) > high_tree(move->left))
	{
		if (head == NULL)
			*tree = move;
		else
		{
			if (high_tree(head->right) > high_tree(head->left))
				head->right = move;
			else
				head->left = move;
		}
			midl = move->left;
			move->left = save;
			save->right = midl;
	}
	if (high_tree(save->right) > high_tree(save->left) && high_tree(move->right) < high_tree(move->left))
	{
		if (head == NULL)
			*tree = move->left;
		else
		{
			if (high_tree(head->right) > high_tree(head->left))
				head->right = move->left;
			else
				head->left = move->left;
		}
		midl = move->left->left;
		midr = move->left->right;
		move->left->left = save;
		move->left->right = move;
		save->right = midl;
		move->left = midr;
	}
	if (high_tree(save->right) < high_tree(save->left) && high_tree(move->right) < high_tree(move->left))
	{
		if (head == NULL)
			*tree = move;
		else
		{
			if (high_tree(head->right) > high_tree(head->left))
				head->right = move;
			else
				head->left = move;
		}
		midr = move->right;
		move->right = save;
		save->left = midr;
	}
	if (high_tree(save->right) < high_tree(save->left) && high_tree(move->right) > high_tree(move->left))
	{
		if (head == NULL)
			*tree = move->right;
		else
		{
			if (high_tree(head->right) > high_tree(head->left))
				head->right = move->right;
			else
				head->left = move->right;
		}
		midr = move->right->right;
		midl = move->right->left;
		move->right->left = move;
		move->right->right = save;
		save->left = midr;
		move->right = midl;
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
	if (abs(high_tree(change->right) - high_tree(change->left)) > 1)
		AVL(tree);
}

void delete(int num, ptnode *tree)
{
	ptnode temp;
	ptnode rr;
	ptnode ll;
	ptnode ltemp = NULL;
	ptnode rtemp = NULL;

	temp = find(*tree, num);
	if (temp == NULL)
		return;
	rr = temp->right;
	ll = temp->left;
	if (temp->left == NULL && temp->right == NULL)
		free(temp);
	else if ((temp->left == NULL && temp->right)|| (temp->right == NULL && temp->left))
	{
		if (temp->left)
		{
			temp->key = temp->left->key;
			free(temp->left);
		}
		else
		{
			temp->key = temp->right->key;
			free(temp->right);
		}
	}
	else
	{
		while (rr->left)
		{
			rtemp = rr;
			rr = rr->left;
		}
		while (ll->right)
		{
			ltemp = ll;
			ll = ll->right;
		}
		if (abs(rr->key - temp->key) <= abs(ll->key - temp->key))
		{
			temp->key = rr->key;
			if (rr->right)
				rtemp->left = rr->right;
			free(rr);
		}
		else
		{
			temp->key = ll->key;
			if (ll->left)
				ltemp->right = ll->left;
			free(ll);
		}
	}
	if (abs(high_tree((*tree)->right) - high_tree((*tree)->left)) > 1)
		AVL(tree);
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
	fprintf(stdout, "%d\n", tree->key);
	fprintf(stdout, "%d\n", tree->right->key);
	return 0;
}
