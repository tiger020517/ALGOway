#include "hw1.h"

int		atoiLike(char *str)
{
	int	idx;
	int	num[3] = {0};
	int	nidx;

	idx = 0;
	nidx = 0;
	while (str[idx] && idx < 6 && nidx < 3)
	{
		if (isdigit(str[idx]))
		{
			num[nidx] = str[idx] - '0';
			nidx++;
		}
		idx++;
	}
	if (nidx == 0)
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