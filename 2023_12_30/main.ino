#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <math.h>

int Error_margin = 20;  // コンパスの誤差

Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);  // コンパスピン設定
void setup() {
  // put your setup code here, to run once:

  // コンパス関連
  Wire.begin();
  bno.begin();
  // シリアル関連
  Serial.begin(9600);
  // ピン関連
  pinMode(11, INPUT_PULLUP);
  pinMode(12, OUTPUT);

  delay(1000);  // コンパス待機

  digitalWrite(12, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(11) == HIGH) {
    //analogWrite(8,212);
    //analogWrite(9,255);
    //delay(1500);
    analogWrite(8, 0);
    analogWrite(9, 0);
    while (1) {
      // digitalWrite(12,HIGH);

      // 変数
      int A0 = analogRead(0);
      int A1 = analogRead(1);
      int A2 = analogRead(2);
      int A3 = analogRead(3);
      int A4 = analogRead(4);
      int A5 = analogRead(5);
      int A6 = analogRead(6);
      int A7 = analogRead(7);  //Ball(前)
      int A8 = analogRead(8);  //Line(前)




      int Ball_min = min(A6, A4);

      // コンパス
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

      if (A8 >= 160) {  //ラインに触れているとき
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 125);
        analogWrite(8, 0);
        analogWrite(9, 0);
        analogWrite(10, 150);
      } else {

        // 姿勢制御
        if (360 - Error_margin <= (int)floor(euler.x()) || (int)floor(euler.x()) <= 0 + Error_margin) {  // ロボットが中心地からずれていないとき
                                                                                                         /*          
                  A2 
          A3 --------------  A5
             |            |
             |            |
          A7 |            |  A4
             |            | 
             |            |
          A6 --------------  A0
                  A1

        */
          if (abs(A7 - A4) <= 80 && A1 >= A2 && A2 <= 800) {                                             //左と右のボールセンサーが80の範囲で等しく、前にボールがあるとき
            analogWrite(5, 0);
            analogWrite(6, 0);
            analogWrite(7, 0);
            analogWrite(8, 125);
            analogWrite(9, 150);
            analogWrite(10, 0);
          } else if (abs(A7 - A4) >= 80 && A1 >= A2) {  //ロボットの左前or右前にあり、前にボールがあるとき
            if(A7<=A4){
              Horizontal_movement(1);  //左に横移動
            }else{
              Horizontal_movement(2);  //右に横移動
            }
          } else {
            analogWrite(5, 0);
            analogWrite(6, 0);
            analogWrite(7, 0);
            analogWrite(8, 0);
            analogWrite(9, 0);
            analogWrite(10, 0);
          }
        } else if (360 - Error_margin >= (int)floor(euler.x()) && (int)floor(euler.x()) >= 181) {  // ロボットが中心地よりも左側にずれているとき
          analogWrite(5, 0);
          analogWrite(6, 50);
          analogWrite(7, 0);
          analogWrite(8, 50);
          analogWrite(9, 0);
          analogWrite(10, 50);
        } else if (180 >= (int)floor(euler.x()) && (int)floor(euler.x()) >= 0 + Error_margin) {  // ロボットが中心地よりも右側にずれているとき
          analogWrite(5, 50);
          analogWrite(6, 0);
          analogWrite(7, 50);
          analogWrite(8, 0);
          analogWrite(9, 50);
          analogWrite(10, 0);
        } /*else {
          analogWrite(5, 0);
          analogWrite(6, 0);
          analogWrite(7, 0);
          analogWrite(8, 0);
          analogWrite(9, 0);
          analogWrite(10, 0);
        }*/
      }
    }  // これより下にはコードは記述しない(関数を除く)
  }
}
void Horizontal_movement(int direction) {
  switch (direction) {
    case 1:
      analogWrite(5, 0);
      analogWrite(6, 100);
      analogWrite(7, 48);
      analogWrite(8, 0);
      analogWrite(9, 60);
      analogWrite(10, 0);
      break;
    case 2:
      analogWrite(5,100);
      analogWrite(6,0);
      analogWrite(7,0);
      analogWrite(8,48);
      analogWrite(9,0);
      analogWrite(10,0);
    case 3
  }
}
