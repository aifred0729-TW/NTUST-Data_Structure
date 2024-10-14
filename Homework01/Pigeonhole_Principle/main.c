#include <stdio.h>
#include <stdbool.h>

int functionF(int x) {
	return x % 5;
}

int main() {
	int n = 20;
	bool found = false;

	int a = 0;
	int b = 0;

	for (size_t i = 1; i < n; i++) {
		for (size_t j = n; j > 0; j--) {
			if (functionF(i) == functionF(j)) {
				found = true;
				a = i;
				b = j;
				break;
			}
		}
		if (found) break;
	}

	printf("Found a = %d & b = %d, such that f(a) = f(b)\n", a, b);

	return 0;
}