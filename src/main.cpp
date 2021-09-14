#include <Arduino.h>

// Define
// SS=超音波センサー
// R=右、L=左、E=エコー、T=トリガー
#define SS_L_E_PIN 2
#define SS_L_T_PIN 3
#define SS_R_E_PIN 4
#define SS_R_T_PIN 5

// 変数定義
// カラーセンサー系
int lr;
int lg;
int lb;
int lir;
int rr;
int rg;
int rb;
int rir;
// 超音波センサー
double SS_L_DU = 0;
double SS_L_DI = 0;
double SS_R_DU = 0;
double SS_R_DI = 0;

// 任意の文字で区切る関数
int split(String data, char delimiter, String *dst) {
  int index = 0;
  int arraySize = (sizeof(data) / sizeof((data)[0]));
  int datalength = data.length();
  for (int i = 0; i < datalength; i++) {
    char tmp = data.charAt(i);
    if (tmp == delimiter) {
      index++;
      if (index > (arraySize - 1))
        return -1;
    } else
      dst[index] += tmp;
  }
  return (index + 1);
}

// シリアルから流れ込んでくるmicroからのi2cのデータを読む
void readserial() {
  String tmp = Serial.readStringUntil('\n');
  String *spltmp;
  split(tmp, '\n', spltmp);
  lr = spltmp[0].toInt();
  lg = spltmp[1].toInt();
  lb = spltmp[2].toInt();
  lir = spltmp[3].toInt();
  rr = spltmp[4].toInt();
  rg = spltmp[5].toInt();
  rb = spltmp[6].toInt();
  rir = spltmp[7].toInt();
}

// 超音波センサーの値を読む
void readsonic() {
  digitalWrite(SS_L_T_PIN, LOW);
  digitalWrite(SS_R_T_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SS_L_T_PIN, HIGH);
  digitalWrite(SS_R_T_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS_L_T_PIN, LOW);
  digitalWrite(SS_R_T_PIN, LOW);
  SS_L_DU = pulseIn(SS_L_E_PIN, HIGH);
  SS_R_DU = pulseIn(SS_R_E_PIN, HIGH);
  if (SS_L_DU > 0) {
    SS_L_DI = SS_L_DU * 340 * 100 / 1000000 / 2;
  }
  if (SS_R_DU > 0) {
    SS_R_DI = SS_R_DU * 340 * 100 / 1000000 / 2;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(SS_L_E_PIN, INPUT);
  pinMode(SS_L_T_PIN, OUTPUT);
  pinMode(SS_R_E_PIN, INPUT);
  pinMode(SS_R_T_PIN, OUTPUT);
}

void loop() {
  readserial();
  readsonic();
}