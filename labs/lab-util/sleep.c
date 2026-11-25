#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
/*
  Pause for n clock ticks
*/
int main(int argc, char *argv[]){

  // sleep command takes ít nhất 1 argument, chửi user nếu truyền sai
  // vì là error nên ta dùng fd 2
  if (argc != 2){
    fprintf(2, "Usage: sleep ticks\n");
    exit(1);
  }

  // parse từ char sang int, lấy second ele vì first element là của sleep program itself
  int tic = atoi(argv[1]);
  sleep(tic);
  exit(0);
}
