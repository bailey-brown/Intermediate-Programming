
#include <stdio.h>
#include <stdlib.h>
#include "QueueLib.h"

void EnqueueSoldSeat(struct Qnode **QueueHead, struct Qnode **QueueTail, char RowToAdd, int SeatToAdd)
{
    struct Qnode *TempPtr = malloc(sizeof(struct Qnode));
    TempPtr->SeatRow = RowToAdd;
	TempPtr->SeatNumber = SeatToAdd;

	/* Queue is empty */
	if (*QueueHead == NULL)
	{
		TempPtr->next_ptr = NULL;
		*QueueHead = *QueueTail = TempPtr;
	}
	else
	{
		(*QueueTail)->next_ptr = TempPtr;
		*QueueTail = TempPtr;
		(*QueueTail)->next_ptr = NULL;
	}
}

void DequeueTickets(struct Qnode *QueueHead)
{
	struct Qnode *TempPtr = QueueHead;
	
    // If queue is empty, return 0.
    if (QueueHead == NULL)
	{
		printf("Queue is emtpy\n\n");
		return;
	}

	while (TempPtr != NULL)
	{
		printf("______________\n");
		printf("|             |\n");
		printf("|  Seat %c%d    |\n", TempPtr->SeatRow, TempPtr->SeatNumber);
		printf("|             |\n");
		printf("______________\n\n");
		TempPtr =  TempPtr->next_ptr;
	}

	free(QueueHead);
	QueueHead = TempPtr;



}



