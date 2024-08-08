/* Imports */
#include <MicroBit.h>
#include <math.h>

/* Global Variables */
MicroBit hBit;
static const int DELAY_MS = 60000;
int is_paused = 0;

/* Function Prototypes */ 
void session(int length);
void pause_pressed(MicroBitEvent);

int main(int argc, char **argv) {
  hBit.init();
  hBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, pause_pressed);

  hBit.display.scroll("START");

  session(25);

  hBit.display.scroll("BREAK");

  session(5);

  hBit.display.clear();
  hBit.display.scroll("END");
}

/* Functions */
void session(int length) {
  for (int i = length; i > 0; i--) {
    // Paused
    while (is_paused == 1) {
      hBit.sleep(1000);
    }

    int num_rows = ceil((double) i / 5);
    int num_in_last_row = i % 5 == 0 ? 5 : i % 5;
    
    hBit.display.print(i);

    hBit.sleep(1000);

    hBit.display.clear();

    for (int row = 0; row < num_rows; row++) {
      int num_columns = row == num_rows - 1 ? num_in_last_row : 5;

      int column = 0;

      for (column = 0; column < num_columns; column++) {
        hBit.display.image.setPixelValue(row, column, 125);
      }

      // Remove the turned off ones
      for (int off_col = row; off_col < 5; off_col++) {
        hBit.display.image.setPixelValue(off_col, column, 0);
      }
    }

    hBit.sleep(DELAY_MS); 
  }
}

void pause_pressed(MicroBitEvent) {
  if (is_paused == 0) {
    hBit.display.scroll("PAUSED");
    is_paused = 1;
  }
  else {
    hBit.display.scroll("RESUMED");
    is_paused = 0;
  }
}
