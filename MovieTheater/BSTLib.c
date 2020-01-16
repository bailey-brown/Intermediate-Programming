/* Bailey Brown 1001555076 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BSTLib.h"

struct Bnode *CreateBST(struct Bnode *root, char MTName[], char MTZip[], char MTMap[])
{
	// If tree is empty, then current node becomes root
    if (root == NULL)
    {
        root = (struct Bnode *)malloc(sizeof(struct Bnode));
        
		root->left = root->right = NULL;
		
        strcpy(root->MovieTheaterName, MTName);
		root->MovieTheaterName[sizeof(root->MovieTheaterName)-1] = '\0';
		strcpy(root->MovieTheaterZip, MTZip);
		root->MovieTheaterZip[sizeof(root->MovieTheaterZip)-1] = '\0';
		strcpy(root->MovieTheaterMap, MTMap);
		root->MovieTheaterMap[sizeof(root->MovieTheaterMap)-1] = '\0';
        
		return root;
    }
    else
    {
        if (strcmp(MTZip, root->MovieTheaterZip) < 0)
			root->left = CreateBST(root->left, MTName, MTZip, MTMap);
		
        else if(strcmp(MTZip, root->MovieTheaterZip) > 0)
            root->right = CreateBST(root->right, MTName, MTZip, MTMap);
        
		else
            printf(" Duplicate Element !! Not Allowed !!!");

        return(root);
    }
}

void ListZipsInOrder(struct Bnode *root)
{
    if( root != NULL)
    {
		ListZipsInOrder(root->left);
        printf("%s\n", root->MovieTheaterZip);
		ListZipsInOrder(root->right);
    }
}

void WriteOutNode(struct Bnode *root, FILE *MyFile)
{
    if( root != NULL)
    {
		WriteOutNode(root->left, MyFile);
		fprintf(MyFile, "%s|%s|%s\n", root->MovieTheaterName, root->MovieTheaterZip, root->MovieTheaterMap);
		WriteOutNode(root->right, MyFile);
    }
}

struct Bnode *SearchForMovieTheater(struct Bnode *root, char Zip[])
{
	if (root == NULL || !strcmp(root->MovieTheaterZip, Zip))
	{
		return root;
	}
		
	if (strcmp(root->MovieTheaterZip, Zip) > 0)
		return SearchForMovieTheater(root->left, Zip);
		
    else
		return SearchForMovieTheater(root->right, Zip);
}

