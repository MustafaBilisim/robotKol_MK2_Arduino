#include <VarSpeedServo.h>

VarSpeedServo servoX; // X ekseni için servo nesnesi (MG995 varsayalım)
VarSpeedServo servoY; // Y ekseni için servo nesnesi (MG945 varsayalım)


const int servoAPin = 7;   // Uc tutamaç ekseni servosunun bağlı olduğu pin //SG90
const int servoXPin = 8;   // X ekseni servosunun bağlı olduğu pin //MG945
const int servoYPin = 9;   // Y ekseni servosunun bağlı olduğu pin //MG945
const int servoZPin = 10;  // Z ekseni 360 derece servosunun bağlı olduğu pin //MG995

const int joystick1XPin = A0; // Joystick X ekseninin bağlı olduğu analog pin
const int joystick1YPin = A1; // Joystick X ekseninin bağlı olduğu analog pin
const int joystick1Btn = 3; // Joystick X ekseninin bağlı olduğu analog pin
const int joystick2Btn = 2; // Joystick X ekseninin bağlı olduğu analog pin
const int joystick2XPin = A2; // Joystick Y ekseninin bağlı olduğu analog pin
const int joystick2YPin = A3; // Joystick X ekseninin bağlı olduğu analog pin

const int joystickOrtaMin = 460; // Joystick'in ortada olduğu minimum değer
const int joystickOrtaMax = 560; // Joystick'in ortada olduğu maksimum değer

int hedefAcisiA = 55; // X ekseni için başlangıç hedef açısı
int hedefAcisiX = 55; // X ekseni için başlangıç hedef açısı
int hedefAcisiY = 55; // Y ekseni için başlangıç hedef açısı
int hedefAcisiZ = 90; // X ekseni için başlangıç hedef açısı

// Joystick ekseninden okunan değeri alıp, ilgili servoyu kontrol eden fonksiyon
void kontrolServoMERKEZ(int joystickDegeri, VarSpeedServo& servo, int& hedefAcisi) {
  if (joystickDegeri < joystickOrtaMin) {
    hedefAcisi = map(joystickDegeri, 0, joystickOrtaMin, 5, 180);
    hedefAcisi = constrain(hedefAcisi, 5, 180);
    servo.write(hedefAcisi, 50);
  } else if (joystickDegeri > joystickOrtaMax) {
    hedefAcisi = map(joystickDegeri, joystickOrtaMax, 1023, 180, 355);
    hedefAcisi = constrain(hedefAcisi, 180, 355);
    servo.write(hedefAcisi, 50);
  } else {
      servo.write(90); // Sürekli dönüşlü servo için durma komutu MG995 için
  }
}

void kontrolServoSOL(int joystickDegeri, VarSpeedServo& servo, int& hedefAcisi) {
  if (joystickDegeri < joystickOrtaMin) {
    hedefAcisi = map(joystickDegeri, 0, joystickOrtaMin, 0, 45);
    hedefAcisi = constrain(hedefAcisi, 0, 45);
    servo.write(hedefAcisi, 50);
  } else if (joystickDegeri > joystickOrtaMax) {
    hedefAcisi = map(joystickDegeri, joystickOrtaMax, 1023, 45, 90);
    hedefAcisi = constrain(hedefAcisi, 45, 90);
    servo.write(hedefAcisi, 50);
  } else {
      servo.stop(); // Pozisyonel servo için hareketi durdur MG945 içim
  }
}

void kontrolServoSAG(int joystickDegeri, VarSpeedServo& servo, int& hedefAcisi) {
  if (joystickDegeri < joystickOrtaMin) {
    hedefAcisi = map(joystickDegeri, 0, joystickOrtaMin, 0, 55);
    hedefAcisi = constrain(hedefAcisi, 0, 55);
    servo.write(hedefAcisi, 50);
  } else if (joystickDegeri > joystickOrtaMax) {
    hedefAcisi = map(joystickDegeri, joystickOrtaMax, 1023, 55, 110);
    hedefAcisi = constrain(hedefAcisi, 55, 110);
    servo.write(hedefAcisi, 50);
  } else {
      servo.stop(); // Pozisyonel servo için hareketi durdur MG945 içim
  }
}

void setup() {
  servoA.attach(servoXPin); // X ekseni servosunu bağla
  servoX.attach(servoXPin); // X ekseni servosunu bağla
  servoY.attach(servoYPin); // Y ekseni servosunu bağla
  servoZ.attach(servoXPin); // X ekseni servosunu bağla
  
  servoA.write(hedefAcisiA); // Y ekseni servosunu başlangıç pozisyonuna al
  servoX.write(hedefAcisiX); // X ekseni servosunu başlangıç pozisyonuna al
  servoY.write(hedefAcisiY); // Y ekseni servosunu başlangıç pozisyonuna al
  servoZ.write(hedefAcisiZ); // Y ekseni servosunu başlangıç pozisyonuna al

  Serial.begin(9600);       // Seri iletişimi başlat (debug için)
}

void loop() {
  int joystick1X = analogRead(joystick1XPin); // Joystick X ekseninden değer oku
  int joystick1Y = analogRead(joystick1YPin); // Joystick Y ekseninden değer oku
  int joystick2X = analogRead(joystick2XPin); // Joystick Y ekseninden değer oku
  int joystick2Y = analogRead(joystick2YPin); // Joystick Y ekseninden değer oku
/*
  Serial.print("Joystick X Değeri: ");
  Serial.print(joystickXValue);
  Serial.print("\tJoystick Y Değeri: ");
  Serial.println(joystickYValue);
*/
  Serial.print("Servo X Değeri: ");
  Serial.print(servoX.read());
  Serial.print("\tServo Y Değeri: ");
  Serial.println(servoY.read());

  // X ekseni servosunu kontrol et (MG945 olduğunu varsayıyoruz)
  kontrolServo(joystickXValue, servoX, hedefAcisiX, false);

  // Y ekseni servosunu kontrol et (MG995 olduğunu varsayıyoruz)
  kontrolServo(joystickYValue, servoY, hedefAcisiY, true);

  delay(50); // Okumalar arasında kısa bir gecikme
}