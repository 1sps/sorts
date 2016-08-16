/* msortlib.c: Source code for misc helper functions used while sorting */

/* Start Date:  2016-08-11 Thu 06:53 PM */
/* Last Update: 2016-08-15 Mon 11:22 PM */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"msortlib.h"


/* swapi: swap arr[i] and arr[j] of int array
 * 
 * @iarr: pointer first member of int array
 * @i: index 1
 * @j: index 2
 */
void swapi(void *iarr, int i, int j)
{
	int temp;
	int *arr;

	arr = (int *) iarr;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/* swaps: swap arr[i] and arr[j] of string array
 * 
 * @sarr: pointer first member of string array
 * @i: index 1
 * @j: index 2
 */
void swaps(void *sarr, int i, int j)
{
	char *temp;
	char **arr;

	arr = (char **) sarr;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/* cmpi: compare two integers 
 *
 * @u: pointer to first int
 * @v: pointer to seconf int
 * 
 * Return value: 
 * -1 if *u smaller than *v,  
 * 1  if *u bigger than *v,  
 * 0  if *u and *v equal  
 */
int cmpi(void *u, void *v) 
{
	int *i1;
	int *i2;

	i1 = (int *) u;
	i2 = (int *) v;

	if (*i1 < *i2)
		return -1;
	else if (*i1 > *i2)
		return 1;
	else
		return 0;
}

/* cmps: compare two strings 
 *
 * @s: pointer to first string
 * @t: pointer to seconf string
 * 
 * Return value: 
 * -1 if *s smaller than *v,  
 * 1  if *s bigger than *v,  
 * 0  if *s and *t equal  
 */
int cmps(void *s, void *t) 
{
	char **pstr1;
	char **pstr2;

	pstr1 = (char **) s;
	pstr2 = (char **) t;

	if (strcmp(*pstr1, *pstr2) < 0)
		return -1;
	else if (strcmp(*pstr1, *pstr2) > 0)
		return 1;
	else
		return 0;
}

/* crt_iarr: create a test int array 
 *
 * This function creates an array from the command lne arguments.
 * @nmemb: total number of command line arguments
 * @elem: array of pointers to command line arguments
 */
struct iarr_info *crt_iarr(size_t nmemb, char *elem[])
{
	int i;
	int *parr;
	struct iarr_info *arr;

	if (nmemb < 1)
		return NULL;	

	if ((arr = malloc(sizeof(struct iarr_info))) == NULL)
		return NULL;

	if ((parr = malloc(nmemb * sizeof(int))) == NULL)
		return NULL;

	for (i = 0; i < nmemb; i++)
		parr[i] = atoi(elem[i]);
	
	arr->parr = parr;
	arr->nmemb = i;
	arr->size = sizeof(int);
	return arr;
}

/* crt_sarr: create a test string array 
 *
 * This function creates an array of strings from the command lne arguments.
 * @nmemb: total number of command line arguments
 * @elem: array of pointers to command line arguments
 */
struct sarr_info *crt_sarr(int nmemb, char *elem[])
{
	int i;
	char **parr;
	struct sarr_info *arr;

	if (nmemb < 1)
		return NULL;	

	if ((arr = malloc(sizeof(struct sarr_info))) == NULL)
		return NULL;

	if ((parr = malloc(nmemb * sizeof(char *))) == NULL)
		return NULL;

	for (i = 0; i < nmemb; i++)
		parr[i] = strdup(elem[i]);
	
	arr->parr = parr;
	arr->nmemb = i;
	arr->size = sizeof(char *);
	return arr;
}

/* print_iarr: print int array 
 *
 * @arr: array to print
 * @nmemb: tot numbers of memb
 */
void print_iarr(int arr[], int nmemb)
{
	int i;

	if (nmemb < 0)
		return;

	i = 0;
	printf("%d", arr[i++]);
	for (; i < nmemb; i++)
		printf(" %d", arr[i]);

	printf("\n");
}

/* print_sarr: print string array 
 *
 * @arr: array to print
 * @nmemb: tot numbers of memb
 */
void print_sarr(char *arr[], int nmemb)
{
	int i;

	if (nmemb < 0)
		return;

	for (i = 0; i < nmemb; i++)
		printf("%s\n", arr[i]);
}


/* EOF */
