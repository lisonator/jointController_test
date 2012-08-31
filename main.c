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
#include "circularBuffer.h"
#include "block.h"
#include "blockLogger.h"
#include <assert.h>
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
    int ret,i,j;
    runMachine(&mControlLogic);
    //test blocklogger
    float st[18];
    for(ret=0;ret<18;ret++)
        st[ret]=0;
    struct BlockLogger bl;
    initializeBlockLogger(&bl,&(controller.motorBlock),st,18);
    
    for(i=0;i<6;++i) {
        for(j=0;j<3;j++)
            printf("%3.3f ",st[3*i+j]);
            printf("\n");}
    
    //test blocklogger end
    
    
    
    //tInitial.action = &init;
    event = 1;
        
    
    printstate(&mControlLogic);
    
    controller.input=1.0;
    
    while(1){
    printf("event: ");
    scanf("%d",&event);
    printf("%d \n", event);
    if(event==10)
        flushBl(&bl);
    if(event==11)
        startBl(&bl);    
    if(event==12)
        pauseBl(&bl);
    if(event==13)
        stopBl(&bl);
    if(event==14)
        handleEvent(&bl.logic,3);
    if(event==99)
        return(0);
    ret = handleEvent(&mControlLogic,event);
    
    if(event==3 && !ret)
        printmotor();
    printf("eventret: %d\n",ret);
    fflush(stdout);
    //printstate(&mControlLogic);
    for(i=0;i<6;++i) {
        for(j=0;j<3;j++)
            printf("%3.3f ",st[3*i+j]);
            printf("\n");}
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

