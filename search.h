#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#define HASHNUM 997
#define int32 unsigned int
#define int64 long long
#define TRUE 1
#define FALSE 0

void errmsg(char *str);

//Linked list
struct LL
{
	int64 key;
	struct LL *next;
};
struct LL *L_insertN(struct LL *H, int64 key);  //insert at tail.
struct LL *L_findN(struct LL *H, int64 key);
void L_traversalN(struct LL *H);
void L_t(struct LL *H);

//Array
struct ARR
{
	int64 key;
};
void A_insertN(struct ARR *T, int64 key);
struct ARR *A_findN(struct ARR *H, int64 key, int32 size);
void A_t(struct ARR *H, int32 size);

//Array with Binary Search
struct ABS
{
	int64 key;
};
int cmpN(const void *a, const void *b);
void ABS_insertN(struct ABS *T, int64 key);
struct ABS *ABS_findN(struct ABS *H, int64 key, int32 size);
void ABS_t(struct ABS *H, int32 size);

//Binary Search Tree
struct BST
{
	int64 key;
	struct BST *L;
	struct BST *R;
};
struct BST *T_insertN(struct BST *R, int64 key);
struct BST *T_findN(struct BST *R, int64 key);
void T_traversalN(struct BST *R); //Postorder
void T_t(struct BST *R); //Inorder

//Hash
int32 H_hashN(int64 key);
void H_insertN(struct LL **hTab, int64 key);
struct LL *H_findN(struct LL **hTab, int64 key);
void H_traversalN(struct LL **hTab);
void H_t(struct LL **hTab);

//RBT
struct RBnode
{
	int64 key;
	char rb;
	struct RBnode *P;
	struct RBnode *L;
	struct RBnode *R;
};
void init(struct RBnode *R);
void RB_Lrotate(struct RBnode *R);
void RB_Rrotate(struct RBnode *R);
struct RBnode *RB_insertN(struct RBnode *R, int64 key);
struct RBnode *RB_findN(struct RBnode *R, int64 key);
struct RBnode *RB_balance(struct RBnode *N);
void RB_traversalN(struct RBnode *R);	//Postorder
void RB_t(struct RBnode *R);	//Inorder

//AVLT
struct AVLnode
{

};

//B+T
struct Bnode
{

};
