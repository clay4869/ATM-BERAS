//--------------PIN---------------
#define buzz 3
#define en_mtr 4
#define fwr_mtr 5
#define rvs_mtr 6
#define limit A0



//-------------Motor-------------
const int speed_close = 50;
const int speed_open = 250;


//--------------Encoder & Limit-----------
bool encd, last_encd;
const int dgClose = 60;
const int dgOpen = 60;
bool limit_cond = 1;
bool var = 0;



//--------------Milis---------
unsigned long last_millis = 0;
unsigned long myTime = 0;
const int open_delay = 2000;

//---------Communication----
char serialOpen = ' ';

//------------BUZZ---------
#define buzz 3
#define gnd_buzz 2


void setup() {
  Serial.begin(115200);
  //--------PIN---------
  pinMode(en_mtr, OUTPUT);
  pinMode(fwr_mtr, OUTPUT);
  pinMode(rvs_mtr, OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(gnd_buzz, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(limit, INPUT_PULLUP);
}

void loop() {
  while (true) {
    if (Serial.available()) {
      serialOpen = Serial.read();
      if (serialOpen == '*') {
        Serial.println("SUKSES");
        break;
      }
      if (serialOpen == '!'){
        denied_buzz();
      }
      else {
        Serial.println("GAGAL");
      }
    }
  }
  Serial.println("FORWARD");
  while (true) {
    open_buzz();
    motor_open();
    limit_cond = digitalRead(limit);
    if (limit_cond == 0) {
      motor_lock();
      wait_buzz();
      motor_stop();
      break;
    }
  }
  Serial.println("REVERSE");
  while (true) {
    motor_close();
    delay(500);
    motor_stop();
    Serial.write('#');
    end_buzz();
    break;
  }
}


void motor_open() {
  analogWrite(fwr_mtr, speed_open);
  digitalWrite(en_mtr, HIGH);
  delay(500);
}
void motor_close() {
  analogWrite(rvs_mtr, speed_close);
  digitalWrite(en_mtr, HIGH);
}
void motor_stop() {
  analogWrite(fwr_mtr, 0);
  analogWrite(rvs_mtr, 0);
  digitalWrite(en_mtr, LOW);
}
void motor_lock() {
  analogWrite(fwr_mtr, 255);
  analogWrite(rvs_mtr, LOW);
  digitalWrite(en_mtr, HIGH);
}

void open_buzz() {
  analogWrite(buzz, 200);
  delay(200);
  analogWrite(buzz, LOW);
  delay(200);
  analogWrite(buzz, 200);
  delay(200);
  analogWrite(buzz, LOW);
  delay(1000);

}
void wait_buzz() {
  analogWrite(buzz, 200);
  delay(1000);
  analogWrite(buzz, LOW);
  delay(500);
  analogWrite(buzz, 200);
  delay(1000);
  digitalWrite(buzz, LOW);
  delay(1500);
}
void end_buzz() {
  analogWrite(buzz, 200);
  delay(500);
  analogWrite(buzz, LOW);
}

void denied_buzz(){
  analogWrite(buzz, 200);
  delay(50);
  analogWrite(buzz, LOW);
  delay(50);
  analogWrite(buzz, 200);
  delay(50);
  analogWrite(buzz, LOW);
  delay(50);
}
