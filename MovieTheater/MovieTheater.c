
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>
#include "QueueLib.h"
#include "StackLib.h"
#include "BSTLib.h"

#define MAX_ROWS 5
#define MAX_COLUMNS 5

void get_command_line_parameter(char *argv[], char ParamName[], char ParamValue[])
{
	int i  = 0; 
	
	while (argv[++i] != NULL)
	{
		if (!strncmp(argv[i], ParamName, strlen(ParamName)))
		{
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
		}
	}
	
	return;
}

typedef struct
{
	int SeatNumber;
	char SeatRow;
	int Sold;
} Seat;

void ReadMovieTheatre(Seat MovieTheater[MAX_ROWS][MAX_COLUMNS], char InputFileName[50], struct Bnode **root, struct Bnode **SelectedMovieTheater)
{
	char buffer[500];
	char MTName[50];
	char MTZip[5];
	char MTMap[50];
	char Zip[6];
	char Delimiters[] = "|\n";
	
	FILE *MyFile;
	MyFile = fopen(InputFileName, "r");
	
	if (MyFile == NULL)
	{
		perror("fopen() failed ");
		exit(0);
	}
	
	while(fgets(buffer, sizeof(buffer), MyFile))
	{
		strcpy(MTName, strtok(buffer, Delimiters));
		strcpy(MTZip, strtok(NULL, Delimiters));
		strcpy(MTMap, strtok(NULL, Delimiters));
		
		*root = CreateBST(*root, MTName, MTZip, MTMap);
	}
	
	fclose(MyFile);
	
	printf("\n\nMovie Theater Search - Please enter the zip code to search for\n\n");
	
	do{
		ListZipsInOrder(*root);
		
		printf("\nZip? ");
		fgets(Zip, sizeof(Zip), stdin);
		Zip[sizeof(Zip)-1] = '\0';
		getchar();
	
		if(!SearchForMovieTheater(*root, Zip))
		{
			printf("Zip %s not found. Please enter zip from list.\n\n", Zip);
			continue;
		}
	} while(!SearchForMovieTheater(*root, Zip));
	
	*SelectedMovieTheater = SearchForMovieTheater(*root, Zip);
	
	printf("\n\nPlease choose your seats at the\n'%s' Movie Theater\n", (*SelectedMovieTheater)->MovieTheaterName);
	printf("located in zip code %s\n", (*SelectedMovieTheater)->MovieTheaterZip);
	
	int i,j,c = 0;
	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			int a = (*SelectedMovieTheater)->MovieTheaterMap[c] - '0';
			MovieTheater[i][j].Sold = a;
			c++;
		}
	}

}

void WriteMovieTheatre(Seat MovieTheatre[MAX_ROWS][MAX_COLUMNS], char OutputFilename[50], struct Bnode *root, struct Bnode *SelectedMovieTheater)
{
	char buffer[500];
	
	FILE *MyFile;
	MyFile = fopen(OutputFilename, "w");
	
	if (MyFile == NULL)
	{
	perror("fopen() failed ");
		exit(0);
	}
	
	int i,j,c;
	for(i=0; i<MAX_ROWS; i++)
	{
		for(j=0; j<MAX_COLUMNS; j++)
		{
			SelectedMovieTheater->MovieTheaterMap[c] = MovieTheatre[i][j].Sold + '0';
			c++;
		}
	}
	
	WriteOutNode(root, MyFile);
	
	fclose(MyFile);
	
}

int SeatAvailable(Seat *Seatptr)
{
	return Seatptr->Sold;
}

void SellSeat(Seat *Seatptr)
{
	Seatptr->Sold=1;
}

