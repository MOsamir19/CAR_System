#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_Interface.h"
#include "GIE_private.h"


void GIE_Enable(void)
{
     SET_BIT(GIE_SREG,I_bit);

}

void GIE_Disable(void)
{
 CLR_BIT(GIE_SREG,I_bit);

}


