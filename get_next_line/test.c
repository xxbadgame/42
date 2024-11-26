#include <stdio.h>

void change_nb(char *str)
{
	str[0] = 'a';
}

int main()
{
	char str[] = "salut";

	printf("%s\n", str);
	change_nb(&str);
	printf("%s\n", str);
	return (0);
}