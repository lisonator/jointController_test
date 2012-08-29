/* 
 * File:   main.c
 * Author: Jakub Lisowski
 *
 * Created on 2 sierpień 2012, 11:48
 */

#include <stdio.h>
#include <stdlib.h>
#include "controlLogic.h"
#include "controller.h"
/*
 * 
 */


void printstate(struct Machine * m){
    printf("state: %d \n",m->current);
}

void printmotor(void){
    float * temp = controller.motorBlock.signals;
    printf("signals: %2.2f %2.2f %2.2f\n",temp[0],temp[1],temp[2]);
}

int main(int argc, char** argv) {
    
    float piparameters[] = {1.0, 0.1, -2.0, 2.0, -3.0, 3.0};
    float pisignals[] = {0.0, 0.0};
    float input = 4;
    int event;
    int ret;
    
    //tInitial.action = &init;
    event = 1;
        
    
    printstate(&mControlLogic);
    initializeMachine(&mControlLogic);
    printstate(&mControlLogic);
    
    controller.input=1.0;
    
    while(1){
    printf("event: ");
    fflush(stdout);
    scanf("%d",&event);
    fflush(stdout);
    printf("%d \n", event);
    fflush(stdout);
    if(event>10)
        break;
    ret = handleEvent(&mControlLogic,event);
    if(event==3 && !ret)
        printmotor();
    printf("eventret: %d\n",ret);
    fflush(stdout);
    printstate(&mControlLogic);
    }
    
    
    
    
    /*
    ret = piInitialization(&myPi,piparameters,6,pisignals,2,1,1);
    
    printf("ret = piInitialization():\n");
    printf("ret = %d\n",ret);
    printf("parameters:\n");
    printf("[%2.2f, %2.2f, %2.2f, %2.2f, %2.2f, %2.2f, ]\n",
            myPi.parameters[0],myPi.parameters[1],
            myPi.parameters[2],myPi.parameters[3],
            myPi.parameters[4],myPi.parameters[5]);
    printf("signals:\n");
    printf("[%2.2f, %2.2f]\n",myPi.signals[0],myPi.signals[1]);
    
    ret = computeSignals(&myPi,&input,1);
    printf("ret = computeSignals():\n");
    printf("ret = %d\n",ret);
    printf("parameters:\n");
    printf("[%2.2f, %2.2f, %2.2f, %2.2f, %2.2f, %2.2f, ]\n",
            myPi.parameters[0],myPi.parameters[1],
            myPi.parameters[2],myPi.parameters[3],
            myPi.parameters[4],myPi.parameters[5]);
    printf("signals:\n");
    printf("[%2.2f, %2.2f]\n",myPi.signals[0],myPi.signals[1]);

    int i;
    for(i=0;i<2;++i)
        ret = computeSignals(&myPi,&input,1);
    printf("ret = computeSignals():\n");
    printf("ret = %d\n",ret);
    printf("parameters:\n");
    printf("[%2.2f, %2.2f, %2.2f, %2.2f, %2.2f, %2.2f, ]\n",
            myPi.parameters[0],myPi.parameters[1],
            myPi.parameters[2],myPi.parameters[3],
            myPi.parameters[4],myPi.parameters[5]);
    printf("signals:\n");
    printf("[%2.2f, %2.2f]\n",myPi.signals[0],myPi.signals[1]);    
    
    */

    return (EXIT_SUCCESS);
}

