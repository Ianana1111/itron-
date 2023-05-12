#include <PS2X_lib.h>
#include <Servo.h>

int car_1 = 7;
int car_2 = 8;
int car_3 = 12;
int car_4 = 13;
int car_A = 5; // 控制1, 2 轉速
int car_B = 6; // 控制3, 4 轉速
int elong_1 = A5;  // 伸長
int elong_2 = A4;  // 伸長
int claw_1 = 3;   
int claw_2 = 5;
//int rotate = 9;
int light_right = A3;
int light_left = A2;

int elong_A = 10;
int claw_B = 9;
// 11 a0 a4 a5 
b
int error = 0;
byte type = 0;
byte vibrate = 0;
int IR = 0;

void movefront_car(){
    analogWrite(car_A, 150);
    analogWrite(car_B, 150);
    digitalWrite( car_1 , HIGH);
    digitalWrite( car_2 , LOW);
    digitalWrite( car_3 , HIGH);
    digitalWrite( car_4 , LOW);

}
void moveback_car(){
    analogWrite(car_A, 150);
    analogWrite(car_B, 150);
    digitalWrite( car_1 , LOW);
    digitalWrite( car_2 , HIGH);
    digitalWrite( car_3 , LOW);
    digitalWrite( car_4 , HIGH);
}

void movebackright_car(){
    analogWrite(car_A, 150);
    analogWrite(car_B, 150);
    digitalWrite( car_1 , LOW);
    digitalWrite( car_2 , LOW); 
    digitalWrite( car_3 , LOW);
    digitalWrite( car_4 , HIGH);
}

void movebackleft_car(){
    analogWrite(car_A, 150);
    analogWrite(car_B, 150);
    digitalWrite( car_1 , LOW);
    digitalWrite( car_2 , HIGH);
    digitalWrite( car_3 , LOW);
    digitalWrite( car_4 , LOW); 
}
void moveright_car(){
    analogWrite(car_A, 150);
    analogWrite(car_B, 150);
    digitalWrite( car_1 , LOW);
    digitalWrite( car_2 , LOW);
    digitalWrite( car_3 , HIGH);
    digitalWrite( car_4 , LOW); 
}

void moveleft_car(){
    analogWrite(car_A, 150);
    analogWrite(car_B, 150);
    digitalWrite( car_1 , HIGH);
    digitalWrite( car_2 , LOW);
    digitalWrite( car_3 , LOW);
    digitalWrite( car_4 , LOW);
}

void movestop_car(){
    digitalWrite( car_1 , LOW);
    digitalWrite( car_2 , LOW);
    digitalWrite( car_3 , LOW);
    digitalWrite( car_4 , LOW);
}

void movefront_elong(){
    analogWrite(elong_A, 150);
    digitalWrite( elong_1 , HIGH);
    digitalWrite( elong_2 , LOW);
}

void moveback_elong(){
    analogWrite(elong_A, 150);
    digitalWrite( elong_1 , LOW);
    digitalWrite( elong_2 , HIGH);
}
void movestop_elong(){
    digitalWrite( elong_1 , LOW);
    digitalWrite( elong_2 , LOW);
}

void movefront_claw(){
    analogWrite(claw_B, 150);
    digitalWrite( claw_1 , HIGH);
    digitalWrite( claw_2 , LOW);
}

void moveback_claw(){
    analogWrite(claw_B, 150);
    digitalWrite( claw_1 , LOW);
    digitalWrite( claw_2 , HIGH);
}
void movestop_elong(){
    digitalWrite( claw_1 , LOW);
    digitalWrite( claw_2 , LOW);
}


Servo myservo;
PS2X ps2x;

void setup() {
  Serial.begin(9600);
  do{
    error = ps2x.config_gamepad(13, 7, 3, 12, true, true);
    if(error){
      Serial.print("Gampad found!");
      break;
    }
  else  delay(100);
  }while(1);
  
  pinMode( car_1 ,OUTPUT);
  pinMode( car_2 ,OUTPUT);
  pinMode( car_3 ,OUTPUT);
  pinMode( car_4 ,OUTPUT);
  pinMode( car_A ,OUTPUT);
  pinMode( car_B ,OUTPUT);
  
  pinMode( elong_1 ,OUTPUT);
  pinMode( elong_2 ,OUTPUT);
  pinMode( claw_1 ,OUTPUT);
  pinMode( claw_2 ,OUTPUT);
  pinMode( light_right, INPUT);   
  pinMode( light_left, INPUT); 
  
//  myservo.attach( rotate );
}

int phase = 1;
void loop() {
  if(phase == 1){
    int sen_r = analogRead(light_right);
    int sen_l = analogRead(light_left);
  
    if(sen_r < 500 && sen_l < 500){
      moveback_car();
      delay(50);
      movestop_car();
      delay(150);
    }
    else if(sen_r > 500 && sen_l < 500) {
      moveleft_car();
      delay(50);
      movestop_car();
      delay(150);
   
    }
    else if(sen_r < 500 && sen_l > 500) {
    moveright_car();
    delay(50);
    movestop_car();
    delay(150);
    }
    else {
      movestop_car();
    }
  }else if(phase == -1){
    ps2x.read_gamepad(false, 0);
    if (ps2x.Button(PSB_PAD_UP)) {
      moveback_car();
    }
      
    if (ps2x.Button(PSB_PAD_DOWN)) {
      movefront_car();
    }
  
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      moveleft_car();
    }
  
    if (ps2x.Button(PSB_PAD_LEFT)) {
      moveright_car();
    }
    
    if(ps2x.Button(PSB_TRIANGLE))  {
      movefront_elong();        //三角按鍵  ->  控制往前凸
    }
  
    if(ps2x.Button(PSB_CROSS))  {
      moveback_elong();            //X按鍵  ->  控制往後凸
    }
  
    if(ps2x.Button(PSB_CIRCLE))  {
      movefront_claw();            //圓型按鍵  ->  控制往前
    }
  
    if(ps2x.Button(PSB_SQUARE))  {
      moveback_claw();             // 正方形  ->  控制往後
    }
  
    if(ps2x.Button(PSB_L1)) myservo.write(5);
  }
  phase = phase * -1;
}

  /*if(ps2x.ButtonPressed()){
    
  }*/
  
  //待修改

 /*if((digitalRead(light_right) == LOW) && (digitalRead(light_left) == LOW) ){
    //Serial.println("None\n");
    movefront_car();
    delay(100);
    movestop_car();
    delay(500);
  }
  else if((digitalRead(light_right) == LOW) && (digitalRead(light_left) == HIGH)) {
    //Serial.println("Left block\n");
    moveright_car();
    delay(100);
    movestop_car();
    delay(500);
  }
  else if((digitalRead(light_right) == HIGH) && (digitalRead(light_left) == LOW)) {
    //Serial.println("Right block\n");
    moveleft_car();
    delay(100);
    movestop_car();
    delay(500);
  }
  else {
    //Serial.println("Both block\n");
    movestop_car();
    delay(500);
  }*/
