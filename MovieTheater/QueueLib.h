/* Bailey Brown 1001555076 */

#ifndef _QUEUELIB_H
#define _QUEUELIB_H

struct Qnode
{
	int SeatNumber;
	char SeatRow;
	struct Qnode *next_ptr;
};

void EnqueueSoldSeat(struct Qnode **, struct Qnode **, char, int);

void DequeueTickets(struct Qnode *);

#endif

