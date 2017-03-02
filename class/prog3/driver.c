#include <stdio.h>

int main (void) {

	int a, b, c, disc, i = 0;

	while (i < 3) {
		printf("Enter three ints for a, b, and c\n");
		scanf ("%d %d %d", &a, &b, &c);
		disc = discrim(a, b, c);
		printf("The discriminant is %d\n----------------\n", disc);
		i++;
	}

	return 0;
}
