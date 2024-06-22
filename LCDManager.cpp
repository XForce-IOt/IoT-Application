#include "LCDManager.h"

LCDManager::LCDManager(uint8_t lcdAddr, int columns, int rows) 
    : lcd(lcdAddr, columns, rows), columns(columns), rows(rows) {}

void LCDManager::init() {
    lcd.init();
    lcd.backlight();
}

void LCDManager::displayMessage(String line1, String line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    if (rows > 1) {
        lcd.setCursor(0, 1);
        lcd.print(line2);
    }
}

void LCDManager::clear() {
    lcd.clear();
}
