#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

enum status{EMPTY, RESTRICT};
typedef struct hash_node
{
	int key;
	int count;
	int hash;
	enum status info;
}Hash_node;
typedef Hash_node* pHash_node;

pHash_node hash_table[MAX];

void init(void)
{
	for (int i = 0; i < MAX; i++)
		hash_table[i] = (pHash_node)malloc(sizeof(Hash_node));
}

int hash_func(int num)
{
	return (++num) * num;
}

int find(int num)
{
	int i = 1;
	int index = num % (MAX + 1) - 1;

	while (hash_table[index]->info == RESTRICT && hash_table[index]->key != num)
	{
		index = index + hash_func(i) - 1;
		if (index > MAX)
			index -= MAX;
	}
	return index;
}

void insert(int num)
{
	int posion = find(num);

	if (hash_table[posion]->key == num)
		hash_table[posion]->count++;
	else
	{
		hash_table[posion]->key = num;
		hash_table[posion]->hash = num % (MAX + 1);
		hash_table[posion]->count = 1;
		hash_table[posion]->info = RESTRICT;
	}
}

int main(void)
{
	init();
	insert(3);
	insert(6);
	insert(1004);
	fprintf(stdout, "key = %d, hash = %d, count = %d\n", hash_table[find(3)]->key, hash_table[find(3)]->hash, hash_table[find(3)]->count);
	fprintf(stdout, "key = %d, hash = %d, count = %d\n", hash_table[find(6)]->key, hash_table[find(6)]->hash, hash_table[find(6)]->count);
	fprintf(stdout, "key = %d, hash = %d, count = %d\n", hash_table[find(1004)]->key, hash_table[find(1004)]->hash, hash_table[find(1004)]->count);

	return 0;
}
