#include "search.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	FILE *fp;
	int fileOK = FALSE;
	int32 num_of_data, num_of_query, upper;

	if(argc < 2) errmsg("Input error");
	else if(!strcmp(argv[1], "-d"))
	{
		if(argc < 3) errmsg("Set data error");
		else if(!strcmp(argv[2], "1e4"))
		{
			num_of_data = 1e4;
			if(fp = fopen("data1", "r"))
				fileOK = TRUE;
			else fp = fopen("data1", "w+");
		}
		else if(!strcmp(argv[2], "1e5"))
		{
			num_of_data = 1e5;
			if(fp = fopen("data2", "r"))
				fileOK = TRUE;
			else fp = fopen("data2", "w+");
		}
		else if(!strcmp(argv[2], "1e6"))
		{
			num_of_data = 1e6;
			if(fp = fopen("data3", "r"))
				fileOK = TRUE;
			else fp = fopen("data3", "w+");
		}
		else errmsg("Data number error");
	}
	else errmsg("Set data error");

	if(!fileOK)
	{
		int64 *arr = (int64 *)malloc(sizeof(int64) * num_of_data);
		memset(arr, 0, sizeof(int64) * num_of_data);

		for(int32 i=0; i<num_of_data; i++)
		{
			arr[i] = rand();
			for(int32 j=0; j<i; j++)
				if(arr[j] == arr[i])
				{
					arr[i]++;
					j=0;
				}
			fprintf(fp, "%lld\n", arr[i]);
		}
		free(arr);
	}
		
	FILE *fp2;
	fileOK = FALSE;

	if(argc < 4) errmsg("Query error");
	else if(!strcmp(argv[3], "-q"))
	{
		if(argc < 5) errmsg("Set query error");
		else if(!strcmp(argv[4], "1e3"))
		{
			num_of_query = 1e3;
			if(fp2 = fopen("query1", "r"))
				fileOK = TRUE;
			else fp2 = fopen("query1", "w+");
		}
		else if(!strcmp(argv[4], "1e4"))
		{
			num_of_query = 1e4;
			if(fp2 = fopen("query2", "r"))
				fileOK = TRUE;
			else fp2 = fopen("query2", "w+");
		}
		else if(!strcmp(argv[4], "1e5"))
		{
			num_of_query = 1e5;
			if(fp2 = fopen("query3", "r"))
				fileOK = TRUE;
			else fp2 = fopen("query3", "w+");
		}
		else errmsg("Query number error");
	}
	else errmsg("Set query error");

	if(!fileOK)
	{
		srand(time(NULL));
		for(int32 i=0; i<num_of_query; i++)
			fprintf(fp2, "%d\n", rand());
	}
	
	int64 num;
	double idiff, qdiff;
	struct timeval istart, iend, qstart, qend;
	
	if(argc < 6) errmsg("Set Data Structure error");
	for(int i=5; i<argc; i++)
	{
		fseek(fp, 0, SEEK_SET);
		fseek(fp2, 0, SEEK_SET);
		if(!strcmp(argv[i], "-ll"))
		{
			struct LL *head = NULL;
			struct LL *find = NULL;

			gettimeofday(&istart, NULL);
			while(fscanf(fp, "%lld", &num) != EOF)
			{
				head = L_insertN(head, num);
			}
			gettimeofday(&iend, NULL);
			idiff = (double) (1000000 * (iend.tv_sec - istart.tv_sec) + iend.tv_usec - istart.tv_usec)/1000000;
			
			gettimeofday(&qstart, NULL);

			while(fscanf(fp2, "%lld", &num) != EOF)
			{
				find = L_findN(head, num);
			}
			gettimeofday(&qend, NULL);
			qdiff = (double) (1000000 * (qend.tv_sec - qstart.tv_sec) + qend.tv_usec - qstart.tv_usec)/1000000;
			
			printf("ll:\nbuilding time:\t%f sec\nquery time:\t%f sec\n", idiff, qdiff);
//			L_t(head);
			L_traversalN(head);
		}
		else if(!strcmp(argv[i], "-arr"))
		{
			struct ARR *head = (struct ARR *)malloc(sizeof(struct ARR) * num_of_data);
			struct ARR *find = NULL;
			int32 j=0;

			gettimeofday(&istart, NULL);
			while(fscanf(fp, "%lld", &num) != EOF && j < num_of_data)
			{
				A_insertN(&head[j], num);
				j++;
			}
			gettimeofday(&iend, NULL);
			idiff = (double) (1000000 * (iend.tv_sec - istart.tv_sec) + iend.tv_usec - istart.tv_usec)/1000000;
			
			gettimeofday(&qstart, NULL);
			
			while(fscanf(fp2, "%lld", &num) != EOF)
			{
				find = A_findN(head, num, num_of_data);
			}
			gettimeofday(&qend, NULL);
			qdiff = (double) (1000000 * (qend.tv_sec - qstart.tv_sec) + qend.tv_usec - qstart.tv_usec)/1000000;

			printf("arr:\nbuilding time:\t%f sec\nquery time:\t%f sec\n", idiff, qdiff);
//			A_t(head, num_of_data);
			free(head);
		}
		else if(!strcmp(argv[i], "-bs"))
		{
			struct ABS *head = (struct ABS *)malloc(sizeof(struct ABS) * num_of_data);
			struct ABS *find = NULL;
			int32 j=0;
		
			gettimeofday(&istart, NULL);
			while(fscanf(fp, "%lld", &num) != EOF && j < num_of_data)
			{
				ABS_insertN(&head[j], num);
				j++;
			}
			qsort(head, num_of_data, sizeof(int64), cmpN);
			gettimeofday(&iend, NULL);
			idiff = (double) (1000000 * (iend.tv_sec - istart.tv_sec) + iend.tv_usec - istart.tv_usec)/1000000;
			
			gettimeofday(&qstart, NULL);
			while(fscanf(fp2, "%lld", &num) != EOF)
			{
				find = ABS_findN(head, num, num_of_data);
			}
			gettimeofday(&qend, NULL);
			qdiff = (double) (1000000 * (qend.tv_sec - qstart.tv_sec) + qend.tv_usec - qstart.tv_usec)/1000000;

			printf("bs:\nbuilding time:\t%f sec\nquery time:\t%f sec\n", idiff, qdiff);
//			ABS_t(head, num_of_data);
			free(head);
		}
		else if(!strcmp(argv[i], "-bst"))
		{
			struct BST *root = NULL;
			struct BST *find = NULL;
			
			gettimeofday(&istart, NULL);
			while(fscanf(fp, "%lld", &num) != EOF)
			{
				root = T_insertN(root, num);
			}
			gettimeofday(&iend, NULL);
			idiff = (double) (1000000 * (iend.tv_sec - istart.tv_sec) + iend.tv_usec - istart.tv_usec)/1000000;
			
			gettimeofday(&qstart, NULL);
			while(fscanf(fp2, "%lld", &num) != EOF)
			{
				find = T_findN(root, num);
			}
			gettimeofday(&qend, NULL);
			qdiff = (double) (1000000 * (qend.tv_sec - qstart.tv_sec) + qend.tv_usec - qstart.tv_usec)/1000000;
			
			printf("bst:\nbuilding time:\t%f sec\nquery time:\t%f sec\n", idiff, qdiff);
//			T_t(root);
			T_traversalN(root);
		}
		else if(!strcmp(argv[i], "-hash"))
		{
			struct LL **hTab = (struct LL **)malloc(sizeof(struct LL *) * HASHNUM);
			struct LL *find = NULL;
			for(int32 i=0; i<HASHNUM; i++)
				hTab[i] = NULL;

			gettimeofday(&istart, NULL);
			while(fscanf(fp, "%lld", &num) != EOF)
			{
				H_insertN(hTab, num);
			}
			gettimeofday(&iend, NULL);
			idiff = (double) (1000000 * (iend.tv_sec - istart.tv_sec) + iend.tv_usec - istart.tv_usec)/1000000;

			gettimeofday(&qstart, NULL);
			while(fscanf(fp2, "%lld", &num) != EOF)
			{
				find = H_findN(hTab, num);
			}
			gettimeofday(&qend, NULL);
			qdiff = (double) (1000000 * (qend.tv_sec - qstart.tv_sec) + qend.tv_usec - qstart.tv_usec)/1000000;

			printf("hash:\nbuilding time:\t%f sec\nquery time:\t%f sec\n", idiff, qdiff);
//			H_t(hTab);
			H_traversalN(hTab);
		}
		
		else if(!strcmp(argv[i], "-rbt"))
		{
			struct RBnode *root = NULL;
			struct RBnode *find = NULL;
			
			gettimeofday(&istart, NULL);
			while(fscanf(fp, "%lld", &num) != EOF)
			{
				root = RB_insertN(root, num);
				root = RB_balance(root);
			}
			gettimeofday(&iend, NULL);
			idiff = (double) (1000000 * (iend.tv_sec - istart.tv_sec) + iend.tv_usec - istart.tv_usec)/1000000;
			
			gettimeofday(&qstart, NULL);
			while(fscanf(fp2, "%lld", &num) != EOF)
			{
				find = RB_findN(root, num);
			}
			gettimeofday(&qend, NULL);
			qdiff = (double) (1000000 * (qend.tv_sec - qstart.tv_sec) + qend.tv_usec - qstart.tv_usec)/1000000;
			
			printf("rbt:\nbuilding time:\t%f sec\nquery time:\t%f sec\n", idiff, qdiff);
//			RB_t(root);
			RB_traversalN(root);
		}
		/*
		else if(!strcmp(argv[i], "-avlt"))
		{
		
		}
		*/
		else errmsg("Data Structure error");
		printf("\n");
	}
	fclose(fp);
	fclose(fp2);

	return 0;
}
