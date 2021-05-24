#include "search.h"

void errmsg(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

//Linked list
struct LL *L_insertN(struct LL *H, long long key)
{
	//insert at head.
	struct LL *p = (struct LL *)malloc(sizeof(struct LL));
	p->key = key;
	p->next = H;
	return p;
}

struct LL *L_findN(struct LL *H, long long key)
{
	struct LL *p = H;
	while(p)
	{
		if(p->key != key) p = p->next;
		else return p;
	}
	return NULL;
}

void L_traversalN(struct LL *H)
{
	struct LL *p = H;
	struct LL *q;
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
}

void L_t(struct LL *H)
{
	struct LL *p = H;
	while(p)
	{
		printf("%lld\n", p->key);
		p = p->next;
	}
}

//Array
void A_insertN(struct ARR *T, int64 key)
{
	T->key = key;
}

struct ARR *A_findN(struct ARR *H, int64 key, int32 size)
{
	for(int32 i=0; i<size; i++)
	{
		if(H[i].key != key) continue;
		else return &H[i];
	}
}

void A_t(struct ARR *H, int32 size)
{
	for(int32 i=0; i<size; i++)
	{
		printf("%lld\n", H[i].key);
	}
}

//Array with Binary Search
int cmpN(const void *a, const void *b)
{
	return (*(int64 *)a - *(int64 *)b);
}

void ABS_insertN(struct ABS *T, int64 key)
{
	T->key = key;
}

struct ABS *ABS_findN(struct ABS *H, int64 key, int32 size)
{
	int32 head = 0, tail = size, find;

	while(tail - head > 1)
	{
		find = (tail+head)/2;
		if(key > H[find].key)
			head = find;
		else if(key < H[find].key)
			tail = find;
		else return &H[find];
	}
	if(find == head)
		if(H[tail].key == key) return &H[tail];
	else if(find == tail)
		if(H[head].key == key) return &H[head];
	return NULL;
}

void ABS_t(struct ABS *H, int32 size)
{
	for(int32 i=0; i<size; i++)
	{
		printf("%lld\n", H[i].key);
	}
}

//Binary Search Tree
struct BST *T_insertN(struct BST *R, int64 key)
{
	struct BST *p;
	if(R == NULL)
	{
		p = (struct BST *)malloc(sizeof(struct BST));
		p->key = key;
		p->L = NULL;
		p->R = NULL;
		return p;
	}
	else
	{
		char rl = '\0';
		struct BST *q;
		q = R;
		while(q)
		{
			if(q->key < key)
			{
				p = q;
				q = q->R;
				rl = 'r';
			}
			else if(q->key > key)
			{
				p = q;
				q = q->L;
				rl = 'l';
			}
			else return R;
		}
		if(rl == 'r') p->R = T_insertN(p->R, key);
		else if(rl == 'l') p->L = T_insertN(p->L, key);
		return R;
	}
}

struct BST *T_findN(struct BST *R, int64 key)
{
	struct BST *p = R;
	while(p)
	{	
		if(p->key < key)
		{
			p = p->R;
		}
		else if(p->key > key)
		{
			p = p->L;
		}
		else return p;
	}
}

void T_traversalN(struct BST *R)
{
	//Postorder
	if(R == NULL) return;
	T_traversalN(R->L);
	T_traversalN(R->R);
	free(R);
}

void T_t(struct BST *R)
{
	//Inorder
	if(R == NULL) return;
	T_t(R->L);
	printf("%lld\n", R->key);
	T_t(R->R);
}

//Hash
int32 H_hashN(int64 key)
{
	int32 hash = key % 64;
	return hash;
}

void H_insertN(struct LL **hTab, int64 key)
{
	int32 hash = H_hashN(key);
	hTab[hash] = L_insertN(hTab[hash], key);
}

struct LL *H_findN(struct LL **hTab, int64 key)
{
	int32 hash = H_hashN(key);
	struct LL *p = hTab[hash];
	while(p)
	{
		if(p->key != key) p = p->next;
		else return p;
	}
	return NULL;
}

void H_traversalN(struct LL **hTab)
{
	struct LL *p;
	struct LL *q;
	for(int32 i=0; i<HASHNUM; i++)
	{
		q = hTab[i];
		while(q)
		{
			p = q;
			q = q->next;
			free(p);
		}
	}
}

void H_t(struct LL **hTab)
{
	struct LL *p;
	for(int32 i=0; i<HASHNUM; i++)
	{
		p = hTab[i];
		while(p)
		{
			printf("%lld\n", p->key);
			p = p->next;
		}
	}
}

//RBTree


//AVLTree

