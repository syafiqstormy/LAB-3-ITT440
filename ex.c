#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void) {
  int pipefds[2];
  int nombo;
  int buffer;
  void sigint_hd(int sig);
  int flag =0;

  if(signal(SIGINT,sigint_hd)==SIG_ERR){
     perror("signal");
     exit(1);}
 
  if(pipe(pipefds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
 
  pid_t pid = fork();
 
  if(pid == 0) { // in child process
    printf("Anak jalan\n");
    printf("Masuk nombo plis\n"); 
    scanf("%d", &nombo);
    close(pipefds[0]); // close read fd
    write(pipefds[1],&nombo, sizeof(nombo)); // write number to pipe
 
    printf("Sending nombor to parent...\n");
    exit(EXIT_SUCCESS);
  }
 
  if(pid > 0) { // in main process
    printf("Tunggu anak\n");
    wait(NULL); // wait for child process to finis
    close(pipefds[1]); // close write fd
    read(pipefds[0],&buffer, sizeof(int)); // read number from pipe
    close(pipefds[0]); // close read fd
 
    printf("Parent received nombor '%d'\n", buffer);

       for (int i = 2; i <= buffer / 2; ++i) {

        // condition for non-prime
        if (buffer % i == 0) {
            flag = 1;
            break;
        }
    }

    if (buffer == 1) {
        printf("1 is neither prime nor composite.");
    }
    else {
        if (flag == 0)
            printf("%d is a prime number.", buffer);
        else
            printf("%d is not a prime number.", buffer);
    }

printf("\n");

  }

 
  return EXIT_SUCCESS;
}

  void sigint_hd(int sig){
   printf("signal interrupt!\n");}

