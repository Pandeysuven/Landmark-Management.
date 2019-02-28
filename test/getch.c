#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main()
{
	int input;
	while (1)
	{
		input = getch();
		if (input == EOF)
		{
			printf("EOF");
			system("pause");
			return 0;
		}
		else if (input == 13)
			return 0;
		else printf("%d\n", input);
	}
	return 0;
}