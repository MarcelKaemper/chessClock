#include <Eventually.h>
#include <LiquidCrystal.h>

const int buzzer = 12;
const int b1=8,b2=9,b3=10,b4=11;
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int index = 0;
int times[] = { 30,60,120,300,600};
int turn = 0;
int lastTimes[2];
int time1=times[0], time2=times[0];

// 0=setup, 1=game
int mode = 0;

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
  mgr.addListener(new EvtPinListener(b2, 300,  (EvtAction)buttonTwo));
  mgr.addListener(new EvtPinListener(b3, 300,  (EvtAction)buttonThree));
  mgr.addListener(new EvtPinListener(b4,  (EvtAction)buttonFour));
  mgr.addListener(new EvtTimeListener(1000, true, (EvtAction)tick));

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(time1);
  lcd.setCursor(0,1);
  lcd.print(time2);
}

//Player 1
bool buttonOne(){
  turn = 1;
  return true;
}

// Change time
bool buttonTwo(){
  if(mode == 0){
    if(index <= 3){
      index = index + 1;
    }else{
      index = 0;
    }
  time1 = times[index];
  time2 = times[index];
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(time1);
  lcd.setCursor(0,1);
  lcd.print(time2);
  }


  return true;
}

// Start/pause
bool buttonThree(){
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);

  if(mode == 0){
     // If game restarted/Time different than before pause
     if(lastTimes[0] != time1 || lastTimes[1] != time2){
      turn = 0;
     }
    mode = 1;
  }else{
    lastTimes[0] = time1;
    lastTimes[1] = time2;
    mode = 0;
  }
  return true;
}

//Player 2
bool buttonFour(){
  turn = 0;
  return true;
}

bool tick(){
  if(mode == 1){
    if(!turn){
      time1--;
    }else{
      time2--;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(time1);
    lcd.setCursor(0,1);
    lcd.print(time2);
    if(time1 <= 0 || time2 <= 0){
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(2000);
      mgr.resetContext();
    }
  }


  return true;
}

USE_EVENTUALLY_LOOP(mgr)
