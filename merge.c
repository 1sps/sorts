/* merge.c: Source code for merge sort */

/* Start Date:  2016-08-13 Sat 02:31 PM */
/* Last Update: 2016-08-15 Mon 11:19 PM */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"msortlib.h"


/* 
 * Macros 
 */
#define EOPT 1  /* Error while parsing option */


/* Function prototype declarations */
void test_mrg_int(int size, char *elem[]);
void test_mrg_str(int size, char *elem[]);
void merge_sort(void *arr, int nmemb, int size, 
		 int (*cmp)(void *, void *),
		 void (*swp) (void *, int, int));
void *copy_arr(void *src, int nmemb, int size);
char *sorted_mrg(char *res, char *arr1, char *arr2, 
                 int nmemb1, int nmemb2, 
                 int (*cmp) (void *, void *),
		 int size);

#ifndef SKIP
/* These will be set in unistd.h. Just showing here explaining which variable
 * means what while using getopt() function. 
 */
int opterr = 1;   /* if nonzero, getopt prints error messages */
int optopt;       /* contains unknown option or option with no argument */
int optind;       /* index of next arg to be processed */
char *optarg;     /* points at the value of options argument */
char *options;    /* string that specifies option characters */
#endif /* SKIP */


/* main: test bubble sort 
 *
 * @argc: total number of command line arguments
 * @argv: array of pointers to command line arguments
 */
int main(int argc , char *argv[])
{
	int iflag;
	int sflag;
	const char *options;
	int c;
	char *cvalue;

	iflag = 0;
	sflag = 0;
	options = "is";
	opterr = 0;

	while ((c = getopt(argc, argv, options)) != -1) {
		switch (c) {
		case 'i':
			iflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		/* TODO:Opiton with argument */ 
		case 't':
			cvalue = optarg;
			fprintf(stderr, 
			        "%s: Sorry, `-t' option is not supported now\n",
				argv[0]);
			break;
		case '?':
			if (optopt == 't')
				fprintf(stderr, 
				        "%s: Error: Missing argument for -t\n",
					argv[0]);
			else
				fprintf(stderr, 
				        "%s: Error: Unknown option `-%c'.\n",
					argv[0], optopt);
			return EOPT;
		default:
			/* TODO: good way to handle this case? */
			abort();
		}
	}

	if (iflag == 1) {
		test_mrg_int(argc, argv);
	} else if (sflag == 1) {
		test_mrg_str(argc, argv);
	} else {
		fprintf(stderr, "%s: Error: No option given\n", argv[0]);
		abort();
	}

	return 0;
}

/* test_mrg_int: test merge_sort for integer arrays
 *
 * @size: total number of command line arguments
 * @elem: array of command line arguments
 */
void test_mrg_int(int size, char *elem[])
{
	struct iarr_info *arr;

	if ((arr = crt_iarr(size - 3, elem + 3)) == NULL) {
		fprintf(stderr, "Error: Could not create array\n");
		exit(ARR_CRT_ERR);
	}

	printf("=== Before sort ===\n");
	print_iarr(arr->parr, arr->nmemb);
	merge_sort((void *) arr->parr, arr->nmemb, arr->size, cmpi, swapi);
	printf("=== After sort ===\n");
	print_iarr(arr->parr, arr->nmemb);

	free(arr->parr);
	free(arr);
	
}


/* test_mrg_str: test merge_sort for string arrays
 *
 * @size: total number of command line arguments
 * @elem: array of command line arguments
 */
void test_mrg_str(int size, char *elem[])
{
	int i;
	struct sarr_info *arr;

	if ((arr = crt_sarr(size - 3, elem + 3)) == NULL) {
		fprintf(stderr, "Error: Could not create array\n");
		exit(ARR_CRT_ERR);
	}

	printf("=== Before sort ===\n");
	print_sarr(arr->parr, arr->nmemb);
	merge_sort((void *) arr->parr, arr->nmemb, arr->size, cmps, swaps);
	printf("=== After sort ===\n");
	print_sarr(arr->parr, arr->nmemb);

	for (i = 0; i < arr->nmemb; i++)
		free(arr->parr[i]);
	free(arr->parr);
	free(arr);
	
}

