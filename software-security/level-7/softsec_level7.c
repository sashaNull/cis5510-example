// Compiled with DEP enabled.
// It's OK if your program crashes after the user exits the shell.
// gcc ./softsec_level7.c -o softsec_level7 -fno-PIE -no-pie -fno-stack-protector

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void cis551_greeting(void) {
  system("find .");
}

void copy_buffer(char *arg) {
  char buf[13];
  strcpy(buf, arg);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: Need a command-line argument\n");
    return 1;
  }
  setuid(0);
  cis551_greeting();
  copy_buffer(argv[1]);
  return 0;
}
