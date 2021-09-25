#include ....

int	main()
{
	int id_1;
	int id_2;

	id_1 = fork();
	id_2 = fork();
	printf("Hellp from %d-%d\n", id_1, id_2);

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
}
