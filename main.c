#include <msp430.h> 
#include <pitches.h>

int melody[] = {
NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5,
NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
NOTE_G4, 0, NOTE_G4, NOTE_D5,
NOTE_C5, 0, NOTE_AS4, 0,
NOTE_A4, 0, NOTE_A4, NOTE_A4,
NOTE_C5, 0, NOTE_AS4, NOTE_A4,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
NOTE_G4, 0, NOTE_G4, NOTE_D5,
NOTE_C5, 0, NOTE_AS4, 0,
NOTE_A4, 0, NOTE_A4, NOTE_A4,
NOTE_C5, 0, NOTE_AS4, NOTE_A4,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
NOTE_G4,0, NOTE_G4, NOTE_AS5,
NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
};

int noteDurations[] = {
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,4,
};

unsigned int thisnote = 0;

void Play_songs();
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;				// Stop watchdog timer

    P8DIR |= BIT1;
    P3DIR |= BIT6;

    P1REN |= BIT2;
    P1OUT |= BIT2;

    P1REN |= BIT3;
    P1OUT |= BIT3;

    while(1)
    {
    	if(P1IN & BIT2){}
    	else
    	{
    	    Play_songs();
    	}
    	thisnote=0;
    }
}

void Play_songs()
{
    while(1)
    {
        TA0CTL |= MC_1 + TASSEL_2 + TACLR; 
        TA0CCTL0 = CCIE;
        if(melody[thisnote]==0){}
        else
        {
            TA0CCR0  = 1000000/melody[thisnote];
            __enable_interrupt();
        }
        thisnote++;

        if(noteDurations[thisnote]==4)
        {
            __delay_cycles(250000);
        }
        else if(noteDurations[thisnote]==8)
        {
            __delay_cycles(125000);
        }

        if(thisnote>=112)
        {
            __disable_interrupt();
            break;
        }
        if(P1IN & BIT3){}
        else
        {
            __disable_interrupt();
            break;
        }
    }
    return;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P3OUT ^= BIT6;
}
