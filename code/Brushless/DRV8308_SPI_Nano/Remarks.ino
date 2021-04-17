/*
 * 
 * Motorparameter für getestete Motoren
 */
 /*
// Motorparameter for others (default Values)
                 
#define Reg00 0b1001101101100101   
//                  ^ ^   ^^
//                 EN BRK SPI-MODE: 01=PWM , 10=RegisterPWM

#define Reg01 30                    
#define Reg02 0b0000001110110100   
#define Reg03 0b0000111110000010   
#define Reg04 0b0000110010000001   

#define Reg05 0b0011000000000111   
#define Reg06 0b0000010010110000   
#define Reg07 950
#define Reg08 300
#define Reg09 600
#define Reg0A 0b00110011100101100
#define Reg0B 0
*/

/* Ardumower BL
// Motorparameter                  // ACT 42BL  53W
#define Reg00 0b1001001101100101   // 0b1001101101100001
//                  ^^^   ^^
//                 EN BRK SPI-MODE: 01=PWM , 10=RegisterPWM
//                   Dir
#define Reg01 30                   
#define Reg02 0b0000001110110100    
#define Reg03 0b1110100000000000    // MOD 120 = 2048(0b0101100000000000) if MOD 120 = 3970 use 0b0101111110000010
#define Reg04 0b0000010010010010     
#define Reg05 0b0011100000000111    
#define Reg06 0b0000010010110000    
#define Reg07 950
#define Reg08 0b0000000100101100      //300
#define Reg09 0b0000001001011000      //600
#define Reg0A 0b10000011100101100
#define Reg0B 0

 */

/*
 * Parameter für Matrix MOW 800 ; Fahrmotor 45ZW24-30 Messermotor 45ZW24-20
#define Reg00 0b1001101001010001   // 0b1001101101100001
#define Reg01 40                   // 30 
#define Reg02 0b0000001110110100   // 0b0000001110110100
#define Reg03 0b0000111110000010   // 0b0111111110000010
#define Reg04 0b0001011100010001    // Matrix MOW 800 45ZW2430 
#define Reg05 0b0011000000000111   // 0b0011000000000111
#define Reg06 0b0000010010110000   // 0b0000010010110000
#define Reg07 950
#define Reg08 300
#define Reg09 600
#define Reg0A 0b00110011100101100
#define Reg0B 0*/
