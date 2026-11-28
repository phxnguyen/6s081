#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winfinite-recursion"

/*
  Write a concurrent prime sieve program for xv6 using pipes
  and the design illustrated in the picture halfway down this page and the surrounding text. 
  This idea is due to Doug McIlroy, inventor of Unix pipes. 
  Your solution should be in the file user/primes.c.
*/

/*
  dùng pipeline pattern 
*/

void sieve(int leftfd){
  int number;
  int res = read(leftfd, &number, sizeof(number));

  if (res == 0){
    // eof 
    close(leftfd);
    exit(0);
  }
  printf("prime %d\n", number);

  int rightfd[2]; pipe(rightfd);
  int pid = fork();
  if (pid == 0){
    close(rightfd[1]);
    close(leftfd);
    sieve(rightfd[0]);
  }else{
    close(rightfd[0]);
    int n;
    // logic 
    while(read(leftfd, &n, sizeof(n))){
      if(n % number != 0)
        write(rightfd[1], &n, sizeof(n));
    }
    close(leftfd);
    close(rightfd[1]);
    wait(0);
    exit(0);
    
  }


}

int main(int argc, char *argv[]){

  int p[2];
  pipe(p);

  int pid = fork();
  if(pid < 0){
    // raise error 
    fprintf(2, "fork failed\n");
    exit(1);
  }

  // in child process 
  if(pid == 0){
    close(p[1]); // close write fd pipe
    sieve(p[0]);
  }  else{
    close(p[0]);
    for(int i=2; i<=35; i++)
      write(p[1], &i, sizeof(i));
    close(p[1]);
    wait(0);
    exit(0);
  }


}

