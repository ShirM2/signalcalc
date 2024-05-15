#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



int main(int argc, char *argv[]){

    if(argc != 5){
        printf("Invalid input, Example: PID Num1 OP Num2\n", argv[0]);
        return 1;
    }

    int P1 = atoi(argv[1]); //PID of the server
    int P2 = atoi(argv[2]);// First number to send
    int P3 = atoi(argv[3]);// Operator to send
    int P4 = atoi(argv[4]); //Second number to send

    //Checking if P3 is a valid operator
    if(P3 <1 && P3 > 4){
        printf("Invaild operator\n");
        return -1;
    }

    fopen("math.txt", "w");
    fprintf("math.txt", "%d %d %d", P2, P3, P4);
    fclose("math.txt");
    kill(P1, SIGINT);//Sending signal to the PID = P1

    //sleeps for the results 

    // ido 123


    return 0;
}