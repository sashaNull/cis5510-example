// gcc ./softsec_level2.c -o softsec_level2 -fno-PIE -fno-stack-protector
// -no-pie
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void win() {
  char buffer[256];
  int flag_fd = open("/flag", O_RDONLY);

  printf("Congratulations! You win! Here is your flag:\n");

  if (flag_fd >= 0) {
    int bytes_read = read(flag_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
      write(1, buffer, bytes_read);
      printf("\n");
      close(flag_fd);
    } else {
      printf("ERROR: Failed to read the flag!\n");
    }
  } else {
    printf("ERROR: Failed to read the flag!\n");

    int euid = geteuid();
    if (euid) {
      printf("Your effective user id is not 0!\n");
      printf("You must directly run the suid binary in order to have the "
             "correct permissions!\n");
    }
  }
}

void expected_control_flow(void) {
  puts("This is the expected control flow.");
  exit(0);
}

void process_inputs() {
  printf("Enter your payload:\n");
  char input[9];
  read(0, input, 0x20);
}

int main() {
  process_inputs();
  expected_control_flow();
  return 0;
}