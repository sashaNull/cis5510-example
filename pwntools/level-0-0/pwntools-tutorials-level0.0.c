#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void print_flag()
{
	char *p;
	FILE *fp;
	char flag[100];

	fp = fopen("/flag", "r");

	if (!fp) {
		perror("[-] fopen failed");
	}

	p = fgets(flag, sizeof(flag), fp);
	if (!p) {
		perror("[-] fgets failed");
		fclose(fp);
	}
	
	printf("%s", flag);

	fclose(fp);
}

int bypass_me(char *buf)
{	
	if (!strncmp(buf, "cis5510", 7)) {
		return 1;
	}
	
	return 0;
}

int main()
{
	char buffer[100];

	printf("Hi! I challenge you to use pwntools to pwn me :)\n");

	fgets(buffer, sizeof(buffer), stdin);

	if (bypass_me(buffer)) {
		print_flag();
	} else {
		printf("You need to bypass some conditions to get the flag: \n");
		printf("Please refer to the source code to understand these conditions\n");	
	}

	return 0;
}
