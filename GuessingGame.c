
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 81

void ConvertDecimalToBinary(int n)
{
	int i;
	int a[8];
	
	for(i=0; i<8; i++)
	{
		
		if((n & 1)==1)
			a[i]=1;
		
		else
			a[i]=0;
		
		n=n>>1;
	}
	
	for(i=7; i>=0; i--)
		printf("%d", a[i]);
}

int GuessALetter(char Phrase[], char PhraseCopy[], char UpperPhrase[])
{
	char Guess;
	char *FindGuess = NULL;
	char GuessALetterCopy[MAX_INPUT] = {};
	int FoundALetter = 0;
	int i;
	
	strcpy(GuessALetterCopy, UpperPhrase);
	
	printf("\n%s\n", PhraseCopy);
	
	printf("Player 2 : Guess a letter : ");
	scanf(" %c", &Guess);
	Guess = toupper(Guess);
	getchar();
	
	FindGuess = strchr(GuessALetterCopy, Guess);
	
	while(FindGuess != NULL)
	{
		FoundALetter = 1;
		
		PhraseCopy[FindGuess-GuessALetterCopy] = Phrase[FindGuess-GuessALetterCopy];
		
		*FindGuess = '-';
		FindGuess = strchr(GuessALetterCopy, Guess);
		
	}
	
	return FoundALetter;
	
}


int main(void)
{
	char Phrase[MAX_INPUT];
	char PhraseCopy[MAX_INPUT];
	char UpperPhrase[MAX_INPUT];
	char Alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ReplaceIt = NULL;
	int Strikes = 0;
	int YoureOut = 3;
	
	printf("\nWelcome to ");
	ConvertDecimalToBinary(YoureOut);
	printf(" STRIKES - YOU'RE OUT - the CSE version\n");
	
	printf("Player 2 - Please look away\n");
	
	printf("Player 1 - please enter the phrase that Player 2 will be guessing.\n");
	printf("Enter a maximum of %d characters.\n", MAX_INPUT-1);
	printf("Your phrase CANNOT contain a dash.\n");
	fgets(Phrase, MAX_INPUT, stdin);
	
	if(strchr(Phrase, '-') != NULL)
	{
		printf("\nYou broke the rules. We can't play. BYE!!!\n");
		exit(0);
	}
	
	Phrase[strlen(Phrase)-1] = '\0';
	
	int i;
	for(i=0; i<=strlen(Phrase); i++)
		UpperPhrase[i] = toupper(Phrase[i]);
	
	strcpy(PhraseCopy, UpperPhrase);
	
	ReplaceIt = strpbrk(PhraseCopy, Alphabet);
	while(ReplaceIt != NULL)
	{
		*ReplaceIt = '-';
		ReplaceIt = strpbrk(PhraseCopy, Alphabet);
	}
	
	printf("\nPlayer 2 - Here's the phrase you need to guess.\n");
	
	do
	{
		if(GuessALetter(Phrase, PhraseCopy, UpperPhrase) == 0)
		{
			Strikes++;
		
			printf("Strikes ");
			ConvertDecimalToBinary(Strikes);
			printf("\n");
		
			if(Strikes>=YoureOut)
			{
				printf("\n");
				ConvertDecimalToBinary(Strikes);
				printf(" STRIKES - YOU'RE OUT!!\n");
				printf("Game over\n");
			
				return 0;
			}
		
		}
	}
	while(strchr(PhraseCopy, '-') != NULL);
	
	
	
	printf("\nYou figured it out!!\n");
	printf("Player 1 entered the phrase\n");
	printf("%s\n", Phrase);
	printf("Player 2 WINS!!!!\n");
	
	return 0;
}


