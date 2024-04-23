// gcc ./softsec_level4.c -o softsec_level4 -fno-PIE -fno-stack-protector -no-pie -z execstack
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/personality.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <seccomp.h>

#define BUFFER_SIZE 0x100

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

void restrict_syscall()
{
  scmp_filter_ctx ctx;
  puts("Restricting system calls (default: kill).\n");
  ctx = seccomp_init(SCMP_ACT_KILL);
  printf("Allowing syscall: %s (number %i).\n", "execve", SCMP_SYS(execve));
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 0) == 0);

  for (int syscall_num = 102; syscall_num <= 124; syscall_num++) {
    printf("Allowing syscall: number %i.\n", syscall_num);
    assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, syscall_num, 0) == 0);
  }

  assert(seccomp_load(ctx) == 0);
}

void move_buffer(char *arg) {
  char buf[107];
  printf("Src Address: %p\n", arg);
  printf("Dest Address: %p\n", &buf);
  printf("MOVING.............\n");
  sleep(1);
  strcpy(buf, arg);
  printf("FLUSH..............\n");
  sleep(1);
  memset(arg, '\0', BUFFER_SIZE);
  restrict_syscall();
}

int main(int argc, char **argv) {
  printf("Enter your payload: \n");
  char buf[BUFFER_SIZE];
  read(0, buf, BUFFER_SIZE);
  printf("You entered: %s\n", buf);
  move_buffer(buf);
  return 0;
}