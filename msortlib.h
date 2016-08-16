/* msortlib.h: Header file for misc sort utilities */

/* St: 2016-08-11 Thu 06:46 PM */
/* Up: 2016-08-15 Mon 11:22 PM */

#ifndef MSORTLIB_H
#define MSORTLIB_H


/* #defines */

#ifndef ARR_CRT_ERR
#define ARR_CRT_ERR 1
#endif /* ARR_CRT_ERR */

#ifndef SKIP
#define SKIP
#endif /* SKIP */


/* struct that holds int array info */
struct iarr_info {
	int *parr;
	size_t nmemb;
	size_t size;
};

/* struct that holds char array info */
struct sarr_info {
	char **parr;
	size_t nmemb;
	size_t size;
};


/* Function prototype declarations */
void swapi(void *iarr, int i, int j);
void swaps(void *sarr, int i, int j);
int cmpi(void *u, void *v);
int cmps(void *s, void *t);
struct iarr_info *crt_iarr(size_t nmemb, char *elem[]);
struct sarr_info *crt_sarr(int size, char *elem[]);
void print_iarr(int arr[], int nmemb);
void print_sarr(char *arr[], int nmemb);


#endif /* MSORTLIB_H */

/* EOF */
