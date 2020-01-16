

#include <stdio.h>
#include <stdlib.h>
#include "QueueLib.h"
#include "StackLib.h"

void PushSoldSeat(struct Snode **StackTop, char RowToAdd, int SeatToAdd)
{
    struct Snode *NewNode = malloc(sizeof(struct Snode));
    NewNode->SeatRow = RowToAdd;
	NewNode->SeatNumber = SeatToAdd;
	
	if (*StackTop == NULL)
	{
		*StackTop = NewNode;
		(*StackTop)->next_ptr = NULL;
	}
	else
	{
		NewNode->next_ptr = *StackTop;
		*StackTop = NewNode;
    }
	
}

void PopTickets(struct Snode *StackTop)
{
	if (StackTop == NULL)
	{
		printf("Pop not executed - stack is empty\n\n");
        return;
	}
	
	struct Snode *TempPtr = StackTop;
	
	while (TempPtr != NULL)
	{
		printf("______________\n");
		printf("|             |\n");
		printf("|  Seat %c%d    |\n", TempPtr->SeatRow, TempPtr->SeatNumber);
		printf("|             |\n");
		printf("______________\n\n");
		TempPtr =  TempPtr->next_ptr;
	}
	
	free(TempPtr);

	return;
}


