/* Bailey Brown 1001555076 */

#ifndef _STACKLIB_H
#define _STACKLIB_H

struct Snode
{ 
	int SeatNumber;
	char SeatRow;
	struct Snode *next_ptr;
};

void PushSoldSeat(struct Snode **, char, int);

void PopTickets(struct Snode *);

#endif

