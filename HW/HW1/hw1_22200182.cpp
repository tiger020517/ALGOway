/*
	1)	용환기 교수님의 Heap 강의
	2)	C++, Heap, Name space 강의 https://youtu.be/oaXqDBh_-qs?si=tRKjMsr9vusCb0pQ
*/
#include <iostream>
#include <stdio.h>			//cout은 여러 변수들을 출력 할 떄 가독성이 떨어진다 판단하여 printf를 사용하기도 하였습니다.
#include <cctype>
#include <cmath>

using namespace std;

#define	HSIZE 31			//1번 인덱스부터 사용하니 저희가 생각하는 Max size + 1로 세팅하였습니다.

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
//	사실 최대 힙 최소 힙을 구분해서 사용하려면 function pointer를 사용해야 하나 
//	이 과제만을 위해 만든 함수들이므로 최대힙만을 사용하는것을 상정하였다.
void	H_swap(Elements *S, int x, int y);
void	H_Msink(Elements *S, int idx);
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


int	main(void)
{
	Elements	*S;
	char		choose;
	int			idx;

	S = new Elements[HSIZE];
	choose = 0;
	do
	{
		printMenu();
		choose = getMenu();
		switch (choose)
		{
		case 'I':
		case 'i':
			if (findBack(S) >= HSIZE)
			{
				cout << "Heap is full\n";
				break ;
			}
			Insert(S);
			H_Maxify(S);
			cout << "\n";
			break ;
		case 'D':
		case 'd':
			if (findBack(S) <= 1)
			{
				cout << "Cannot delete form an empty queue\n";
				break ;
			}
			H_Mpop(S);
			H_Maxify(S);
			break ;
		case 'R':
		case 'r':
			if (findBack(S) <= 1)
			{
				cout << "Queue is empty\n";
				break;
			}
			Retriver(S);
			break ;
		case 'N':
		case 'n':
			if (findBack(S) <= 1)
			{
				cout << "Queue is empty\n";
				break;
			}			
			Increase(S);	
			H_Maxify(S);
			break ;
		case 'P':
		case 'p':
			if (findBack(S) <= 1)
			{
				cout << "Queue is empty\n";
				break;
			}
			PrintQ(S);
			break ;
		default :
			break ;
		}
		cout << "\n";
		H_Maxify(S);
	} while (choose != 'Q' && choose != 'q');
	
}


//	Heap을 위한 함수들
void	H_Mpop(Elements *S)
{
	int	idx;
	int	back;

	back = findBack(S);
	idx = 0;				//Queue의 0번 idx는 사용하지 않으므로 0번은 없어진 취급
	while (++idx < back)
		S[idx - 1] = S[idx];
	printf("Deleted element: [%s, %d, %s]", S[0].name, S[0].score, S[0].className);
	delete S[0].name;
	delete S[0].className;
	S[back - 1].name = 0;
	S[back - 1].score = 0;
	S[back - 1].className = 0;
}

void	H_swap(Elements *S, int x, int y)
{
	Elements	temp;

	temp = S[x];
	S[x] = S[y];
	S[y] = temp;
}

void	H_Msink(Elements *S, int idx)
{
	int	back;

	back = findBack(S);
	while (idx <= back / 2)
	{
		int	child = idx * 2;
		if (child + 1 <= back && S[child].score < S[child + 1].score)
			child++;
		if (S[idx].score < S[child].score)
		{
			H_swap(S, idx, child);
			idx = child;
		}
		else break ;
	}
}

void	H_Maxify(Elements *S)
{
	int	idx;

	if (findBack(S) == 1)
		return ;
	idx = 1;
	while (idx <= (findBack(S) / 2))
	{
		H_Msink(S, idx);
		idx++;
	}
}

// 메뉴 관련된 햄수들
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

// 메뉴 선택시 작동하는 함수들
void	Insert(Elements *S)
{
	int		back;
	char	scores[6];

	back = findBack(S);
	printf("Enter the name of the student: ");
	S[back].name = new char[20];
	cin.getline(S[back].name, 20);
	printf("Enter the score of the element: ");
	cin.getline(scores, 6);
	while (atoiLike(scores) == 404)
	{
		cout << "Error! Enter the score between 0 to 100\n";
		cout << "Enter the score of the element: ";
		cin.getline(scores, 6);
	}
	S[back].score = atoiLike(scores);
	cout << "Enter the class name: ";
	S[back].className = new char[20];
	cin.getline(S[back].className, 20);
	printf("New element [%s, %d, %s] has been inserted.", S[back].name, S[back].score, S[back].className);
}

void	PrintQ(Elements *S)
{
	int	idx;
	int	back;

	back = findBack(S);
	idx = 0;
	printf("Current queue elements\n");
	while (++idx < back)
	{
		printf("%d. [%s, %d, %s]\n", idx, S[idx].name, S[idx].score, S[idx].className);
	}
}

void	Retriver(Elements *S)
{
	cout << "Element with the largest key: ";
	printf("[%s, %d, %s]\n", S[1].name, S[1].score, S[1].className);
}

void	Increase(Elements *S)
{
	char	goalin[6];
	int		select;
	int		back;
	int		goal;

	back = findBack(S);
	cout << "Enter the index of the element: ";
	scanf("%d", &select);
	if (select >= back || select <= 0)
	{
		cout << "Wrong index Please Check the queue with menu 'P'\n";
		return ;
	}
	cout << "Enter the new score: ";
	cin.ignore(1000, '\n');
	cin.getline(goalin, 6);
	goal = atoiLike(goalin);
	while (goal == 404 || goal <= S[select].score)
	{
		if (goal <= S[select].score)
			cout << "New score should be larger than current score. Please enter again\n";
		else if (goal == 404)
		cout << "Error! Enter the score between 0 to 100\n";
		cout << "Enter the new score: ";
		cin.getline(goalin, 6);
		goal = atoiLike(goalin);
	}
	S[select].score = goal;
	printf("Key updated. [%s, %d, %s] had been repositioned in the queue\n", S[select].name, S[select].score, S[select].className);
	H_Maxify(S);
}

// 기타 함수들
int		atoiLike(char *str)
{
	int	idx;
	int	num[3] = {0};
	int	nidx;
	int	midx;	// -의 갯수

	idx = 0;
	nidx = 0;
	midx = 0;
	while (str[idx] && idx < 6 && nidx < 3)
	{
		if (isdigit(str[idx]))
		{
			num[nidx] = str[idx] - '0';
			nidx++;
		}
		else if(str[idx] == '-')
			midx++;
		idx++;
	}
	if (nidx == 0 || midx % 2) // -가 홀수 개 있으면 음수이므로 틀린 input이다.
		return (404);
	idx = 0;
	for (int i = 0; i < nidx; i++)
		idx += pow(10, nidx - (i + 1)) * num[i];
	if (idx > 100)
		return (404);
	return (idx);
}

int		findBack(Elements *S)
{
	int	idx;

	idx = 0;
	while (S[++idx].name) ;
	return (idx);
}