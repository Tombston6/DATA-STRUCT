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

int findmax(ptnode tree)
{
	ptnode ff = tree;

	if (ff == NULL)
		exit(-1);
	while (ff->right)
		ff = ff->right;
	return ff->key;
}

void insert(int num, ptnode *tree)
{
	ptnode temp = *tree;
	ptnode save = NULL;

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
	}
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
}


int main(void)
{
	ptnode tree = init();
	
	return 0;
}
