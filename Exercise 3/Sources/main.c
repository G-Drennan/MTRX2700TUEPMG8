#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
  

int period;

__interrupt void speakerISR();
__interrupt void UnimplementedISR(void);

void play_note(int freq,int duration);
void delay_ms(unsigned int k);

int find_freq(int i, char* Notes);
int find_duration(int i, char* Notes);

//----------------------------------------------Main---------------------------------------------//

                  
void main(void){
	              //  A     b     c      D    E     F     G     R     //Cap = 2 sec, Lower = 1 sec
	char Notes[8] = {0x41, 0x62, 0x63, 0x44, 0x45, 0x46, 0x47, 0x52}; // Temp input from terminal 
  int i;
  
  // determine how long the string will play for
  int song_length = 0;
  for (i = 0; i<8; i++){
    
    song_length = song_length + find_duration(i, Notes);         // sum the duration of each note 
                                                                 // to give the length of the song 
  }
                                                                 //output the final result to the termninal ***** 
 
  // play each note
  for (i = 0; i<8; i++){
    
    // determine the frequency and duration of each note
    int freq = find_freq(i, Notes);              // if the inputed charecter is undefined the freq = 20
    int duration = find_duration(i, Notes);         // determine the input 
  
    play_note(freq, duration);                       // the 
  }

    for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

//-----------------------------------------Sub-Functions-----------------------------------------//

int find_freq(int i, char* Notes){
  
  char current_note = Notes[i];
  volatile int index = 0;
  
  char valid_input[16] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x52,      // define all valid 
                          0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x72};     // char inputs
  int corresponding_freq[16]= {3411, 3039, 5737, 5111, 4553, 4298, 3829,  0,   // define their
                               3411, 3039, 5737, 5111, 4553, 4298, 3829,  0};  // corresponding freq
  
  // loop through each valid input to determine the corresponding frequency 
  int j=0; 
  for(j=0 ; j < 16 ; j++){
    if(valid_input[j] == current_note){
      index = j;                                                      // record the index
    }
  }
  
  return corresponding_freq[index];                                   // return the found frequency 
}

int find_duration(int i, char* Notes){
  char current_note = Notes[i];
  volatile int index = 0;
  
  char valid_input[16] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x52,
                          0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x72}; 
  int corresponding_duration[16]= {2000, 2000, 2000, 2000, 2000, 2000, 2000,  2000,
                                   1000, 1000, 1000, 1000, 1000, 1000, 1000,  1000};
  
  int j=0; 
  for(j=0 ; j < 16 ; j++){
    if(valid_input[j] == current_note){
      index = j; 
    }
  }
  
  return corresponding_duration[index];
}

void play_note(int freq,int duration){
  // Disable all interrupts
	asm("sei");
	
	// Enable timer and fast flag clear
	TSCR1 = 0x90; 
	
	// Set prescaler to 8
	TSCR2 = 0x03;
	
	// Choose output compare for channel 5
	TIOS = 0x20;
	
	// Toggle upon successful output compare 
	TCTL1 = 0x04; 
	
	// Start with high frequency
	period = freq;
	
	// Enable interrupts for timer 5
	TIE = 0x20;
	
	// Set first output compare to happen
	TC5 = TCNT + period;
	EnableInterrupts;
	

  delay_ms(duration);     // Wait half a second
  period = freq;          // Switch to low frequency

}


