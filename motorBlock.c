#include "motorBlock.h"

static int motorBlockCompute(Block *,
            const float *inputs, int nInputs);

int initializeMotorBlock(Block *this, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs)
{
    if(nParameters!=5)
        return(EXIT_FAILURE);
    if(nSignals!=3)
        return(EXIT_FAILURE);
    if(nOutputs!=3)
        return(EXIT_FAILURE);
    if(nInputs!=1)
        return(EXIT_FAILURE);
    
    initializeBlock(this,parameters,nParameters,
            signals,nSignals,
            nInputs,nOutputs);

    this->compute = &motorBlockCompute;
    
    return(EXIT_SUCCESS);
}

static int motorBlockCompute(Block * this,
        const float *inputs, int nInputs)
{
    /*Ac Tc Aw Tw Tp*/
    float *par = this->parameters;
    /*c w p*/
    float *sig = this->signals;
    
    if(nInputs != this->nInputs)
        return(EXIT_FAILURE);
    
    /*compute position*/
    sig[2] = sig[2] + sig[1]*par[4];
    
    /*compute velocity*/
    sig[1] = par[2]*par[3]*sig[0]+(1-par[3])*sig[1];
    
    /*compute current*/
    sig[0] = par[0]*par[1]*inputs[0]+(1-par[1])*sig[0];
    return(EXIT_SUCCESS);
}
