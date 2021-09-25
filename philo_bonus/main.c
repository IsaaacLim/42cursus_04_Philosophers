#include <stdio.h>

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
int	main()
{
	// int id_1;
	// int id_2;

	// id_1 = fork();
	// id_2 = fork();
	// printf("Hellp from %d-%d\n", id_1, id_2);

	// if (id_1 != 0)
	// {
	// 	if (id_2 != 0)
	// 		printf("Hello from %d-%d\n", id_1, id_2);
	// 	else
	// 		printf("Hellp from %d-%d\n", id_1, id_1);
	// }
	// else
	// {
	// 	if (id_2 != 0)
	// 		printf("Hellp from %d-%d\n", id_1, id_2);
	// 	else
	// 		printf("Hellp from %d-%d\n", id_1, id_1);
	// }

	char *str;
	char *test;

	test = ft_strncpy(str, "Hello", 10);
	printf("%s\n", str);
	printf("%s\n", test);
}
