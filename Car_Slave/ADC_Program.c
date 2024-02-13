/*
 * ADC_Program.c
 *
 *  Created on: Aug 18, 2022
 *      Author: General
 */



/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "ADC_Config.h"
#include "ADC_Private.h"





/*****************************************************************************************/
#ifdef ISR_ENABEL

static void (*ADC_CallBack)(void) = {NULL};
static u16 * ADC_po16DataResult = NULL ;

ACD_ERROR_RETURN ADC_voidSetCallBack(u16 *copy_po16Data, void (*ptr_adc)(void) )
{

	ACD_ERROR_RETURN local_error =OK ;
	/*TO get ADC data */
	if( copy_po16Data != NULL )
	{
		ADC_po16DataResult =copy_po16Data ;
	}
	else
	{
		local_error =NULL_ERROR ;
	}

	/*FOR notification */
	if(ptr_adc!=NULL)
	{
		ADC_CallBack=ptr_adc;
	}
	else
	{
		local_error =NULL_ERROR ;
	}

	return  local_error ;
}


/*****************************************************************************************/


void __vector_16() __attribute__((signal)) ;
void __vector_16 ()
{
	if(ADC_po16DataResult != NULL)
	{
		/*TO get ADC data */

#if TYPE_DATA ==RIGHT_DATA
		//store data from REG ( ADC_DATA )  to copy_Pu8Data
		(*ADC_po16DataResult) = ADC_DATA     ;
#elif TYPE_DATA ==LEFT_DATA

		(*ADC_po16DataResult) = (ADC_DATA>>6) ;
#endif

	}

	if(ADC_CallBack != NULL)
	{
		/*FOR notification */
		ADC_CallBack();
	}



}
#endif
/*****************************************************************************************/

void ADC_voidInit()
{
	ADMUX_REG->ADLAR = TYPE_DATA ;

	ADMUX_REG->REFS  = REF_VOLT  ;

	ADCSRA_REG->ADPS = PRSCALLER ;

	ADCSRA_REG->ADEN = EN        ;

#ifdef ISR_ENABEL
	ADCSRA_REG->ADIE = EN        ;
#endif


#ifdef TRIGGER_ENABEL
	ADCSRA_REG->ADATE =EN ;
	SFIOR_REG->SFIOR_ADTS = TRIGGER_SOURCE;
#endif

}

/*****************************************************************************************/

/* Sellect one ADC Channel to work */
ACD_ERROR_RETURN ADC_voidChannelSellect(ACD_CHANNEL_NUM copy_u8ChannelSellect )
{
	ACD_ERROR_RETURN local_error =OK ;
	if( ( copy_u8ChannelSellect<=7 )   )
	{


		ADMUX_REG->MUX = copy_u8ChannelSellect ;
	}
	else
	{
		local_error =NUM_OUT_OF_RANGE ;
	}

	return local_error ;

}

/*****************************************************************************************/

/* Start Conversion on ADC Channel  Sellected */
ACD_ERROR_RETURN ADC_StartConversionBoling(u16 *copy_Pu8Data)
{
	u32 counter =0 ;
	ACD_ERROR_RETURN local_error =OK ;

	if(copy_Pu8Data != NULL)
	{
		// Start Conversion --- bit H
		ADCSRA_REG->ADSC = 1 ;
		// wait for flag
		while ( (ADCSRA_REG->ADIF ==0) &&counter<=TIME_OUT )
		{
			counter ++ ;
		}
		if((ADCSRA_REG->ADIF) ==1 )
		{
			// Clear flag
			ADCSRA_REG->ADIF = 1 ;

        #if TYPE_DATA ==RIGHT_DATA
			//store data from REG ( ADC_DATA )  to copy_Pu8Data
			(*copy_Pu8Data) = ADC_DATA     ;
        #elif TYPE_DATA ==LEFT_DATA

			(*copy_Pu8Data)=((u16)ADC_DATA>>6) ;
       #endif
		}

		else
		{
			local_error=TIME_OUT_ERROR ;
		}

	}

	else
	{
		local_error=NULL_ERROR ;
	}
	return  local_error ;
}
/*****************************************************************************************/
void ADC_StartConversion(void)
{
	// Start Conversion --- bit H
	ADCSRA_REG->ADSC = 1 ;
}
/*****************************************************************************************/



/* Read all   ADC Channel and store it in array */
ACD_ERROR_RETURN ADC_voidChannelMulBoling(u16 *copy_Pu8Data)
{
	u8 i =4 ;
	ACD_ERROR_RETURN local_error =OK ;
	if(copy_Pu8Data!=NULL)
	{
		while(i!=0)
		{
			i-- ;
			ADC_voidChannelSellect(i);
			local_error =ADC_StartConversionBoling( (&copy_Pu8Data[i]) ) ;


		/*  if(local_error== TIME_OUT_ERROR)
			{
				local_error =ADC_StartConversionBoling( (&copy_Pu8Data[i]) ) ;
			}*/

		}

	}
	else
	{
		local_error =NULL_ERROR ;
	}

	return  local_error ;
}


/*****************************************************************************************/



u16 ADC_Mapping( u16 x1 ,u16 x2 , u16 y1 ,u16 y2)
{
	u16 data ;
	u16 local_adc_data = 0 ;
#if TYPE_DATA ==RIGHT_DATA
	//store data from REG ( ADC_DATA )  to copy_Pu8Data
	local_adc_data = ADC_DATA     ;

#elif TYPE_DATA ==LEFT_DATA

	local_adc_data=((u16)ADC_DATA>>6) ;
#endif

	data =( ( (u32)(local_adc_data-x1)*(y2-y1) ) / (x2-x1) ) +y1 ;

	return  data ;
}

/*****************************************************************************************/

/*****************************************************************************************/



