/* bubble.c: Source code for bubble sort */

/* St: 2016-08-11 Thu 06:21 PM */
/* Up: 2016-08-12 Fri 09:04 PM */


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"msortlib.h"


/* 
 * Macros 
 */
#define EOPT 1  /* Error while parsing option */


/* Function prototype declarations */
void test_bbl_int(int size, char *elem[]);
void test_bbl_str(int size, char *elem[]);
void bubble_sort(void *arr, int nmemb, int size, 
		 int (*cmp)(void *, void *),
		 void (*swp) (void *, int, int));


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
		test_bbl_int(argc, argv);
	} else if (sflag == 1) {
		test_bbl_str(argc, argv);
	} else {
		fprintf(stderr, "%s: Error: No option given\n", argv[0]);
		abort();
	}

	return 0;
}

/* test_bbl_int: test bubble_sort for integer arrays
 *
 * @size: total number of command line arguments
 * @elem: array of command line arguments
 */
void test_bbl_int(int size, char *elem[])
{
	struct iarr_info *arr;

	if ((arr = crt_iarr(size - 3, elem + 3)) == NULL) {
		fprintf(stderr, "Error: Could not create array\n");
		exit(ARR_CRT_ERR);
	}

	printf("=== Before sort ===\n");
	print_iarr(arr->parr, arr->nmemb);
	bubble_sort((void *) arr->parr, arr->nmemb, arr->size, cmpi, swapi);
	printf("=== After sort ===\n");
	print_iarr(arr->parr, arr->nmemb);

	free(arr->parr);
	free(arr);
	
}


/* test_sort_str: test bubble_sort for string arrays
 *
 * @size: total number of command line arguments
 * @elem: array of command line arguments
 */
void test_bbl_str(int size, char *elem[])
{
	int i;
	struct sarr_info *arr;

	if ((arr = crt_sarr(size - 3, elem + 3)) == NULL) {
		fprintf(stderr, "Error: Could not create array\n");
		exit(ARR_CRT_ERR);
	}

	printf("=== Before sort ===\n");
	print_sarr(arr->parr, arr->nmemb);
	bubble_sort((void *) arr->parr, arr->nmemb, arr->size, cmps, swaps);
	printf("=== After sort ===\n");
	print_sarr(arr->parr, arr->nmemb);

	for (i = 0; i < arr->nmemb; i++)
		free(arr->parr[i]);
	free(arr->parr);
	free(arr);
	
}

/* bubble_sort_gen: sort an array 
 *
 * This function sorts an array of any type using bubble sort.
 * @arr: pointer to array to sort
 * @nmemb: number of members in array
 * @size: size of each member
 * @cmp: function to compare two values
 * @swp: function to swap two values
 */
void bubble_sort(void *arr, int nmemb, int size, int (*cmp)(void *, void *),
		 void (*swp) (void *, int, int))
{
	int i;
	int j;
	int swap;
	char *carr;

	carr = (char *) arr;

	for (i = 0; i < nmemb-1; i++) {
		swap = 0;
		for (j = 0; j < nmemb-1-i; j++) {
			if (cmp((void *) (carr + (j+1)*size),
			        (void *) (arr + j*size)) < 0) {
				swp((void *)carr, j, j+1);
				swap = 1;
			}
		}
		if (swap == 0)
			break;
	}
}

/* EOF */