/* merge_sort: sort an array 
 *
 * This function sorts an array using merge sort.
 * @arr: pointer to array to sort
 * @nmemb: number of members in array
 * @size: size of each member
 * @cmp: function to compare two values
 * @swp: function to swap two values
 */
void merge_sort(void *arr, int nmemb, int size, int (*cmp)(void *, void *),
		    void (*swp) (void *, int, int))
{
	int mid;
	int left;
	int right;
	char *carr;
	char *sub1;
	char *sub2;

	right = nmemb - 1;
	left = 0;

	if (left >= right)
		return;

	carr = (char *) arr;
	mid = (left + right)/2;

	merge_sort((void *) carr, mid+1, size, cmp, swp);
	merge_sort((void *) carr + (mid+1)*size, nmemb - (mid+1),
	                  size, cmp, swp);

	if ((sub1 = (char *) copy_arr(carr, mid+1, size)) == NULL) {
		fprintf(stderr, "Error: internal copy error\n");
		return;
	}
	if ((sub2 = (char *) copy_arr(carr + (mid+1)*size, nmemb -
	     (mid+1), size)) == NULL) {
		fprintf(stderr, "Error: internal copy error\n");
		return;
	}

	if (sorted_mrg(carr, sub1, sub2, mid+1, nmemb - (mid+1), cmp, size) 
	    != carr) {
		fprintf(stderr, "Error: merge thinks sorted merge failed\n");
		free(sub1);
		free(sub2);
		abort();
	}

	free(sub1);
	free(sub2);
}

/* sorted_mrg: merge two sorted arrays 
 * 
 * @dst: pointer to result array
 * @arr1: pointer to array 1
 * @arr2: pointer to array 2
 * @nmemb1: number of members in arr1
 * @nmemb2: number of members in arr2
 * @cmp: pointer to compare function
 * @size: size of member of array
*/
char *sorted_mrg(char *res, char *arr1, char *arr2, int nmemb1, int nmemb2, 
                 int (*cmp) (void *, void *), int size)
{
	int i;
	int j;
	int k;
	int tot;
	char *tres;

	i = 0;
	j = 0;
	tot = nmemb1 + nmemb2;
	tres = res;

	for (k = 0; k < tot; k++) {
		if (i >= nmemb1) {
			if ((char *) memcpy((void *) res, (void *) arr2, size)
			    != res) {
				fprintf(stderr, "Error: memcpy error\n");
				return NULL;
			}
			arr2 += size;
		} else if (j >= nmemb2) {
			if ((char *) memcpy((void *) res, (void *) arr1, size)
			    != res) {
				fprintf(stderr, "Error: memcpy error\n");
				return NULL;
			}
			arr1 += size;
		} else {
			if (cmp((void *) arr1, (void *) arr2) < 0) {
				if ((char *) memcpy((void *) res,
				                    (void *) arr1, size) 
						    != res) {
					fprintf(stderr, "Error: memcpy error\n");
					return NULL;
				}
				arr1 += size;
				i++;
			} else {
				if ((char *) memcpy((void *) res,
				                    (void *) arr2, size) 
						    != res) {
					fprintf(stderr, "Error: memcpy error\n");
					return NULL;
				}
				arr2 += size;
				j++;
			}
		}
		res += size;
	}
	return tres;
}

/* copy_arr: make a copy of an array 
 *
 * @src: pointer to source array
 * @nmemb: total members in array
 * @size: size of each member in array
 */
void *copy_arr(void *src, int nmemb, int size)
{
	char *dst;

	if ((dst = malloc(nmemb * size)) == NULL)
		return NULL;
	
	if ((char *) (memcpy((void *)dst, src, nmemb * size)) != dst) {
		/* TODO: free right here? */
		free(dst);
		return NULL;
	}

	return (void *) dst;
}


/* EOF */
