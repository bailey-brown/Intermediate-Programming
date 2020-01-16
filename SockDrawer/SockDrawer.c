
#include <stdio.h>
#include <string.h>
#include "SockLib.h"

int NumDrawers;

int GetNumDrawers()
{
	do
	{
		printf("How many drawers does your dresser have? (1-10)  ");
		scanf("%d", &NumDrawers);
		
		if(NumDrawers==0)
			return 0;
		
		else if(NumDrawers<1 || NumDrawers>10)
		{
			printf("Number of Drawers must be between 1 and 10\n");
			printf("Please re-enter\n");
		}
	}
	while(NumDrawers<1 || NumDrawers>10);
	
	return 1;
}

	


void DisplayMyDresser(SockDrawer Dresser[])
{
	printf("\n\nMy Dresser\n\n"); 
	
	int i;
	for(i=0;i<NumDrawers;i++)
	{
		printf("Drawer %d has\t", Dresser[i].DrawerID); 
		printf("%d %s socks\t", Dresser[i].NumberOfSocks, Dresser[i].SockColor);
		printf("and can hold up to\t");
		printf("%d socks\n", Dresser[i].MaxDrawerCapacity);
	}
	
	
}

void PutAwayMySocks(SockDrawer Dresser[])
{
	int DrawerID;
	int HowMany;
	
	printf("\nWhich Drawer are you putting socks into?  ");
	scanf("%d", &DrawerID);
	DrawerID--;
	
	if(DrawerID<0 || DrawerID>=NumDrawers)
	{
		printf("Thats not one of your drawers!\n");
		return;
	}
	
	printf("\nHow many socks are you putting away?  ");
	scanf("%d", &HowMany);
	
	if((HowMany+Dresser[DrawerID].NumberOfSocks)>Dresser[DrawerID].MaxDrawerCapacity)
	{
		printf("%d socks fit in the drawer", (Dresser[DrawerID].MaxDrawerCapacity)-(Dresser[DrawerID].NumberOfSocks));
		printf(" and %d fell on the floor\n", HowMany-((Dresser[DrawerID].MaxDrawerCapacity)-(Dresser[DrawerID].NumberOfSocks)));
		
		(Dresser[DrawerID].NumberOfSocks)=(Dresser[DrawerID].MaxDrawerCapacity);
	}
	else
	{
		(Dresser[DrawerID].NumberOfSocks)+=HowMany;
	}
}

void PutOnMySocks(SockDrawer Dresser[])
{
	int DrawerID;
	int HowMany;
	
	printf("\nWhich drawer do you want to get socks from?  ");
	scanf("%d", &DrawerID);
	DrawerID--;
	
	if(DrawerID<0 || DrawerID>=NumDrawers)
	{
		printf("That's not one of your drawers!\n");
		return;
	}
	
	printf("\nHow many socks are you getting out?  ");
	scanf("%d", &HowMany);
	
	if(HowMany>(Dresser[DrawerID].NumberOfSocks))
	{
		printf("You dont have that many socks!! You can only get %d socks.\n", Dresser[DrawerID].NumberOfSocks);
		(Dresser[DrawerID].NumberOfSocks)=0;
	}
	else
	{
		(Dresser[DrawerID].NumberOfSocks)-=HowMany;
	}
}

void CreateDresser(SockDrawer *MyDresser, int DrawerID)
{
	MyDresser->DrawerID = DrawerID+1;
	
	printf("\nHow many total socks will fit in to Drawer %d?  ", MyDresser->DrawerID);
	scanf("%d", &MyDresser->MaxDrawerCapacity);
	
	printf("\nHow many socks are you putting in Drawer %d?  ", MyDresser->DrawerID);
	scanf("%d", &MyDresser->NumberOfSocks);
	getchar();
	
	if((MyDresser->NumberOfSocks)>(MyDresser->MaxDrawerCapacity))
	{
		printf("%d socks fit in the drawer", MyDresser->MaxDrawerCapacity);
		printf(" and %d fell on the floor\n", (MyDresser->NumberOfSocks)-(MyDresser->MaxDrawerCapacity));
		
		(MyDresser->NumberOfSocks)=(MyDresser->MaxDrawerCapacity);
	}
	
	printf("\nWhat color are the socks in Drawer %d?  ", MyDresser->DrawerID);
	fgets(MyDresser->SockColor, 10, stdin);
	
	MyDresser->SockColor[strlen(MyDresser->SockColor)-1]='\0';
}

void SortMySocks(SockDrawer Dresser[])
{
	int Choice;
	
	printf("\nDo you want to sort by?\n\n");
	printf("0. Changed my mind - don't want to sort\n");
	printf("1. Drawer ID?\n");
	printf("2. Number of socks in drawer?\n");
	printf("3. Max Capacity in drawer?\n");
	printf("4. Sock Color?\n\n");
	printf("Choice : ");
	scanf("%d", &Choice);
	
	int (*CompareFunctionPtrArray[4])(const void *, const void *) = {DrawerIDCompare, NumberOfSocksCompare, MaxCapacityCompare, SockColorCompare};
	
	if(Choice)
	{
		qsort(Dresser, NumDrawers, sizeof(SockDrawer), (*CompareFunctionPtrArray[Choice-1]));
	}
	else
	{
		printf("Your sock drawer is a mess!");
		return;
	}	
}
	

int main(void)
{
	enum SockAction
	{
		RemoveSocks=1,AddSocks,DisplayDresser,SortSocks
	};
	SockDrawer Dresser[10];
	int Choice;
	
	if(!GetNumDrawers())
		return 0;
	
	
	int i;
	for(i=0;i<NumDrawers;i++)
	{
		SockDrawer *Dresserptr = &Dresser[i];
		CreateDresser(Dresserptr, i);
	}
	
	do
	{
		printf("\nWhat do you need to do?\n\n");
		printf("0. Don't have socks!!\n");
		printf("1. Take socks out of a drawer\n");
		printf("2. Put more socks in a drawer\n");
		printf("3. Display dresser\n");
		printf("4. Sort Socks\n\n");
		printf("Choice : ");
		scanf("%d", &Choice);
		
		switch (Choice)
		{
			case RemoveSocks:
				PutOnMySocks(Dresser);
				DisplayMyDresser(Dresser);
				break;
			
			case AddSocks:
				PutAwayMySocks(Dresser);
				DisplayMyDresser(Dresser);
				break;
			
			case DisplayDresser:
				DisplayMyDresser(Dresser);
				break;
				
			case SortSocks:
				SortMySocks(Dresser);
				DisplayMyDresser(Dresser);
				break;
		};
		
	}
	while(Choice);
	
	printf("Time to do laundry\n\n");
	
	return 0;
	
}

