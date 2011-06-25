#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MatrixDef.h"


/* #define DEBUG_HEAPSORT */

#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#ifndef DEBUG_HEAPSORT
#define DEBUG_PARM __attribute__((unused))
#else
#define DEBUG_PARM 
#endif
#else
#define UNUSED
#define DEBUG_PARM
#endif

#define HSMAXX 26
#define HS_USE_MALLOC 0

struct heap {
	unsigned char *a;
	unsigned char n; /* length of array */
	unsigned char hsize; /* size of heap */
};

#if !HS_USE_MALLOC
static unsigned char hsarray[HSMAXX];
#endif

static void initialize_heap(struct heap *h, int n, int ydim)
{
	int i;

#if HS_USE_MALLOC
	h->a = malloc(sizeof(h->a[0]) * n);
	h->a--; /* make it a 1 based array to make heapsort easier */
#else
	h->a = &hsarray[0];
#endif
	for (i = 1; i <= n; i++)
		h->a[i] = (unsigned char) rand() % ydim;
	h->n = n;
	h->hsize = n;
}

#if HS_USE_MALLOC
static void free_heap(struct heap *h)
{
	h->a++; /* back to zero based before freeing */
	free(h->a);
}
#else
static void free_heap(UNUSED struct heap *h)
{
}
#endif

static void print_heap(DEBUG_PARM char *title, DEBUG_PARM struct heap *h)
{
#ifdef DEBUG_HEAPSORT
	int i;

	printf("%s\n", title);
	for (i = 1; i <= h->n; i++)
		printf("%d\n", h->a[i]);
#endif
}

static void exchange(struct heap *h, int x, int y)
{
	unsigned char tmp[sizeof(h->a[0])];
	memcpy(tmp, &h->a[x], sizeof(h->a[x]));
	h->a[x] = h->a[y];
	memcpy(&h->a[y], tmp, sizeof(h->a[y]));
}

static int length(struct heap *h)
{
	return h->n;
}

static int heapsize(struct heap *h)
{
	return h->hsize;
}

#if 0
static int parent(int i)
{
	return i / 2;
}
#endif

int left(int i)
{
	return 2 * i;
}

static int right(int i)
{
	return 2 * i + 1;
}

static void max_heapify(struct heap *h, int i)
{
	int l, r, largest;

	l = left(i);
	r = right(i);

	if (l <= heapsize(h) &&
		h->a[l] > h->a[i])	
		largest = l;
	else
		largest = i;

	if (r <= heapsize(h) && 
		h->a[r] > h->a[largest])
		largest = r;

	if (largest != i) {
		exchange(h, i, largest);
		max_heapify(h, largest);
	} 
}

static void build_max_heap(struct heap *h)
{
	int i;

	h->hsize = heapsize(h);
	for (i = length(h) / 2; i >= 1; i--)
		max_heapify(h, i);
}

static void heap_sort(struct heap *h)
{
	int i;

	build_max_heap(h);
	for (i = heapsize(h); i >= 1; i--) {
		exchange(h, 1, i);
		h->hsize = heapsize(h) - 1;
		max_heapify(h, 1);
		displayList((char *) h->a, length(h));
	}
}

static void heapsort(int xdim, int ydim, int seed)
{
	struct heap h;

	if (xdim > HSMAXX - 1)
		xdim = HSMAXX - 1;

	srand(seed);
	initialize_heap(&h, xdim, ydim);
	print_heap("before sorting:", &h);
	heap_sort(&h);
	print_heap("after sorting:", &h);
	free_heap(&h);
	return;
}

