/* 
 * File:   motorBlock.h
 * Author: jlisowski
 *
 * Created on 19 sierpień 2012, 01:56
 */

#ifndef MOTORBLOCK_H
#define	MOTORBLOCK_H

#include "block.h"

#ifdef	__cplusplus
extern "C" {
#endif
    /* Simple motor
     * parameters[5]:
     * [Ac, Tc, Aw, Tw, Tp]
     * signals[3]:
     * [current(k), velocity(k), position(k)]
     * outputs[3]:
     * [current(k), velocity(k), position(k)]
     * inputs[1]:
     * voltage(k)
     */
    int initializeMotorBlock(Block *, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs);



#ifdef	__cplusplus
}
#endif

#endif	/* MOTORBLOCK_H */

