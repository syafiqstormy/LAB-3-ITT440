#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int getPIN() {
// use PPFID and PID AS THE SEED

  srand(getpid() + getppid());
  int secret = 1000 + rand() % 9000;
  return secret;}

int main (void){
  int fd[2];
  pipe(fd);
  pid_t pid = fork();

  if(pid>0){
  close(0);
  close(fd[1]);
  dup(fd[0]);

  int secretNum;
  size_t readBytes = read(fd[0], &secretNum, sizeof(secretNum));

  printf("waiting for PIN..\n");
  wait(NULL);
  printf("Bytes read: %ld\n",readBytes);
  printf("PIN: %d\n", secretNum);
}

else if(pid==0){
	close(1);
	close(fd[0]);
	dup(fd[1]);

	int secret = getPIN();
	write (fd[1], &secret, sizeof(secret));
	exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}

