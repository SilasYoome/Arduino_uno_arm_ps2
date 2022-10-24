#include "Emakefun_MotorDriver.h"
#include "PS2X_lib.h"  //for v1.6
#include "DFRobotDFPlayerMini.h"
//#include "SoftwareSerial.h"

#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

long time = 0;

PS2X ps2x; // create PS2 Controller Class
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);
Emakefun_DCMotor* DCMotor_1 = mMotorDriver.getMotor(M1);
Emakefun_DCMotor* DCMotor_2 = mMotorDriver.getMotor(M2);
Emakefun_DCMotor* DCMotor_3 = mMotorDriver.getMotor(M3);
Emakefun_DCMotor* DCMotor_4 = mMotorDriver.getMotor(M4);

int speed_val = 255;
void setup()
{
  Serial.begin(9600);
  mMotorDriver.begin(50);
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  int ps2_error = 0;
  int player_error = 0;
  do {
    ps2_error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    if (ps2_error == 0) {
      break;
    }
    else {
      delay(100);
    }
  } while (1);

}

void loop()
{
  ps2x.read_gamepad(false, 0);
  delay(30);
  if (ps2x.NewButtonState() == false) {
    if (ps2x.Button(PSB_START)){}
    if (ps2x.Button(PSB_SELECT)){}

    if (ps2x.Button(PSB_PAD_UP)) {
      DCMotor_1->setSpeed(200);
      DCMotor_1->run(FORWARD);
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(FORWARD);
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(BACKWARD);
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      DCMotor_1->setSpeed(200);
      DCMotor_1->run(BACKWARD);
    }
  }
  else {
    DCMotor_1->run(BRAKE);
    DCMotor_2->run(BRAKE);
    DCMotor_3->run(BRAKE);
    DCMotor_4->run(BRAKE);
  }
  if (ps2x.ButtonPressed(PSB_SQUARE)) {
    DCMotor_3->setSpeed(speed_val);
    DCMotor_3->run(FORWARD);
  }
  if (ps2x.ButtonPressed(PSB_CROSS)) {

    DCMotor_4->setSpeed(speed_val);
    DCMotor_4->run(FORWARD);
  }
  if (ps2x.ButtonPressed(PSB_CIRCLE)) {
    DCMotor_3->setSpeed(speed_val);
    DCMotor_3->run(BACKWARD);
  }
  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
    DCMotor_4->setSpeed(speed_val);
    DCMotor_4->run(BACKWARD);
  }
}