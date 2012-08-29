//#include "sfsm.h"
#include "controlLogic.h"
#include "controller.h"
#include "stdio.h"

enum states{
    S1_STANDBY,
    S2_RUNNING,
    S3_SAFE_MODE,
    S4_CRASHED};
enum events{
    E_RUN,
    E_STOP,
    E_SZ_ENTERED,
    E_TS_TICK,
    E_LIMITER_HIT,
    E_CRASH_ACK};


    
int init(void){
    printf("initializing...\n");
    return(controllerInitialize());
}
int run(void){
    printf("running...\n");
    return(EXIT_SUCCESS);
}
int stop(void){
    printf("stopping...\n");
    return(EXIT_SUCCESS);
}
int brake(void){
    printf("braking...\n");
    controllerBrake();
    return(EXIT_SUCCESS);
}
int process(void){
    printf("processing...\n");
    controllerProcess();
    return(EXIT_SUCCESS);
}
int safeProcess(void){
    printf("safe_processing...\n");
    controllerProcess();
    return(EXIT_SUCCESS);
}
int onCrash(void){
    printf("I crashed!!!\n");
    return(EXIT_SUCCESS);
}
int recover(void){    
    printf("recovering...");
    return(EXIT_SUCCESS);
}

struct Transition tInitial = {S1_STANDBY, &init, NULL};
/*from S1_STANDBY*/
const struct Transition t12 = {S2_RUNNING, &run, NULL};
/*from S2_RUNNING*/
const struct Transition t21 = {S1_STANDBY, &stop, NULL};
const struct Transition t22 = {S2_RUNNING, &process, NULL};
const struct Transition t23 = {S3_SAFE_MODE, &brake, NULL};
const struct Transition t24 = {S4_CRASHED, &onCrash, NULL};
/*from S3_SAFE_MODE*/
const struct Transition t31 = {S1_STANDBY, &stop, NULL};
const struct Transition t32 = {S2_RUNNING, &run, NULL};
const struct Transition t33 = {S3_SAFE_MODE, &safeProcess, NULL};
const struct Transition t34 = {S4_CRASHED, &onCrash, NULL};
/*from S4_CRASHED*/
const struct Transition t41 = {S1_STANDBY, &recover, NULL};

/*transition table*/
const struct Transition *mControlLogicTt[24] = {
    &t12,NULL,NULL,NULL,NULL,NULL, //from S1_STANDBY
    NULL,&t21,&t23,&t22,&t24,NULL, //from S2_RUNNING
    &t32,&t31,NULL,&t33,&t34,NULL, //from S3_SAFE_MODE
    NULL,NULL,NULL,NULL,NULL,&t41};
    
struct Machine mControlLogic = {
    6,4,&tInitial,&mControlLogicTt[0],NULL, -1,
    S1_STANDBY};
