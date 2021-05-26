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

//Red Black Tree
//1. root是黑色
//2. 所有leaf都是黑色(NIL節點)
//3. 所有紅色節點的子節點都是黑色
//4. 任一節點到其leaf的所有簡單路徑都包含相同數目的黑色節點
void RB_init(struct RBnode *R)
{
	R->key = -1;
	R->rb = 'r';
	R->P = NULL;
	R->L = NULL;
	R->R = NULL;
}

void RB_Lrotate(struct RBnode *R)
{
	struct RBnode *n = R->R;
	struct RBnode *p = R->P;
	struct RBnode *r = R->R->L;
	R->R = r;
	if(r) r->P = R;
	R->P = n;
	n->L = R;
	n->P = p;
	if(p)
	{
		if(p->L == R) p->L = n;
		else p->R = n;
	}
}

void RB_Rrotate(struct RBnode *R)
{
	struct RBnode *n = R->L;
	struct RBnode *p = R->P;
	struct RBnode *l = n->R;
	R->L = l;
	if(l) l->P = R;
	R->P = n;
	n->R = R;
	n->P = p;
	if(p)
	{
		if(p->L == R) p->L = n;
		else p->R = n;
	}
}

struct RBnode *RB_insertN(struct RBnode *R, int64 key)
{
	struct RBnode *p;
	static int first = TRUE;
	if(R == NULL)
	{
		p = (struct RBnode *)malloc(sizeof(struct RBnode));
		RB_init(p);
		p->key = key;
		if(first) {p->rb = 'b'; first = FALSE;}
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
		       	q = RB_balance(p->R);
		}
		else if(rl == 'l') 
		{
			p->L = RB_insertN(p->L, key);
		       	p->L->P = p;
		       	q = RB_balance(p->L);
		}
		return q;
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
	// case2. if p->rb == black, do noting
	// case3. p->rb == red and u->rb == red
	// case4_1. p->rb == red and (u->rb == black or u == NULL) and cur == p->right and p = g->left >>>> rotate left
	// case4_2. p->rb == red and (u->rb == black or u == NULL) and cur == p->left and p = g->right >>>> rotate right
	// case5_1. p->rb == red and (u->rb == black or u == NULL) and cur == p->left and p = g->left >>>> rotate right
	// case5_2. p->rb == red and (u->rb == black or u == NULL) and cur == p->right and p = g->right >>>> rotate left
	if(N->P == NULL) {N->rb = 'b'; return N;}
	else if(N->P->rb == 'b')
	{
		struct RBnode *root = N;
		while(root->P) {root = root->P;}
		return root;
	}
	else if(N->P->rb == 'r')
	{
		struct RBnode *U;
		struct RBnode *P = N->P;
		struct RBnode *G = N->P->P;
		if(G->L == P) U = G->R;
		else U = G->L;

		if(U && U->rb == 'r')
		{
			P->rb = 'b';
			U->rb = 'b';
			G->rb = 'r';
			RB_balance(G);
		}
		else if(U == NULL || U->rb == 'b')
		{
			if(N == P->R && P == G->L)
			{
				RB_Lrotate(P);
				RB_balance(P);
			}
			else if(N == P->L && P == G->R)
			{
				RB_Rrotate(P);
				RB_balance(P);
			}
			else
			{
				if(N == P->L && P == G->L)
				{
					P->rb = 'b';
					G->rb = 'r';
					RB_Rrotate(G);
					RB_balance(N);
				}
				else if(N == P->R && P == G->R)
				{
					P->rb = 'b';
					G->rb = 'r';
					RB_Lrotate(G);
					RB_balance(N);
				}
			}
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

//AVL Tree
void AVL_init(struct AVLnode *R)
{
	R->key = -1;
	R->hCnt = 0;
	R->P = NULL;
	R->L = NULL;
	R->R = NULL;
}

struct AVLnode *AVL_Rrotate(struct AVLnode *R)
{
	struct AVLnode *n = R->L;
	struct AVLnode *p = R->P;
	struct AVLnode *l = n->R;
	R->L = l;
	if(l) l->P = R;
	R->P = n;
	n->R = R;
	n->P = p;
	if(p)
	{
		if(p->L == R) p->L = n;
		else if(p->R == R) p->R = n;
	}
	n->hCnt = 0;
	R->hCnt = 0;
	struct AVLnode *root = n;
	while(root->P) {root = root->P;}
	return root;
}

struct AVLnode *AVL_Lrotate(struct AVLnode *R)
{
	struct AVLnode *n = R->R;
	struct AVLnode *p = R->P;
	struct AVLnode *r = n->L;
	R->R = r;
	if(r) r->P = R;
	R->P = n;
	n->L = R;
	n->P = p;
	if(p)
	{
		if(p->L == R) p->L = n;
		else if(p->R == R) p->R = n;
	}
	n->hCnt = 0;
	R->hCnt = 0;
	struct AVLnode *root = n;
	while(root->P) {root = root->P;}
	return root;
}

struct AVLnode *AVL_insertN(struct AVLnode *R, int64 key)
{
	struct AVLnode *p;
	if(R == NULL)
	{
		p = (struct AVLnode *)malloc(sizeof(struct AVLnode));
		AVL_init(p);
		p->key = key;
		return p;
	}
	else
	{
		int l = FALSE, r = FALSE;
		char rl = '\0';
		struct AVLnode *cur = NULL;
		struct AVLnode *q = R;
		while(q)
		{
			p = q;
			if(key > q->key)
			{
				q = q->R;
				rl = 'r';
				p->hCnt++;
				if(abs(p->hCnt) == MAXH)
				{
					p->hCnt--;
					cur = p;
					r = TRUE;
					l = FALSE;
				}
			}
			else if(key < q->key)
			{
				q = q->L;
				rl = 'l';
				p->hCnt--;
				if(abs(p->hCnt) == MAXH)
				{
					p->hCnt++;
					cur = p;
					l = TRUE;
					r = FALSE;
				}
			}
			else return R;
		}
		struct AVLnode *root;
		if(rl == 'r') 
		{
			p->R = AVL_insertN(p->R, key);
		       	p->R->P = p;
			if(r)
			{
				root = AVL_Lrotate(cur);
			}
			else if(l)
			{
				root = AVL_Lrotate(p);
				root = AVL_Rrotate(cur);
			}
			else return R;
		}
		else if(rl == 'l') 
		{
			p->L = AVL_insertN(p->L, key);
		       	p->L->P = p;
			if(r)
			{
				root = AVL_Rrotate(p);
				root = AVL_Lrotate(cur);
			}
			else if(l)
			{
				root = AVL_Rrotate(cur);
			}
			else return R;
		}
		return root;
	}
}

struct AVLnode *AVL_findN(struct AVLnode *R, int64 key)
{
	struct AVLnode *p = R;
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

void AVL_traversalN(struct AVLnode *R)	//Postorder
{
	if(R == NULL) return;
	AVL_traversalN(R->L);
	AVL_traversalN(R->R);
	free(R);
}

void AVL_t(struct AVLnode *R)	//Inorder
{
	if(R == NULL) return;
	AVL_t(R->L);
	printf("%lld\n", R->key);
	AVL_t(R->R);
}
