#include <Arduino.h>

// Define
// SS=超音波センサー
// L=左、R=右、C=センター、B=後ろ、E=エコー、T=トリガー
#define SS_L_E_PIN 2
#define SS_L_T_PIN 3
#define SS_R_E_PIN 4
#define SS_R_T_PIN 5
#define PR_L1_PIN A0
#define PR_L2_PIN A1
#define PR_R1_PIN A2
#define PR_R2_PIN A3
#define PR_C_PIN A4

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
int l;
int r;
// 超音波センサー
double SS_L_DU = 0;
double SS_L_DI = 0;
double SS_R_DU = 0;
double SS_R_DI = 0;

// シリアルから流れ込んでくるmicroからのi2cのデータを読む
void readserial() {
  if (Serial.available() > 0) {
    String tmp = Serial.readStringUntil('\n');
    l = tmp.toInt() / 10;
    r = tmp.toInt() - l * 10;
  }
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