// Compiled with DEP enabled.
// It's OK if your program crashes after the user exits the shell.
// gcc ./softsec_level7.c -o softsec_level7 -fno-PIE -no-pie -fno-stack-protector

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

void auth(int pennkey, char *name, char *email, char *research, int course_code, char *cmd, bool pwnnsylvanian, char *fav_ctf_category) {
  printf("Pwnnsylvanian? %s\n", pwnnsylvanian ? "true" : "false");
  printf("Pennkey: %d\n", pennkey);
  printf("Name: %s\n", name);
  printf("Email: %s\n", email);
  printf("Area of Research: %s\n", research);
  printf("Course Code: %d\n", course_code);
  printf("Favourite CTF category: %s\n", fav_ctf_category);
  printf("Executing command......\n");
  sleep(1);
  if (pennkey == 0x1337 && pwnnsylvanian)
  {
    system(cmd);
  }
  else
  {
    printf("Sorry, only Sebastian has the permission to execute commands!\n");
  }
}

void read_buffer() {
  char buf[8];
  printf("READING.............\n");
  sleep(1);
  read(0, buf, 0x13);
  printf("Dest address read: %p!\n", &buf);
}

int main() {
  setuid(0);
  auth(0x1337, "sebastian", "sebastian.angel@cis.upenn.edu", "Cybersecurity", 5510, "echo CIS5510 is awesome!", true, "pwn, rev");
  read_buffer();
  return 0;
}
