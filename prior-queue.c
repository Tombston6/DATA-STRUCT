#include<stdio.h>
#include<stdlib.h>
#define MAX 101

typedef struct heap_node
{
	int heap[MAX];
	int heap_size;
}Heap;

Heap H;

Heap init(Heap H)
{
	Heap init_H = H;
	init_H.heap_size = 0;

	return init_H;
}

#堆的插入，从下一个叶子节点创建一个空结点，将插入值放入，如果破坏了堆的结构，那么就将这个空穴与父节点交换，直至不破坏堆的结构
Heap insert(Heap H, int num)
{
	Heap temp = H;
	int index;

	if (temp.heap_size == 0)
		temp.heap[++(temp.heap_size)] = num;
	else
	{
		temp.heap[++(temp.heap_size)] = num;
		for (index = temp.heap_size; index > 1; index /= 2)
		{
			if (num < temp.heap[index / 2])
				temp.heap[index] = temp.heap[index / 2];
			else
				break;
		}
		temp.heap[index] = num;
	}
	return temp;
}

#堆的删除最小值，树的顶点删除后产生一个空穴，如何堆的序列的最后一个节点放在这不破坏堆的结构，那么就完成了，但是这一般不可能，
#所以我们需要将这个空穴向下推，将其较小的结点填充到空穴，空穴就向下移动了，直至最后一个结点放置空穴不破坏空穴位置
Heap Deletemin(Heap H)
{
	Heap temp = H;

	if (temp.heap_size == 0)
		return temp;
	else
	{
		int receive = temp.heap[(temp.heap_size)--];
		int index;

		for (index = 1; index < temp.heap_size;)
		{
			if (receive <= temp.heap[index * 2] && receive <= temp.heap[index * 2 + 1])
				break;
			else
			{
				if (temp.heap[index * 2] < temp.heap[index * 2 + 1])
				{
					temp.heap[index] = temp.heap[index * 2];
					index *= 2;
				}
				else
				{
					temp.heap[index] = temp.heap[index * 2 + 1];
					index = 2 * index + 1;
				}
			}
		}
		temp.heap[index] = receive;
	}
	return temp;
}

int main(void)
{
	H = init(H);

	H = insert(H, 20);
	H = insert(H, 30);
	H = insert(H, 10);
	H = insert(H, 25);
	fprintf(stdout, "%d\n", H.heap_size);
	fprintf(stdout, "%d %d %d\n", H.heap[1], H.heap[2], H.heap[3]);
	H = Deletemin(H);
	fprintf(stdout, "%d %d %d\n", H.heap[1], H.heap[2], H.heap[3]);
	return 0;
}
