// gcc ./softsec_level3.c -o softsec_level3 -fno-PIE -fno-stack-protector -no-pie -z execstack
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/personality.h>
#include <sys/prctl.h>
#include <unistd.h>

void __attribute__((constructor))
disable_aslr(int argc, char **argv, char **envp) {
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
  strcpy(buf, arg);
}

int main(int argc, char **argv) {
  printf("Enter your payload: \n");
  char buf[0x100];
  read(0, buf, 0x100);
  copy_buffer(buf);
  return 0;
}