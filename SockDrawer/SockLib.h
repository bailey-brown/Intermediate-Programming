/* Bailey Brown 1001555076 */

#include <stdio.h>

#ifndef _SOCKLIB_H
#define _SOCKLIB_H

typedef struct
{
	int DrawerID;
	int NumberOfSocks;
	char SockColor[10];
	int MaxDrawerCapacity;
} SockDrawer;

int SockColorCompare(const void *, const void *);

int DrawerIDCompare(const void *, const void *);

int NumberOfSocksCompare(const void *, const void *);

int MaxCapacityCompare(const void *, const void *);

#endif


