/* 
 * File:   controller.h
 * Author: jlisowski
 *
 * Created on 18 sierpień 2012, 14:14
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include "motorBlock.h"
#include "pid.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
    /*singleton object*/
    struct Controller{
        struct Block piCascade[3];
        struct Block motorBlock;
        float input;
        
        int bitFlags;
    } controller;
    
    int controllerInitialize(void);
    void controllerProcess(void);
    void controllerSafeProcess(void);
    
    void controllerBrake(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

