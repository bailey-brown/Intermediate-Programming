
#include <stdio.h>

void ConvertDecimalToBinary(int n, int a[])
{
	int i;
	
	for(i=0; i<8; i++)
	{
		
		if((n & 1)==1)
		{
			a[i]=1;
		}
		else
		{
			a[i]=0;
		}
		
		n=n>>1;
	}
	
}

void PrintBinary(int a[])
{
	int i;
	
	for(i=7; i>=0; i--)
	{
		printf("%d", a[i]);
	}
	
	printf("\n");
	
}

int main(void)
{
	int num=-1;
	int numArray[8];
	
	printf("Decimal to binary convertor\n");
	
	while(num<0 || num>255)
	{
		printf("Please enter a decimal number between 0 and 255\t");
		scanf("%d", &num);
		
		if(num>=0 && num<=255)
		{
			printf("Decimal %d converts to binary ", num);
			
			ConvertDecimalToBinary(num, numArray);
			PrintBinary(numArray);
		}
		else
		{
			printf("You entered a number not between 0 and 255\n");
		}
	}
	
	return 0;
}

