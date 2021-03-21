#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h> 
#include "float.h"



int is_special ( float f ) {
    uint32_t temp;
    memcpy(&temp,&f,4); /*hardcode specification for float (4-bytes)*/
    temp = temp & 0x7f800000; /*mask representation of the exponent*/
    temp = temp >>23;
    if(temp == 0 || temp == 0xff) /* subnormal numbers, inf and nan are special cases*/
        return 1;
    else
        return 0;
}


float get_M  ( float f ) {
    uint32_t temp;
    memcpy(&temp,&f,4); /*hardcode specification for float (4-bytes)*/
    temp = temp & 0x7f800000; /*mask representation of the exponent*/
    temp = temp >>23;
    if(temp == 0 || temp == 0xff){ /*If all bits are set (0xff) special case we have to handle*/
        uint32_t temp;
        memcpy(&temp,&f,4); /*hardcode specification for float (4-bytes)*/
        temp = temp & 0x7fffff; /*mask representation of the mantissa*/
        /*Start at 0, for special case mantissas*/ 
        float sum = 0;
        for(int i = 0;i<23;i++){
          sum+= pow(2,i-23) * (temp & 1); /*If bit is not set do nothing*/
          temp >>= 1;
        }
        return sum;
    }
    else{
        uint32_t temp;
        memcpy(&temp,&f,4); /*hardcode specification for float (4-bytes)*/
        temp = temp & 0x7fffff; /*mask representation of the mantissa*/
        float sum = 1; /*sum starts at 1 for the implied bit*/
        for(int i = 0;i<23;i++){
        /*If bit is not set do nothing. Starts at bit 0(or 2^-23, least signifcant bit)*/
          sum+= pow(2,i-23) * (temp & 1);
        /*move on to the next bit(slightly more signifcant than previous bit)*/
          temp >>= 1;
        }
        return sum; /* sum of manitissa converted to fractions */
    }
}


int get_s ( float f ) {
    uint32_t temp;
    memcpy(&temp,&f,4); /*hardcode specification for float (4-bytes)*/
    if (temp>>31) /*Shift to the right 31 because sign is in the 32nd bit*/
        return -1; /* if sign bit is set return -1*/
    else
        return 1; /* if sign bit is not set return 1*/
}


int get_E ( float f ) {
    uint32_t temp;
    memcpy(&temp,&f,4); /*hardcode specification for float (4-bytes)*/
    temp = temp & 0x7f800000; /*mask representation of the exponent*/
    temp = temp >>23; /*Shift the exponent to the right 23 bits beccause exponent in 23rd bit*/
    if(temp == 0) /* if the exponent is zero, its a special case (subnormal number)*/
        return -126; //return -126 if nan
     else if(temp == 0xff)
        return 0xff; /*return 255*/
    else
        return (int)temp - 127; /*return the exponent if not a special case*/  
}
