#include <Eventually.h>
#include <LiquidCrystal.h>

const int buzzer = 12;
const int b1=8,b2=9,b3=10,b4=11;
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int turn = 0;
int time1=30, time2=30;

EvtManager mgr;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(buzzer, OUTPUT);
  mgr.addListener(new EvtPinListener(b1,  (EvtAction)buttonOne));
  mgr.addListener(new EvtPinListener(b2,  (EvtAction)buttonTwo));
  mgr.addListener(new EvtPinListener(b3,  (EvtAction)buttonThree));
  mgr.addListener(new EvtPinListener(b4,  (EvtAction)buttonFour));
  mgr.addListener(new EvtTimeListener(1000, true, (EvtAction)tick));
}

bool buttonOne(){
  turn = 1;
  return true;
}

bool buttonTwo(){
  return true;
}

bool buttonThree(){
  return true;
}

bool buttonFour(){
  turn = 0;
  return true;
}

bool tick(){
  if(!turn){
    time1--;
  }else{
    time2--;
  }
  if(time1 <= 0 || time2 <= 0){
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    mgr.resetContext();
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println(time1);
  lcd.setCursor(0,1);
  lcd.println(time2);
  return true;
}

USE_EVENTUALLY_LOOP(mgr)
