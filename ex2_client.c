#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/random.h>

void errHandler(int err){
    if (err == -1){
        printf("ERROR_FROM_EX2\n");
        exit(-1);   
    }
}

void handler(int sig){
    char to_client[20];
    sprintf(to_client,"to_client_%d",(int)getpid());
    int fd = open(to_client, O_RDONLY);
    errHandler(fd);
    char buff[1];
    while(read(fd,buff,1) > 0 ){
        printf("%c",buff[0]);
    }
    printf("\n");
    close(fd);
    remove(to_client);
}

int main(int argc, char *argv[]){
    

    if(argc != 5){
        errHandler(-1);
    }

    int P1 = atoi(argv[1]); //PID of the server
    int P2 = atoi(argv[2]);// First number to send
    int P3 = atoi(argv[3]);// Operator to send
    int P4 = atoi(argv[4]); //Second number to send

    signal(SIGUSR1,handler);

    //Checking if P3 is a valid operator
    if(P3 <1 && P3 > 4){
        errHandler(-1);
    }
    for(int i = 0; i < 10; i++){
        int fd1 = open("to_srv",O_RDONLY);
        if(fd1 != -1){
            int rnd[1] = {0};
            int err = getrandom(rnd,sizeof(int),0);
            errHandler(err);
            rnd[0] = (abs(rnd[0]) % 5) + 1;
            sleep(rnd[0]);
            close(fd1);
            printf("Waited between 1-5 seconds\n");
        } else {
            FILE* fd = fopen("to_srv", "w");
            printf("Created to_srv\n");
            if(fd == NULL){
                printf("ERROR_FROM_EX2\n");
                exit(-1);
            }
            fprintf(fd, "%d %d %d %d", getpid() , P2, P3, P4);
            fclose(fd);
            kill(P1, SIGUSR1); //Sending signal to the PID = P1
            int P1;
            FILE* fd2 = fopen("to_srv", "r");
            int err = fscanf(fd, "%d", &P1);
            // printf("%d %d\n", P1, getpid());
            if (P1 != getpid()){
                continue;
            }
            pause();
            exit(0);
        }
    }

    errHandler(-1);
}