void delay_ms(unsigned int time){
    int i,j;
    for(i=0;i<time;i++)
      for(j=0;j<4000;j++);
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void speakerISR() 
{
  TC5 = TC5 + period;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void UnimplementedISR(void)
{
   /* Unimplemented ISRs trap.*/
   asm BGND;
}

typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFF80 = {     /* Interrupt table */
        UnimplementedISR,                 /* vector 0x40 */
        UnimplementedISR,                 /* vector 0x3F */
        UnimplementedISR,                 /* vector 0x3E */
        UnimplementedISR,                 /* vector 0x3D */
        UnimplementedISR,                 /* vector 0x3C */
        UnimplementedISR,                 /* vector 0x3B */
        UnimplementedISR,                 /* vector 0x3A */
        UnimplementedISR,                 /* vector 0x39 */
        UnimplementedISR,                 /* vector 0x38 */
        UnimplementedISR,                 /* vector 0x37 */
        UnimplementedISR,                 /* vector 0x36 */
        UnimplementedISR,                 /* vector 0x35 */
        UnimplementedISR,                 /* vector 0x34 */
        UnimplementedISR,                 /* vector 0x33 */
        UnimplementedISR,                 /* vector 0x32 */
        UnimplementedISR,                 /* vector 0x31 */
        UnimplementedISR,                 /* vector 0x30 */
        UnimplementedISR,                 /* vector 0x2F */
        UnimplementedISR,                 /* vector 0x2E */
        UnimplementedISR,                 /* vector 0x2D */
        UnimplementedISR,                 /* vector 0x2C */
        UnimplementedISR,                 /* vector 0x2B */
        UnimplementedISR,                 /* vector 0x2A */
        UnimplementedISR,                 /* vector 0x29 */
        UnimplementedISR,                 /* vector 0x28 */
        UnimplementedISR,                 /* vector 0x27 */
        UnimplementedISR,                 /* vector 0x26 */
        UnimplementedISR,                 /* vector 0x25 */
        UnimplementedISR,                 /* vector 0x24 */
        UnimplementedISR,                 /* vector 0x23 */
        UnimplementedISR,                 /* vector 0x22 */
        UnimplementedISR,                 /* vector 0x21 */
        UnimplementedISR,                 /* vector 0x20 */
        UnimplementedISR,                 /* vector 0x1F */
        UnimplementedISR,                 /* vector 0x1D */
        UnimplementedISR,                 /* vector 0x1C */
        UnimplementedISR,                 /* vector 0x1B */
        UnimplementedISR,                 /* vector 0x1A */
        UnimplementedISR,                 /* vector 0x19 (PORT H) */
        UnimplementedISR,                 /* vector 0x18 (PORT J) */
        UnimplementedISR,                 /* vector 0x17 (ATD1) */
        UnimplementedISR,                 /* vector 0x16 (ATD0) */
        UnimplementedISR,                 /* vector 0x15 (SCI1) */
        UnimplementedISR,                 /* vector 0x14 (SCI0) */
        UnimplementedISR,                 /* vector 0x13 */
        UnimplementedISR,                 /* vector 0x12 */
        UnimplementedISR,                 /* vector 0x11 */
        UnimplementedISR,                 /* vector 0x10 (TOF) */
        UnimplementedISR,                 /* vector 0x0F (TIE, C7I)  */
        UnimplementedISR,                 /* vector 0x0E (TIE, C6I)  */
        speakerISR,                       /* vector 0x0C (TIE, C5I)  */
        UnimplementedISR,                 /* vector 0x0C (TIE, C4I)  */
        UnimplementedISR,                 /* vector 0x0B (TIE, C3I)  */
        UnimplementedISR,                 /* vector 0x0A (TIE, C2I)  */
        UnimplementedISR,                 /* vector 0x09 (TIE, C1I)  */
        UnimplementedISR,                 /* vector 0x08 (TIE, C0I) */
        UnimplementedISR,                 /* vector 0x07 (RTIE) */
        UnimplementedISR,                 /* vector 0x06 */
        UnimplementedISR,                 /* vector 0x05 */
        UnimplementedISR,                 /* vector 0x04 */
        UnimplementedISR,                 /* vector 0x03 */
        UnimplementedISR,                 /* vector 0x02 */
        UnimplementedISR,                 /* vector 0x01 */
       // _Startup                          /* vector 0x00 (RESET) */
   };

