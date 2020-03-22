/*

  u8x8_debounce.c
  
  Key/button simple debounce algorithm (Addon for u8x8)
  
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
*/

#include "u8x8.h"



/*
  State A:
    u8x8->debounce_last_pin_state == current_state 
      --> State A
    u8x8->debounce_last_pin_state != current_state 
      --> u8x8->debounce_last_pin_state = current_state 
      --> State B + cnt

  State B + cnt
    --> state--

  State B
    u8x8->debounce_last_pin_state == current_state 
      --> keypress detected
      --> State C
    u8x8->debounce_last_pin_state != current_state 
      --> State A

  State C
    u8x8->debounce_last_pin_state == current_state 
      --> State C
    u8x8->debounce_last_pin_state != current_state 
      --> State A

*/
 char test_buttons(void)//(int *testear_boton)
  { 
   // revisar_timer();
   // if (*testear_boton == 1)
   // {
      int dataan = analogRead(0);
//      Serial.println("dato an:");
//      Serial.println(datoan);
      if (dataan > 20)
      {
        if (dataan > 650 && dataan < 1024)//izquierda
        {
  
          //         void U8G2::clearDisplay(void)  ; u8g2.clearBuffer();
          //         u8g2.drawStr("DERECHA",1,1);
            return 'p';
        }
        else if (dataan > 300 && dataan < 650)//enter
        {
          //          void U8G2::clearDisplay(void)  ; u8g2.clearBuffer();
          //          u8g2.drawStr("Enter",1,1);
         return 's';
        }
        else if (dataan > 150 && dataan < 300)  //derecha
        {
  
          //              void U8G2::clearDisplay(void)  ; u8g2.clearBuffer();
          //              u8g2.drawStr("Enter",1,1);
          return 'n';
        }
      }
      else
      {
         return 'z';
      }
   //   *testear_boton = 0;
   // }
  }


#ifdef __unix__xxxxxx_THIS_IS_DISABLED

#include <stdio.h>
#include <stdlib.h>
uint8_t u8x8_GetMenuEvent(void)
{
    yield();
    int c;
    c = test_buttons();//getc(stdin);
    switch(c)
    {
        case 'n':
            return  U8X8_MSG_GPIO_MENU_NEXT;
        case 'p':
            return  U8X8_MSG_GPIO_MENU_PREV;
        case 's':
            return  U8X8_MSG_GPIO_MENU_SELECT;
        case 'h':
            return  U8X8_MSG_GPIO_MENU_HOME;
        case 'x':
      //      exit(0);
        default:
            puts("press n, p, s, h or x");
            break;
    }
    return 0;
}


#else  /* __unix__ */


#define U8X8_DEBOUNCE_WAIT 2
/* do debounce and return a GPIO msg which indicates the event */
/* returns 0, if there is no event */
#ifdef  __GNUC__
# pragma weak  u8x8_GetMenuEvent
#endif
uint8_t u8x8_GetMenuEvent(u8x8_t *u8x8)
{
    yield();
    int c;
    c = test_buttons();//getc(stdin);
    switch(c)
    {
        case 'n':
            return  U8X8_MSG_GPIO_MENU_NEXT;
        case 'p':
            return  U8X8_MSG_GPIO_MENU_PREV;
        case 's':
            return  U8X8_MSG_GPIO_MENU_SELECT;
        case 'h':
            return  U8X8_MSG_GPIO_MENU_HOME;
        case 'x':
           // exit(0);
        default:
            puts("press n, p, s, h or x");
            break;
    }
    return 0;
}

#endif /* __unix__ */>
