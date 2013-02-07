#include <stdlib.h>

#include "phoboz/ctrl.h"

int get_input(void)
{
  int input = 0;
  Uint8 *keys = SDL_GetKeyState(NULL);

  if(keys[SDLK_ESCAPE])
    input=SET_BITS(input,PRESS_ESC);

  if(keys[SDLK_UP])
    input=SET_BITS(input,PRESS_UP);

  if(keys[SDLK_RIGHT])
    input=SET_BITS(input,PRESS_RIGHT);

  if(keys[SDLK_LEFT])
    input=SET_BITS(input,PRESS_LEFT);

  if(keys[SDLK_DOWN])
    input=SET_BITS(input,PRESS_DOWN);

  if(keys[SDLK_SPACE])
    input=SET_BITS(input,PRESS_JUMP);

  if(keys[SDLK_LCTRL])
    input=SET_BITS(input,PRESS_ATTACK);

  return input;
}

int get_input_keydown(int ks)
{
  int input = 0;

   switch(ks)
   {
      case SDLK_ESCAPE:
	 input=SET_BITS(input,PRESS_ESC);
	 break;
      case SDLK_UP:
         input=SET_BITS(input,PRESS_UP);
         break;
      case SDLK_RIGHT:
         input=SET_BITS(input,PRESS_RIGHT);
         break;
      case SDLK_LEFT:
         input=SET_BITS(input,PRESS_LEFT);
         break;
      case SDLK_DOWN:
         input=SET_BITS(input,PRESS_DOWN);
         break;
      case SDLK_SPACE:
         input=SET_BITS(input,PRESS_JUMP);
         break;
      case SDLK_LCTRL:
         input=SET_BITS(input,PRESS_ATTACK);
         break;
      default: break;
   }

   return input;
}

int get_input_keyup(int ks)
{
  int input = 0;

   switch(ks)
   {
      case SDLK_ESCAPE:
	 input=RESET_BITS(input,PRESS_ESC);
	 break;
      case SDLK_UP:
         input=RESET_BITS(input,PRESS_UP);
         break;
      case SDLK_RIGHT:
         input=RESET_BITS(input,PRESS_RIGHT);
         break;
      case SDLK_LEFT:
         input=RESET_BITS(input,PRESS_LEFT);
         break;
      case SDLK_DOWN:
         input=RESET_BITS(input,PRESS_DOWN);
         break;
      case SDLK_SPACE:
         input=RESET_BITS(input,PRESS_JUMP);
         break;
      case SDLK_LCTRL:
         input=RESET_BITS(input,PRESS_ATTACK);
         break;
      default: break;
   }

   return input;
}

