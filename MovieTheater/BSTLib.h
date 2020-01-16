/*Bailey Brown 1001555076*/

#ifndef _BSTLIB_H
#define _BSTLIB_H

struct Bnode
{
	char MovieTheaterName[50];
	char MovieTheaterZip[6];
	char MovieTheaterMap[26];
	struct Bnode *left, *right;
};

struct Bnode *CreateBST(struct Bnode *, char [], char [], char []);

void ListZipsInOrder(struct Bnode *);

void WriteOutNode(struct Bnode *, FILE *);

struct Bnode *SearchForMovieTheater(struct Bnode *, char []);

#endif

