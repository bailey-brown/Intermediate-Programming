/*Bailey Brown 1001555076 */

#include <stdio.h>
#include <string.h>
#include "SockLib.h"

int SockColorCompare(const void *a, const void *b)
{
	return (strcmp(((SockDrawer*)a)->SockColor, ((SockDrawer*)b)->SockColor));
}

int DrawerIDCompare(const void *a, const void *b)
{
	return (((SockDrawer*)a)->DrawerID - ((SockDrawer*)b)->DrawerID);
}

int NumberOfSocksCompare(const void *a, const void *b)
{
	return (((SockDrawer*)a)->NumberOfSocks - ((SockDrawer*)b)->NumberOfSocks);
}

int MaxCapacityCompare(const void *a, const void *b)
{
	return (((SockDrawer*)a)->MaxDrawerCapacity - ((SockDrawer*)b)->MaxDrawerCapacity);
}

