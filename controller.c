#include "controller.h"
#include <stdio.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

//parameters:
//[kp, ki, minI, maxI, minU, maxU]
static float curpiparameters[] = {1,0,0,0,-100,100};    
static float velpiparameters[] = {1,0.1,-10,10,-100,100};
static float pospiparameters[] = {1,0,0,0,-100,100};
//[Acur, Tcur, Avel, Tvel, Tpos]
static float motorparameters[] = {100,0.1,0.1,0.95,0.1};

//signals:
static float curpisignals[2];
static float velpisignals[2];
static float pospisignals[2];
static float motorsignals[3];

int controllerInitialize(void)
{
    int error = EXIT_SUCCESS;
    int i;
    controller.input = 0.0;

    error = initializePi(&controller.piCascade[0], 
            curpiparameters, 6,
            curpisignals, 2,
            1, 1) || error;
    error = initializePi(&controller.piCascade[1], 
            velpiparameters, 6,
            velpisignals, 2,
            1, 1) || error;
    error = initializePi(&controller.piCascade[2], 
            pospiparameters, 6,
            pospisignals, 2,
            1, 1) || error;
    error = initializeMotorBlock(&controller.motorBlock, 
            motorparameters, 5,
            motorsignals, 3,
            1, 3) || error;
    return(error);
}

void controllerBrake(void){
    printf("motor brake!\n");
}

/*crunch some numbers and set control signal to motor*/
void controllerProcess(void)
{
    float temp = controller.input;
    float * motorsignals = getOutputs(&controller.motorBlock);
    
    int i;
    for(i=2;i>=0;--i)
        if(CHECK_BIT(controller.bitFlags,i+1)){
            temp = temp - *(motorsignals+i);
            computeSignals(&controller.piCascade[i],&temp,1);
            temp = *(getOutputs(&controller.piCascade[i]));
        }
    computeSignals(&(controller.motorBlock),&temp,1);
}

void controllerSafeProcess(void)
{
    const float * const motorsignals = getOutputs(&controller.motorBlock);
    printf("safeprocess\n");
}