
/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*/

#ifndef DOORS_MOVING_LIGHT_H_
#define DOORS_MOVING_LIGHT_H_


void Doors_init(void ) ;
void ALL_Doors_Closed(void) ;
u8 Select_Door(const u8 data ) ;

u8 Select_Moving_Way(u8 copy_data);
void Moving_Init(void) ;

u8 Light_Intensit(u8 copy_data);


#endif /* DOORS_MOVING_LIGHT_H_ */
