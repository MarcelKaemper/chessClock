#include <Eventually.h>
#include <LiquidCrystal.h>

const int b1=8,b2=9,b3=10,b4=11;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

EvtManager mgr;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  mgr.addListener(new EvtPinListener(b1 40, LOW, (EvtAction)buttonOne));
  mgr.addListener(new EvtPinListener(b2, 40, LOW, (EvtAction)buttonTwo));
  mgr.addListener(new EvtPinListener(b3, 40, LOW, (EvtAction)buttonThree));
  mgr.addListener(new EvtPinListener(b4, 40, LOW, (EvtAction)buttonFour));
}

bool buttonOne(){
  return true;
}

bool buttonTwo(){
  return true;
}

bool buttonThree(){
  return true;
}

bool buttonFour(){
  return true;
}

USE_EVENTUALLY_LOOP(mgr)