void PrintSeatMap(Seat MovieTheater[MAX_ROWS][MAX_COLUMNS])
{
	int i, j, c;
	
	printf("\n\n");
	printf("\t X - Sold \t O - Available\n\n");
	
	for(c=0; c<MAX_COLUMNS; c++)
		printf("\tSeat %d", c+1);
	
	printf("\n");
	
	for(i=0; i<MAX_ROWS; i++)
	{
		printf("Row %c\t", i+'A');
		
		for(j=0; j<MAX_COLUMNS; j++)
		{
			
			if(MovieTheater[i][j].Sold == 0)
				printf("O\t");
			else
				printf("X\t");
			
		}
		
		printf("\n");
	
	}
	
	printf("\n");
}

int main(int argc, char *argv[])
{
	char arg_value[100];
	char InputFileName[20] = {};
	char OutputFilename[20] = {};
	char PrintType[10] = {};
	Seat MovieTheater[MAX_ROWS][MAX_COLUMNS];
	int NumberOfTickets;
	char Input[5];
	char Row;
	int ArrayRow;
	int SeatNumber;
	int ArrayCol;
	struct Qnode *QueueHead = NULL;
	struct Qnode *QueueTail = NULL; 
	struct Snode *StackTop = NULL; 
	struct Bnode *root = NULL;
	struct Bnode *SelectedMovieTheater = NULL;
	
	//First command line argument can either by 'PRINTTYPE=QUEUE' or 'PRINTTYPE=STACK'. Any input that isn't queue will automatically be stack
	get_command_line_parameter(argv, "PRINTTYPE=", arg_value);
	strcpy(PrintType, arg_value);
	
	//Second command line argument in this case is 'INPUTFILENAME=EmptyMovieTheater.txt'
	get_command_line_parameter(argv, "INPUTFILENAME=", arg_value);
	strcpy(InputFileName, arg_value);
	
	//Can have any .txt file name
	get_command_line_parameter(argv, "OUTPUTFILENAME=", arg_value);
	strcpy(OutputFilename, arg_value);
	
	ReadMovieTheatre(MovieTheater, InputFileName, &root, &SelectedMovieTheater);
	
	PrintSeatMap(MovieTheater);
	
	printf("\nHow many movie tickets do you want to buy? ");
	scanf("%d", &NumberOfTickets);
	getchar();
	
	int i;
	for(i=0; i<NumberOfTickets; i++)
	{
		do
		{
			printf("\nPick a seat (Row Seat) ");
			fgets(Input, sizeof(Input), stdin);
			Input[strlen(Input)-1] = '\0';
			
			Row = toupper(Input[0]);
			SeatNumber = atoi(&Input[1]);

		
			ArrayRow = Row-'A';
			ArrayCol = SeatNumber-1;
		
			if(ArrayRow>=MAX_ROWS || ArrayRow<0 || ArrayCol>=MAX_COLUMNS || ArrayCol<0)
				printf("\nThat is not a valid seat. Please choose again \n");
		
		}
		while(ArrayRow>=MAX_ROWS || ArrayRow<0 || ArrayCol>=MAX_COLUMNS || ArrayCol<0);
		

		do
		{
			
			if(!SeatAvailable(&MovieTheater[ArrayRow][ArrayCol]))
			{
				SellSeat(&MovieTheater[ArrayRow][ArrayCol]);
				
				if(strcmp(PrintType, "QUEUE") == 0)
					EnqueueSoldSeat(&QueueHead, &QueueTail, Row, SeatNumber);
				else
					PushSoldSeat(&StackTop, Row, SeatNumber);
				
				PrintSeatMap(MovieTheater);
			}
			
			else
			{
				printf("\nSeat %c - %d is not available\n", Row, SeatNumber);
				PrintSeatMap(MovieTheater);
				i--;
			}
		}
		while(!SeatAvailable(&MovieTheater[ArrayRow][ArrayCol]));
	}
	
	printf("Here's your tickets for %s. Enjoy your show!\n\n", SelectedMovieTheater->MovieTheaterName);
	
	if(strcmp(PrintType, "QUEUE") == 0)
		DequeueTickets(QueueHead);
	else
		PopTickets(StackTop);

	
	WriteMovieTheatre(MovieTheater, OutputFilename, root, SelectedMovieTheater);
}




