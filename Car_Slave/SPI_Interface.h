
#ifndef SPI_SPI_INT_H_
#define SPI_SPI_INT_H_


void SPI_voidInit(void);
u8   SPI_voidTransiver(u8);
u8 SPI_voidReceiveChar(u8 *Copy_u8Data);
void SPI_VoidSendChar(u8 Copy_U8_Data);

u8 SPI_voidReceiveStr(u8 *Copy_u8Data) ;

void SPI_voidSetCallBack(  void (*ptr_spi)(void) );

#endif /* SPI_SPI_INT_H_ */
