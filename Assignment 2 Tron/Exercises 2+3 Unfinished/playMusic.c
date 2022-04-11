#include <mc9s12dp256.h>

int period;


void play_note(int freq,int duration);
void delay_ms(unsigned int k);

int find_freq(char input); 
int findduration(char note);

//----------------------------------------------Description---------------------------------------------//
// This function work by concidering the bit values of the inputed charecters. The division of bits
// is shown in the below figure:
//
//                          8 bit data structure; _ _  _ _  _ _ _ _ 
//                                                Oc   Du   Note(12 notes + a rest)   
//
// Given this, the corseponding frequency is found by concidering the inputed notes and inputed octive 
// which is sent to the speaker. The duration of the note is then determined and sent to the delay function. 
//------------------------------------------------------------------------------------------------------// 

                  
void playMusic(char* Notes){
	 
  int i;
  
  // turn LED on to indicate that the music is being played  
  DDRB = 0xFF;
  PORTB = 0xFF;
  
  // play each note
  for (i = 0; i<8; i++){
    char current_note = Notes[i];
    
    // determine the frequency and duration of each note
    int freq = find_freq(current_note);              // if the inputed charecter is undefined the freq = 20
    int duration = findduration(current_note);         // determine the input 
  
    play_note(freq, duration);                       
  }
  
  
  // turn LED on to indicate that the music is being played  
  PORTB = 0;

}


int find_freq(char input){
  
  unsigned char note_mask = 0x0F; // Concider these bit 00001111
  unsigned int note_index = (note_mask & input); // only concider the last 4 bits, giving values from 0-15 
  int notes[16]= {2868, 2707, 2555, 2412, 2277, 2149, 2028, 1914, 1807, 1706, 1609, 1519, 0, 0, 0,  0}; // octave 3 freq for each note
    
  unsigned char octave_mask = 0xC0; // Concider these bit 11000000
  unsigned int octave_index = (octave_mask & input) >> (6); // only concider the first 2 bits, giving values 0-3  
    

  signed int freq = notes[note_index] * (1<<octave_index);
  
  return freq;
}


int findduration(char note){
  int index = 0;
  
  unsigned char mask = 0x30; // Concider these bit 00110000
  unsigned int duration_index = (mask & note) >> (4); // shift over 4 places so we get 0-3
  
  int corresponding_duration[4]= {500, 1000, 2000, 4000}; // defined four durations, eight, quater, half, full of a four second note
  
  return corresponding_duration[duration_index];
}

void play_note(int freq,int duration){

	// Disable all interrupts
	asm("sei");
	
	// Enable timer and fast flag clear
	TSCR1 = 0x90; 
	
	// Set prescaler to 8
	TSCR2 = 0x03;     //00000011
	
	// Choose output compare for channel 5
	TIOS = 0x20;      //00100000
	
	// Toggle upon successful output compare 
	TCTL1 = 0x04;     //
	
	// Enable interrupts for timer 5
	TIE = 0x20;
	
	
	period = freq;
	
	if (freq == 0){                   // if the frequency is set to 0 this inducates a rest. to do this turn the speaker off
	    TIOS = 0;
	}
	
  delay_ms(duration);               // Wait for the defined duration of the song 
  
  
  TIOS = 0;                         //turn off the speaker
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