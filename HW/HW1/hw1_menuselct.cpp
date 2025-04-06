#include "hw1.h"

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
	printf("[%s, %d, %s\n]", S[1].name, S[1].score, S[1].className);
}

void	Increase(Elements *S)
{
	int	idx;
	int	select;
	int	back;
	int	goal;

	back = findBack(S);
	cout << "Enter the index of the element: ";
	cin >> select;
	if (select >= back || select <= 0)
	{
		cout << "Wrong index Please Check the queue with menu 'P'\n";
		return ;
	}
	cout << "Enter the new score: ";
	scanf("%d", &goal);
	while (goal < S[select].score)
	{
		cout << "New score should be larger than current score. Please enter again\n";
		cout << "Enter the new score: ";
		scanf("%d", &goal);
	}
	S[select].score = goal;
	printf("Key updated. [%s, %d, %s] had been repositioned in the queue\n", S[select].name, S[select].score, S[select].className);
	H_Maxify(S);
}