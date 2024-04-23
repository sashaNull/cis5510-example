// gcc ./softsec_level3.c -o softsec_level3 -fno-PIE -fno-stack-protector -no-pie -z execstack
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/personality.h>
#include <assert.h>
#include <sys/prctl.h>


void __attribute__((constructor)) disable_aslr(int argc, char **argv, char **envp)
{
  int current_personality = personality(0xffffffff);
  assert(current_personality != -1);
  if ((current_personality & ADDR_NO_RANDOMIZE) == 0) {
    assert(personality(current_personality | ADDR_NO_RANDOMIZE) != -1);
    assert(prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != -1);
    execve("/proc/self/exe", argv, envp);
  }
}

void copy_buffer(char *arg) {
  char buf[107];
  printf("Src Address: %p\n", arg);
  printf("Dest Address: %p\n", &buf);
  sleep(1);
  printf("COPY.............\n");
  strcpy(buf, arg);
}

int main(int argc, char **argv) {
  printf("Enter your payload: \n");
  char buf[0x100];
  read(0, buf, 0x100);
  printf("You entered: %s\n", buf);
  copy_buffer(buf);
  return 0;
}