#ifndef LCDManager_h
#define LCDManager_h

#include <LiquidCrystal_I2C.h>

class LCDManager {
private:
    LiquidCrystal_I2C lcd;
    int columns;
    int rows;

public:
    LCDManager(uint8_t lcdAddr, int columns, int rows);
    void init();
    void displayMessage(String line1, String line2);
    void clear();
};

#endif
