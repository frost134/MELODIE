/*
 * swu166_project.c
 *
 * Created: 2019/2/7 21:14:03
 * Author : frost
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "keypad.h"
#include "bit.h"
#include "timer.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "MAX7219_Matrix.c"
#include "MAX7219.c"
#include "stdlib.h"

enum Main_State{Start, menu, score_display, count_A, count_B} mainState;
unsigned char sequence = 0;
int scoreA = 1;
double Convert_Key_to_Note()
{
    
    switch(GetKeypadKey())
    {
        case '1': return 523.25; break;
        case '2': return 587.33; break;
        case '3': return 659.25; break;
        case '4': return 698.46; break;
        case '5': if(mainState == count_A && sequence >= 27){return 391.99;} return 783.99; break;
        case '6': return 880.00; break;
        case '7': return 987.77; break;
        case '8': return 1046.50; break;
        case '9': return 1174.66; break;
        case '0': return 1318.51; break;
        default: return 0.00; break;
    }
}
void set_PWM(double frequency) {

    static double current_frequency;

    if (frequency != current_frequency) {

        if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter

        else { TCCR0B |= 0x03; } // resumes/continues timer/counter

        if (frequency < 0.954) { OCR0A = 0xFFFF; }

        else if (frequency > 31250) { OCR0A = 0x0000; }

        else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

        TCNT0 = 0;

        current_frequency = frequency;

    }

}

void PWM_on() {

    TCCR0A = (1 << COM0A0) | (1 << WGM00);

    TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);

    set_PWM(0);

}

void PWM_off() {

    TCCR0A = 0x00;

    TCCR0B = 0x00;

}
void displayBlank()
{
    MAX7219_MatrixInit();
    MAX7219_MatrixUpdate();
}
void displayTitle()
{
    MAX7219_MatrixInit();
    MAX7219_MatrixSetRow64(0, logo[3]);
    MAX7219_MatrixSetRow64(1, logo[2]);
    MAX7219_MatrixSetRow64(2, logo[1]);
    MAX7219_MatrixSetRow64(3, logo[0]);
    MAX7219_MatrixUpdate();
}
void displayFin()
{
    MAX7219_MatrixInit();
    MAX7219_MatrixSetRow64(0, symbol[5]);
    MAX7219_MatrixSetRow64(1, Atoz[13]);
    MAX7219_MatrixSetRow64(2, Atoz[8]);
    MAX7219_MatrixSetRow64(3, Atoz[5]);
    MAX7219_MatrixUpdate();
}
uint64_t rank_analyse(int a);
void displayRank()
{
    MAX7219_MatrixInit();
    MAX7219_MatrixSetRow64(3, rank[0]);
    MAX7219_MatrixSetRow64(2, rank[1]);
    MAX7219_MatrixSetRow64(1, rank[2]);
    MAX7219_MatrixSetRow64(0, rank_analyse(scoreA));
    MAX7219_MatrixUpdate();
}
void waitTime(int timeee)
{
    int a = 0;
    while (a < timeee)
    {
        a++;
        while (!TimerFlag){}
        TimerFlag = 0;
    }
}
uint64_t trans(char a)
{
    switch (a)
    {
        case '0':return symbol[2]; break;
        case '1':return numbers[1]; break;
        case '2':return numbers[2]; break;
        case '3':return numbers[3]; break;
        case '4':return numbers[4]; break;
        case '5':return numbers[5]; break;
        case '6':return numbers[6]; break;
        case '7':return numbers[7]; break;
        case '8':return numbers[8]; break;
        case '9':return numbers[9]; break;
        case 'a':return numbers[0]; break;
        default: return symbol[2]; break;
    }
}
uint64_t rank_analyse(int a)
{
    if(a > 1550){return Atoz[18];}
    if(a > 1400){return Atoz[0];}
    if(a > 1250){return Atoz[1];}
    if(a > 1000){return Atoz[2];}    
    if(a > 750){return Atoz[3];}
    return Atoz[4];
}
void set_bar_pos(int a)
{
    switch(a)
    {
        case 1: MAX7219_MatrixSetRow64(2, bar[1]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 2: MAX7219_MatrixSetRow64(2, bar[2]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 3: MAX7219_MatrixSetRow64(2, bar[3]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 4: MAX7219_MatrixSetRow64(2, bar[4]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 5: MAX7219_MatrixSetRow64(2, bar[5]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 6: MAX7219_MatrixSetRow64(2, bar[6]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 7: MAX7219_MatrixSetRow64(2, bar[7]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 8: MAX7219_MatrixSetRow64(2, bar[8]);MAX7219_MatrixSetRow64(1, bar[0]);break;
        case 9: MAX7219_MatrixSetRow64(2, bar[9]);MAX7219_MatrixSetRow64(1, bar[1]);break;
        case 10: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[2]);break;
        case 11: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[3]);break;
        case 12: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[4]);break;
        case 13: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[5]);break;
        case 14: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[6]);break;
        case 15: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[7]);break;
        case 16: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[8]);break;
        case 17: MAX7219_MatrixSetRow64(2, bar[0]);MAX7219_MatrixSetRow64(1, bar[9]);break;
        default:MAX7219_MatrixSetRow64(2, symbol[2]); MAX7219_MatrixSetRow64(1, symbol[2]); break;
    }
}
uint64_t bar_position(int a)
{
    switch(a)
    {
        case 1: return test[1];break;
        case 2: return test[2];break;
        case 3: return test[3];break;
        case 4: return test[4];break;
        case 5: return test[5];break;
        case 6: return test[6];break;
        case 7: return test[7];break;
    }
}
unsigned char menuFlag = 0;
unsigned char test01[] = {'1','2','3','1','1','2','3','1','3','4','5','3','4','5','5','6','5','4','3','1','5','6','5','4','3','1','2','5','1','2','5','1'};
unsigned short test02[] = {50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,100 ,50 ,50 ,100 ,25 ,25 ,25 ,25 ,50 ,50 ,25 ,25 ,25 ,25 ,50 ,50, 50, 50, 100, 50, 50, 100 };
unsigned char key = 0;
//unsigned char sequence = 0;
//int scoreA = 1;
char intStr[10];
void Tick1()
{
    switch(mainState)
    {
        case Start: {mainState = menu; break;}
        case menu: {
            if(GetKeypadKey() == 'A'){mainState = count_A; sequence = 0; itoa(scoreA, intStr, 10);LCD_DisplayString(1, intStr); break;}
            else if(GetKeypadKey() == 'B'){mainState = count_B; break;}
            else{break;}
        }
        case score_display:{
            itoa(scoreA, intStr, 10);
            LCD_DisplayString(1, intStr);
            MAX7219_MatrixInit();
            MAX7219_MatrixUpdate();
            waitTime(200);
            for (int i = 0; i < 4; i++)
            {
                displayFin();
                waitTime(80);
                displayBlank();
                waitTime(80);
            }
            displayRank();
            waitTime(600);
            while(1){if(GetKeypadKey()!='\0')break;}
            
            mainState = menu;
            break;
        }        
        case count_A: 
            MAX7219_MatrixInit();
            MAX7219_MatrixUpdate();
            if(sequence >= sizeof(test01)/sizeof(test01[0])){mainState = score_display;}
            break;
        case count_B: mainState = menu; break;
        default: break;
    }
    switch(mainState)
    {
        case Start: menuFlag =0; break;
        case menu:
            if (menuFlag == 0)
            {
                itoa(scoreA, intStr, 10);
                LCD_DisplayString(1, "A = test_song, B = SenbonZakura");
                //LCD_DisplayString(1, intStr);
                for (int i = 0; i < 3; i++)
                {
                    displayTitle();
                    waitTime(20);
                    displayBlank();
                    waitTime(20);
                }
                displayTitle();             
            }
            if (GetKeypadKey() == '*')
            {
                MAX7219_MatrixLShift(1);
                MAX7219_MatrixUpdate();
            }
            if (GetKeypadKey() == '#')
            {
                MAX7219_MatrixRShift(1);
                MAX7219_MatrixUpdate();
            }
            menuFlag = 1;
            scoreA = 0;
            break;
            
        case count_A:
            menuFlag = 0;
            //LCD_DisplayString(1,"test_song");
            if(sequence == 0)
            {
                MAX7219_MatrixSetRow64(3,symbol[2]);
                MAX7219_MatrixSetRow64(0,trans(test01[0]));
                MAX7219_MatrixUpdate();
                waitTime(100);
                MAX7219_MatrixInit();
                MAX7219_MatrixUpdate();
            }
            unsigned int j = 1;
            for (int i = 1; i <= test02[sequence]*1.75; i++)
            {
                while (!TimerFlag){}
                TimerFlag = 0;
                
                if (i == 1)
                {
                    MAX7219_MatrixSetRow64(3,trans(test01[sequence]));
                    //MAX7219_MatrixSetRow64(2,test[1]);
                    if(sequence<31){MAX7219_MatrixSetRow64(0,trans(test01[sequence+1]));}
                    else{MAX7219_MatrixSetRow64(0,symbol[2]);}
                    MAX7219_MatrixUpdate();
                }
                //MAX7219_MatrixRShift(32/test02[sequence]);
                if(GetKeypadKey()==test01[sequence])
                {
                    scoreA = scoreA + 1;              
                }
                if (i % 10 ==0)
                {
                    set_bar_pos(j);
                    j++;
                }
                if (i%5 == 0)
                {
                    MAX7219_MatrixUpdate();
                }
                if (i %20 == 0){
                    itoa(scoreA, intStr, 10);
                    LCD_DisplayString(1, intStr);
                }                
            }
            
            sequence++;
        break;
        default: menuFlag = 0; break;
    }

	

}



int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    DDRA = 0xF0; PORTA = 0x0F; //KEYPAD!!!!
    DDRB = 0xFF; PORTB = 0x00;//PWM
    LCD_init();
    MAX7219_MatrixInit();
    MAX7219_MatrixUpdate();
	TimerSet(5);
	TimerOn();
	mainState = Start;
    PWM_on();

	while(1){

		key = GetKeypadKey();
		Tick1();
		
	}
}

