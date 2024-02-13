/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/
 /*****************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



/***********************************************************/
typedef enum
{
	CHANNEL_0 = 0x00 ,
	CHANNEL_1 = 0x01 ,
	CHANNEL_2 = 0x02 ,
	CHANNEL_3 = 0x03 ,
	CHANNEL_4 = 0x04 ,
	CHANNEL_5 = 0x05 ,
	CHANNEL_6 = 0x06 ,
	CHANNEL_7 = 0x07
}ACD_CHANNEL_NUM;

typedef enum
{
	NULL_ERROR      ,
	TIME_OUT_ERROR  ,
	OK              ,
	NUM_OUT_OF_RANGE

}ACD_ERROR_RETURN;
/***********************************************************/

void ADC_voidInit();

/**********************************************************/
ACD_ERROR_RETURN ADC_voidChannelSellect(ACD_CHANNEL_NUM copy_u8ChannelSellect);

/***********************************************************/
 void ADC_StartConversion(void);
/***********************************************************/

ACD_ERROR_RETURN  ADC_StartConversionBoling(u16 *copy_Pu8Data);

/***********************************************************/

ACD_ERROR_RETURN ADC_voidChannelMulBoling(u16 *copy_Pu8Data);


/*********************************************************/

ACD_ERROR_RETURN ADC_voidSetCallBack(u16 *copy_po16Data,void(*PTR)(void));


/********************************************************/
u16 ADC_Mapping( u16 x1 ,u16 x2 , u16 y1 ,u16 y2) ;

#endif /* ADC_INTERFACE_H_ */
