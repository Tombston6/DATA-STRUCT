#include<stdio.h>
#include<stdlib.h>
#define MAX 100

//跟着搞项目，时间久了不想重新想怎么写deletmin函数了

//树的节点
typedef struct node
{
	int key;
	struct node* first;
	struct node* next_bro;
}Binomial_node;
typedef Binomial_node* PB;

//二项队列的定义
typedef struct queue
{
	PB Binomial_queue[MAX];
	int size;
}Binomial;

//二项队列中树的合并
PB tree_mert(PB t1, PB t2)
{
	if (t1->key > t2->key)
		return tree_mert(t2, t1);
	t2->next_bro = t1->first;
	t1->first = t2;
	return t1;
}

//二项堆的合并
Binomial queue_mert(Binomial H1, Binomial H2)
{
	PB tree1 = NULL, tree2 = NULL, Carry = NULL;
	int i, j;

	if (H1.size + H2.size > MAX - 1)
		fprintf(stderr, "size too big to can't save it!");
	H1.size += H2.size;
	for (i = 0, j = 1; j <= MAX; i++, j *= 2)
	{
		tree1 = H1.Binomial_queue[i];
		tree2 = H2.Binomial_queue[i];

		switch (!!tree1 + 2 * !!tree2 + 4 * !!Carry)
		{
			case 0:
				break;
			case 1:
				break;
			case 2:
				H1.Binomial_queue[i] = tree2;
				H2.Binomial_queue[i] = NULL;
				break;
			case 4:
				H1.Binomial_queue[i] = Carry;
				Carry = NULL;
				break;
			case 3:
				Carry = tree_mert(tree1, tree2);
				H1.Binomial_queue[i] = H2.Binomial_queue[i] = NULL;
				break;
			case 5:
				Carry = tree_mert(tree1, Carry);
				H1.Binomial_queue[i] = NULL;
				break;
			case 6:
				Carry = tree_mert(tree2, Carry);
				H2.Binomial_queue[i] = NULL;
				break;
			case 7:
				H1.Binomial_queue[i] = Carry;
				Carry = tree_mert(tree1, tree2);
				H2.Binomial_queue[i] = NULL;
				break;
		}
	}
	return H1;
}



Binomial init(void)
{
	Binomial B;
	for (int i = 0; i < MAX; i++)
		B.Binomial_queue[i] = NULL;
	B.size = 0;
	return B;
}

//向队列插入，但是可以将插入看作特殊情况的合并，冗余函数
Binomial insert(int num, Binomial B)
{
	PB temp = NULL;
	int move = 0;
	
	if (B.size % 2 == 0)
	{
		B.Binomial_queue[move] = (PB)malloc(sizeof(Binomial_node));
		B.Binomial_queue[move]->first = NULL;
		B.Binomial_queue[move]->next_bro = NULL;
		B.Binomial_queue[move]->key = num;
	}
	else
	{
		temp = (PB)malloc(sizeof(Binomial_node));
		temp->key = num;
		temp->first = NULL;
		temp->next_bro = NULL;
		while (B.Binomial_queue[move])
		{
			temp = tree_mert(B.Binomial_queue[move], temp);
			free(B.Binomial_queue[move]);
			B.Binomial_queue[move] = NULL;
			move++;
		}
		B.Binomial_queue[move] = (PB)malloc(sizeof(Binomial_node));
		B.Binomial_queue[move] = temp;
	}
	B.size++;
	return B;
}

int main(void)
{
	Binomial B = init();

	B = insert(1, B);
	B = insert(3, B);
	B = insert(5, B);
	B = insert(7, B);
	B = insert(9, B);

	fprintf(stdout, "%d\n", B.size);
	fprintf(stdout, "%d\n", B.Binomial_queue[0]->key);
	fprintf(stdout, "%d\n", B.Binomial_queue[2]->key);

	return 0;
}
