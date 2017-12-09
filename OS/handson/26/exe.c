#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("Hola!\n");
	if(argc > 1) {
		printf("Args passed: \n");
		for(int i = 0; i < argc; i++) {
			printf("%s\n", argv[i]);
		}
	}
}