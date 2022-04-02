#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int max(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

bool is_prime(int n) {
    bool result = true;

	if (n <= 1) {
		result = false;
	} else {
        int i;
        for (i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                result = false;
                break;
            }
        }
	}	

    return result;
}
