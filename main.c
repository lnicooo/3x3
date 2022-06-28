#include <avr/io.h>
#include <avr/interrupt.h>

#include "animations.h"

uint8_t anim=0;

void initTimer1(){
  
  TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS12); //ps1024
  TCNT1 = 0;
  OCR1A = 1500; 

  TIMSK1 |= (1<<OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect){
  anim++;
  if(anim>192)
    anim=0;
}

int main(){
  
  uint16_t x;
  uint8_t layer=0;
  DDRB=0xFF;
  DDRC=0x3F;
  PORTB=0;
  PORTC=0;
  initTimer1();
  
  while(1){

    PORTB |= ((1<<layer)<<1); //PB1,PB2,PB3
    
    x=pgm_read_word(&animation[anim][layer]);   
    
    PORTC = (x&0x3f);//PC0 .. PC5

    //PORTB |= ((0x100>>8)&0x01);//PB0

    PORTB = ((x>>2)&0x30)|((x>>8)&0x01);//PB4, PB5
    
    
    
    layer++;

    if(layer>3)
      layer = 0;
    
  }


}
