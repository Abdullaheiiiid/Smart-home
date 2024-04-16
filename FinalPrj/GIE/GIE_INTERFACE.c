#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "GIE_CONFIG.h"
#include "GIE_PRIVATE.h"
#include "GIE_INTERFACE.h"

void GIE(){
    SET_BIT(SREG, SREGF);
}

void GID(){
    CLEAR_BIT(SREG, SREGF);
}