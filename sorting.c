#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Blatantly stolen from Zed Shaw to handle errors */
void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

typedef int *(*sort_func) (int *numbers, int count);

int *bubble_sort(int *numbers, int count)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++) {
		for (j = 0; j < count - 1; j++) {
			if (target[j] > target[j + 1]) {
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}
	
	return target;
}

int *insertion_sort(int *numbers, int count)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < (count - 1); i++) {
		if (target[i] > target[i + 1]) {
			temp = target[i + 1];
			target[i + 1] = target[i];
			target[i] = temp;
			for (j = i; j > 0; j--) {
				if (target[j - 1] > target[j]) {
					temp = target[j - 1];
					target[j - 1] = target[j];
					target[j] = temp;
				}
			}
		}
	}

	return target;
}

void test_sorting(int *numbers, int count, sort_func srt)
{
	int i = 0;
	int *sorted = srt(numbers, count);

	if (!sorted)
		die("Failed to sort as requested.");
	
	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");
	
	free(sorted);
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 4 3 1 5 6");
	// accepts command line args as the list of numbers to sort
	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;

	int *numbers = malloc(count * sizeof(int));
	if (!numbers) die("Memory error.");

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);	
	}
	
	printf("Bubble sort ------\n");
	test_sorting(numbers, count, bubble_sort);
	printf("Insertion sort ------\n");
	test_sorting(numbers, count, insertion_sort);
	
	return 0;
}
