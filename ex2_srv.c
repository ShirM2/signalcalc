#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int calc(int num1, int op, int num2) {
	int sum=0;

	switch(op){
	case 1:
	
		sum = num1 + num2;

		break;
	case 2:
		sum = num1 - num2;
		break;

	case 3:
		sum = num1 * num2;
		break;

	case 4:
		sum = num1 / num2;
		break;

	}

	return sum;
}

void readFile(int signum){
    int P1, P2, P3, P4;
    
    int pid = fork();
    if(pid==0){
        FILE* fd = fopen("to_srv", "r");//READ FILE
        if(fd == NULL){
            printf("ERROR_FROM_EX2\n");
            exit(-1);
        }
        int err = fscanf(fd, "%d %d %d %d", &P1, &P2, &P3, &P4);
        printf("Child Read to_srv\n");
        if (err == EOF){
            printf("ERROR_FROM_EX2\n");
            exit(-1);   
        }
        fclose(fd);
        remove("to_srv");
        printf("Child Deleted to_srv\n");
        int sum = calc(P2, P3, P4);

        char to_client[20];
        snprintf(to_client,sizeof(to_client),"to_client_%d",P1);
        fd = fopen(to_client, "w");//WRITE FILE
        printf("Child Created to_client_XXXX\n");
        if(fd == NULL){
            printf("ERROR_FROM_EX2\n");
            exit(-1);
        }
        fprintf(fd, "%d",sum);
        fclose(fd);
        kill(P1,SIGUSR1);
        printf("Child Sent Signal to client\n");
        exit(1);
    }else{
        printf("Created a Child process\n");
        wait(NULL);
    }
}


int main(){
    printf("Server Start\n");
    signal(SIGUSR1, readFile);//Listens
    printf("Waiting for signal\n");
    while(1){
       pause(); 
       printf("Handled client\n");
    }
    

    return 0;
}