#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

/*
  Write a simple version of the UNIX find program for xv6: 
  find all the files in a directory tree with a specific name. 
  Your solution should be in the file user/find.c.
*/

/**
 * 
 * idea là loop entries của path truyền vào rồi call dfs preorder để tìm 
 * trong các sub directory 
 * 
 * vì sao lại là preorder, vì mình xử lý node hiện tại rồi mới 
 * recursive call xuống subdir
 * 
 * algo:
 *  find(path, target):
 *    open(path)
 *    for e in entry:
 *       skip "." and ".."
 *       subpath(path + "/" + name)
 *       if (compare(name, target)): print(smth)
 *       find(subpath, target)
 */
void find(char *path, char *target){
  char buf[512], *p;
  int fd = open(path, O_RDONLY);
  struct dirent de;
  struct stat st;

  if(fd < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
  switch(st.type){
  case T_DEVICE:
  case T_FILE:{
    char *base = path;
    for(char *q=path; *q; q++)
      if(*q=='/' && *(q+1)) base=q+1;
    if(strcmp(base, target)==0) printf("%s\n", path);
    break;
  }
    

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum==0) continue;
      if(!strcmp(de.name,".") || !strcmp(de.name,"..")) continue;
      memmove(p, de.name, DIRSIZ); p[DIRSIZ]=0;
      if(stat(buf,&st)<0) continue;
      if(strcmp(p, target)==0) printf("%s\n", buf);
      if(st.type==T_DIR) find(buf, target);
    }
    break;
  }
  close(fd);
  
}

int main(int argc, char *argv[]){
  if (argc < 3){
    // raise err
    fprintf(2,"usage: find path name\n"); exit(1); 
  }

  find(argv[1],argv[2]);
  exit(0);
}
