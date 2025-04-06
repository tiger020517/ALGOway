#include "hw1.h"

char	getMenu()
{
	char	in[10];
	char	out;

	cout << "Choose menu: ";
	cin.getline(in, 10);
	while (!validMenu(in))
	{
		cout << "error! choose another menu: ";
		cin.getline(in, 10);
	}
	return (validMenu(in));
}

int	validMenu(char a[10])
{
	int	idx;

	idx = -1;
	while (isspace(a[++idx])) ;
	if (a[idx] == 'I' || a[idx] == 'D' || a[idx] == 'R' || a[idx] == 'N' || a[idx] == 'P' || a[idx] == 'Q')
		return (a[idx]);
	else if (a[idx] == 'i' || a[idx] == 'd' || a[idx] == 'r' || a[idx] == 'n' || a[idx] == 'p' || a[idx] == 'q')
		return (a[idx]);
	else
		return (0);
}

void	printMenu()
{
	cout << "********** MENU **********\n";
	cout << "I : Insert a new element into the queue\n";
	cout << "D : Delete the element with the largest key from the queue\n";
	cout << "R : Retrieve the element with the largest key\n";
	cout << "N : Increase the key of an element in the queue\n";
	cout << "P : Print all elements in the queue\n";
	cout << "Q : Quit\n";
	cout << "\n";
}