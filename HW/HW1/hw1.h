#include <iostream>
#include <vector>
#include <stdio.h>
#include <cctype>
#include <cmath>

using namespace std;

#define	HSIZE 31			//Real Size + 1 because we don't use index 0

struct Elements
{							
	char	*name;
	int		score;
	char	*className;
};

//	functions for menu
void	printMenu();
char	getMenu();
int		validMenu(char a[10]);
//	functions for Heap
void	H_swap(Elements *S, int x, int y);
void	H_Msink(Elements *S, int idx);
void	H_Mswim(Elements *S, int idx);
void	H_Maxify(Elements *S);
void	H_Mpop(Elements *S);
//	functions for menu select
void	Insert(Elements *S);
void	PrintQ(Elements *S);
void	Retriver(Elements *S);
void	Increase(Elements *S);
//	another functions
int		findBack(Elements *S);
int		atoiLike(char *str);
