#include "hal.h"

int main() {
  halCreate(); 

  printFont(128, 128, "elo ziomy", 1);
  while(1) {
   /* switch(eState) {
      case STATE_MENU: menuLoop(); break;
      case STATE_GAME: gameLoop(); break;
    }*/
  }
  halDestroy(); 

  return 0;
}