#include <stdio.h>
#include <stdarg.h>
#include <features.h>
#undef __GLIBC_USE_DEPRECATED_SCANF
#define __GLIBC_USE_DEPRECATED_SCANF 1


    int main() {
        printf("Please enter password\n");
        char password[1000];
        scanf("%s\n", password);
	    printf("Doing super secret stuff\n");

        while (1);
    }
