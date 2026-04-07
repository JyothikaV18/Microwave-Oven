/*
 * File:   main.c
 * Author: jyoth
 *
 * Created on March 21, 2026, 10:50 PM
 */

/*
 * Name : Jyothika Vijayakumar
 * Date : 21/03/2026
 * Project : Microwave Oven
 */

//PORTb PORTD TRISB predefined as address
#include "main.h"

void init_config(void)
{
    //To initialize timer2
    init_timer2();
    //To initialize clcd
    init_clcd();
    //To initialize matrix keypad
    init_matrix_keypad();
    //To enable global interrupt
    GIE = 1;
    //To enable external peripheral interrupt
    PEIE = 1;
    //To direct RC1 as output and enable buzzer
    TRISC1 = 0;
    //To direct RC1 as output and enable fan
    TRISC2 = 0;
    //To call power up screen on reset/power on
    power_up();
}

void main(void)
{
    init_config();
    
    unsigned char key;
    unsigned char micr, gril, convec, strt;
    unsigned char control_flag = MENU_SCREEN, reset_flag = RESET_NOTHING;
    
    while(1)
    {
        key = read_matrix_keypad(STATE);
        
        if(control_flag == MENU_SCREEN && key != ALL_RELEASED)
        {
            if(key == 1)
            {
                control_flag = MICRO;
                clear_screen();
                clcd_print("Power = 900W", LINE2(2));
                __delay_ms(1000);
                clear_screen();
                reset_flag = RESET_MICRO;
            }
            else if(key == 2)
            {
                control_flag = GRILL;
                clear_screen();
                reset_flag = RESET_GRILL;
            }
            else if(key == 3)
            {
                control_flag = CONVECTION;
                clear_screen();
                reset_flag = RESET_CONVEC;
            }
            else if(key == 4)
            {
                control_flag = START;
                clear_screen();
                reset_flag = RESET_START;
            }
        }
        
        switch(control_flag)
        {
            //To display menu screen
            case MENU_SCREEN:
                menu_screen();
                break;
            //Micro mode
            case MICRO:
                micr = micro(key, reset_flag);
                
                if(micr == RETURN_BACK)
                {
                    control_flag = MENU_SCREEN;
                    clear_screen();
                }
                break;
            //Grill mode
            case GRILL:
                gril = grill(key, reset_flag);
                
                if(gril == RETURN_BACK)
                {
                    control_flag = MENU_SCREEN;
                    clear_screen();
                }
                break;
            //Convection mode
            case CONVECTION:
                convec = convection(key, reset_flag);
                
                if(convec == RETURN_BACK)
                {
                    control_flag = MENU_SCREEN;
                    clear_screen();
                }
                break;
            //Start mode
            case START:
                strt = start(key, reset_flag);
                
                if(strt == RETURN_BACK)
                {
                    control_flag = MENU_SCREEN;
                    clear_screen();
                }
                break;
        }
        reset_flag = RESET_NOTHING;
    }
    return;
}