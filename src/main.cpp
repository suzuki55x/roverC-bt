#include <M5StickC.h>
#include "RoverC.h"
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// 動作用ステート
#define STATE_STOP 0
#define STATE_GOAHEAD 1
#define STATE_BACKOFF 2
#define STATE_TURNRIGHT 3
#define STATE_TURNLEFT 4
#define STATE_MOVERIGHT 5
#define STATE_MOVELEFT 6

BluetoothSerial SerialBT;

void setup() {
  M5.begin();

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.setCursor(30, 30, 4);
  M5.Lcd.printf("RoverC");

  SerialBT.begin("RoverC-1"); //Bluetooth device name
  SerialBT.println("The device started, now you can pair it with bluetooth!");

  RoverC_Init();
  Move_stop(100);
}

void loop() {
    M5.update();
   if (M5.BtnA.wasReleased()) {
      delay(1500); 
      Servo_angle(1, 90);
      delay(1000);
      Move_back(50);
      delay(2000);
      Move_turnleft(30);
      delay(2000);
      Move_turnright(30);
      delay(2000);
      Move_forward(50);
      delay(2000);
      Move_stop(100);
      Servo_angle(1, 0);
      delay(1000); 
  }
  if (SerialBT.available()) {
    uint8_t read_char = SerialBT.read();
    switch (read_char) {
      case STATE_GOAHEAD:
        Move_forward(50);
        break;
      case STATE_BACKOFF:
        Move_back(50);
        break;
      case STATE_MOVELEFT:
        Move_left(50);
        break;
      case STATE_MOVERIGHT:
        Move_right(50);
        break;
      case STATE_TURNLEFT:
        Move_turnleft(50);
        break;
      case STATE_TURNRIGHT:
        Move_turnright(50);
        break;
      case STATE_STOP:
      default:
        Move_stop(100);
        break;
    }
  }
}