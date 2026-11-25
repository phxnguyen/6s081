#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int toChild[2];  // parent -> child
  int toParent[2]; // child -> parent
  char buf[1];

  if (pipe(toChild) < 0 || pipe(toParent) < 0) {
    fprintf(2, "pingpong: pipe failed\n");
    exit(1);
  }

  int pid = fork();
  if (pid < 0) {
    fprintf(2, "pingpong: fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    // child: receive ping, reply with pong
    close(toChild[1]);
    close(toParent[0]);

    if (read(toChild[0], buf, 1) != 1) {
      fprintf(2, "pingpong: child read failed\n");
      exit(1);
    }
    close(toChild[0]);

    printf("%d: received ping\n", getpid());

    if (write(toParent[1], buf, 1) != 1) {
      fprintf(2, "pingpong: child write failed\n");
      exit(1);
    }
    close(toParent[1]);

    exit(0);
  } else {
    // parent: send ping, wait for pong
    close(toChild[0]);
    close(toParent[1]);

    buf[0] = 'x';
    if (write(toChild[1], buf, 1) != 1) {
      fprintf(2, "pingpong: parent write failed\n");
      exit(1);
    }
    close(toChild[1]);

    if (read(toParent[0], buf, 1) != 1) {
      fprintf(2, "pingpong: parent read failed\n");
      exit(1);
    }
    close(toParent[0]);

    printf("%d: received pong\n", getpid());

    wait(0);
    exit(0);
  }
}
