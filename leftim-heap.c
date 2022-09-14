#左式堆，左结点的零路径长度至少与其右兄弟的零路径长度相同
#include<stdio.h>
#include<stdlib.h>

typedef struct left_heap_node
{
	int key;
	struct left_heap_node* left;
	struct left_heap_node* right;
	int deep;
}Left_heap_node;
typedef Left_heap_node* pl;

pl init(void)
{
	return NULL;
}
#左式堆的合并， 插入和删除，相当于特殊的合并
#填好各结点的零路径长度
pl mert(pl h1, pl h2)
{
	pl swap1 = NULL;
	pl swap2 = NULL;
	pl mid = NULL;
	pl save = NULL;

	if (h1 == NULL)
		return h2;
	if (h2 == NULL)
		return h2;
	if (h1->key < h2->key)
	{
		save = h1;
		swap1 = h1->right;
		swap2 = h2;
	}
	else
	{
		save = h2;
		swap1 = h2->right;
		swap2 = h1;
	}
	h1 = save;
	#循环结束的条件就是一个左式堆已经合并完
	while (swap1 && swap2)
	{
		if (swap1->key > swap2->key)
		{
			save->right = swap2;
			swap2 = swap2->right;
		}
		else
		{
			save->right = swap1;
			swap1 = swap1->right;
		}
		if (save->left && save->right)
		{
			if (save->left->deep < save->right->deep)
				save->deep = save->left->deep + 1;
			else
				save->deep = save->right->deep + 1;
		}
		else
			save->deep = 0;
		save = save->right;
	}
	if (swap1)
		save->right = swap1;
	if (swap2)
		save->right = swap2;
	if (save->left && save->right)
	{
		if (save->left->deep < save->right->deep)
			save->deep = save->left->deep + 1;
		else
			save->deep = save->right->deep + 1;
	}
	else
		save->deep = 0;
	if (h1->left && h1->right)
	{
		if (h1->left->deep < h1->right->deep)
			h1->deep = h1->left->deep + 1;
		else
			h1->deep = h1->right->deep + 1;
	}
	else
		h1->deep = 0;
	save = h1;

	while (h1)
	{
		if (h1->right && h1->left)
		{
			if (h1->right->deep > h1->left->deep)
			{
				pl mid = h1->right;
				h1->right = h1->left;
				h1->left = mid;
			}
		}
		else
		{
			if (h1->right)
			{
				pl mid = h1->right;
				h1->right = h1->left;
				h1->left = mid;
			}
		}
		h1 = h1->right;
	}
	h1 = save;
	return h1;
}

pl insert(pl left_heap, int num)
{
	pl h1 = left_heap;
	pl h2 = (pl)malloc(sizeof(Left_heap_node));
	
	h2->key = num;
	h2->deep = 0;
	h2->left = NULL;
	h2->right = NULL;
	left_heap = mert(h1, h2);
	return left_heap;
}

pl deletmin(pl left_heap)
{
	if (left_heap == NULL)
		return NULL;
	pl left = left_heap->left;
	pl right = left_heap->right;
	free(left_heap);
	left_heap = mert(left, right);
	return left_heap;
}

int main(void)
{
	pl left_heap = init();

	left_heap = insert(left_heap, 20);
	left_heap = insert(left_heap, 40);
	left_heap = insert(left_heap, 30);
	left_heap = insert(left_heap, 50);
	left_heap = insert(left_heap, 26);
	
	fprintf(stdout, "%d %d\n", left_heap->key, left_heap->deep);
	fprintf(stdout, "%d %d\n", left_heap->left->key, left_heap->left->deep);
	fprintf(stdout, "%d %d\n", left_heap->right->left->key, left_heap->right->left->deep);
	left_heap = deletmin(left_heap);
	fprintf(stdout, "%d %d\n", left_heap->key, left_heap->deep);
	return 0;
}
