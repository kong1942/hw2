#include "search.h"

void errmsg(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

//Linked list
struct LL *L_insertN(struct LL *H, int64 key)
{
	//insert at head.
	struct LL *p = (struct LL *)malloc(sizeof(struct LL));
	p->key = key;
	p->next = H;
	return p;
}

struct LL *L_findN(struct LL *H, int64 key)
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
			p = q;
			if(q->key < key)
			{
				q = q->R;
				rl = 'r';
			}
			else if(q->key > key)
			{
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
	int32 hash = key % HASHNUM;
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
//1. root是黑色
//2. 所有leaf都是黑色(NIL節點)
//3. 所有紅色節點的子節點都是黑色
//4. 任一節點到其leaf的所有簡單路徑都包含相同數目的黑色節點
void init(struct RBnode *R)
{
	R->rb = 'r';
	R->P = NULL;
	R->L = NULL;
	R->R = NULL;
}

void RB_Lrotate(struct RBnode *R)
{
	struct RBnode *n = R->R;
	struct RBnode *p = R->P;
	struct RBnode *r = n->L;
	n->L = R;
	n->P = p;
	if(p)
	{
		if(p->L == R) p->L = n;
		else p->R = n;
	}
	p = n;
	n = r;
}

void RB_Rrotate(struct RBnode *R)
{
	struct RBnode *n = R->L;
	struct RBnode *p = R->P;
	struct RBnode *l = n->R;
	n->R = R;
	n->P = p;
	if(p)
	{
		if(p->L == R) p->L = n;
		else p->R = n;
	}
	p = n;
	n = l;
}

struct RBnode *RB_insertN(struct RBnode *R, int64 key)
{
	struct RBnode *p;
	if(R == NULL)
	{
		p = (struct RBnode *)malloc(sizeof(struct RBnode));
		init(p);
		p->key = key;
		return p;
	}
	else
	{
		char rl = '\0';
		struct RBnode *q = R;
		while(q)
		{
			p = q;
			if(key > q->key)
			{
				q = q->R;
				rl = 'r';
			}
			else if(key < q->key)
			{
				q = q->L;
				rl = 'l';
			}
			else return R;
		}
		if(rl == 'r')
		{
			p->R = RB_insertN(p->R, key);
			p->R->P = p;
		}
		else if(rl == 'l')
		{
			p->L = RB_insertN(p->L, key);
			p->L->P = p;
		}
		return R;
	}
}

struct RBnode *RB_findN(struct RBnode *R, int64 key)
{
	struct RBnode *p = R;
	while(p)
	{
			if(key > p->key)
				p = p->R;
			else if(key < p->key)
				p = p->L;
			else return p;
	}
	return NULL;
}

struct RBnode *RB_balance(struct RBnode *N)
{
	// P = parent node, U = uncle node, G = grandparent node
	// case1. if node == root, then rb = black
	if(N->P == NULL) {N->rb = 'b'; return N;}
	// case2. if p->rb == black, do noting
	else if(N->P->rb == 'b') return N;
	else 
	{
		struct RBnode *U;
		struct RBnode *G = N->P->P;
		if(G->L == N->P) U = G->R;
		else U = G->L;

		// case3. p->rb == red and u->rb == red
		if(N->P->rb == 'r' && U->rb == 'r')
		{
			N->P->rb = 'b';
			U->rb = 'b';
			G->rb = 'r';
			RB_balance(G);
		}
		// case4_1. p->rb == red and (u->rb == black or u == NULL) and cur == p->right and p = g->left >>>>> rotate left
		else if(N->P->rb == 'r' && (U == NULL || U->rb == 'b') && N == N->P->R && N->P == G->L)
		{
			RB_Lrotate(N->P);
			RB_balance(N->L);
		}
		// case4_2. p->rb == red and (u->rb == black or u == NULL) and cur == p->left and p = g->right >>>>> rotate right
		else if(N->P->rb == 'r' && (U == NULL || U->rb == 'b') && N == N->P->L && N->P == G->R)
		{
			RB_Rrotate(N->P);
			RB_balance(N->R);
		}
		// case5_1. p->rb == red and (u->rb == black or u == NULL) and cur == p->left and p = g->left >>>>> rotate right
		// case5_2. p->rb == red and (u->rb == black or u == NULL) and cur == p->right and p = g->right >>>>> rotate left
		else
		{
			N->P->rb = 'b';
			G->rb = 'r';
			if(N->P->rb == 'r' && (U == NULL || U->rb == 'b') && N == N->P->L && N->P == G->L)
				RB_Rrotate(G);
			else RB_Lrotate(G);
		}
	}
}

void RB_traversalN(struct RBnode *R)
{
	if(R == NULL) return;
	RB_traversalN(R->L);
	RB_traversalN(R->R);
	free(R);
}

void RB_t(struct RBnode *R)
{
	if(R == NULL) return;
	RB_t(R->L);
	printf("%lld\n", R->key);
	RB_t(R->R);
}

//AVLTree

