#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int readFile(int signum){
    int P2, P3, P4;
    
    int pid =fork();
    if(pid==0){
        int fd = fopen("math.txt", "r");//READ FILE
        fscanf(fd, "%d %d %d", &P2, &P3, &P4);
        fclose("math.txt");
        int sum = calc(P2, P3, P4);

        fopen("math.txt", "w");//WRITE FILE
        fprintf("math.txt", "%d",sum);
        fclose("math.txt");
        exit(1);
    }else{
        wait(NULL);
        print("Child finished");

    }
}

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

int main(){

    printf("Server Listening\n");

    signal(SIGINT, readFile);//Listens 
    while(1){
        
    }
    


    return 0;
}