- used  Bluetooth (virtual terminal in proteus) to control motion, lighting, speed, doors, and temperature                                    
- ATMEGA32 as master Responsible to rceive char through UART protocol  and send it through SPI protocol                                       
- ATMEGA32 as Slave Responsible to rceive char through (ISR) SPI protocol  from master and Processes this data                                     
- 4 doors by using 4 LED and 4 Servo Motor  on the Same pwm signal timer1 by use DEMUX to select which one will work                                    
- 2 led in front onf pwm signal on timer0                                                                                                     
- 2 led in back  pwm signal on timer2                                                                                                                          
- control motion by  2 motor and use motor H-Bridge                                                                                                                        
- LM35 TEM Sensor on ADC0                                                                                                                                
- LCD 4*20                                                                                                                                       

---------------------------------------------------------------------------------------------
- string of light                                                                                                                                 
- LFI# ---> Increase front light
- LFD# ---> Decrease front light                                                                     
- LBI# ---> Increase back light
- LBD# ---> Decrease back light      

---------------------------------------------------------------------------------------------

- string of Doors                                                                                                                                
- D1OPEN# ---> DOOR 1 OPEN                                                                                                                                     -
- D1CLOSE# ---> DOOR 1 CLOSE                                                                               
- D2OPEN# ---> DOOR 2 OPEN                                                                             
- D2CLOSE# ---> DOOR 2 CLOSE                                                                                                                                                           
- D3OPEN# ---> DOOR 3 OPEN                                                                             
 - D3CLOSE# ---> DOOR 3 CLOSE                                                                                                                                                            
- D4OPEN#  ---> DOOR 4 OPEN                                                                             
- D4CLOSE# ---> DOOR 4 CLOSE                                                                                  

---------------------------------------------------------------------------------------------

- string of Motion                                                                                                                                
- MF# --->  Moving Forward                                                                             
- MB# --->   Moving Back                                                                                                                                                           
- MR# --->  Moving Right                                                                             
- ML#   --->  Moving Left
- MS#   ---> Stoped                                                                                     

---------------------------------------------------------------------------------------------


 
