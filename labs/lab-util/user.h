struct stat;

// system calls

// create a new child process
// return a pid 
// if p > 0, which means in current process 
// if p == 0, which means in child process 
// otherwise, err
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);

// create a new pipe, pass in an array with 2 elements 
// first one is read end, second one is write end
int pipe(int*);
int write(int fd, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat *);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
// get current process pid
int getpid(void);
char* sbrk(int);

/*
  Pause for n clock ticks.
*/
int sleep(int);
int uptime(void);
// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);
