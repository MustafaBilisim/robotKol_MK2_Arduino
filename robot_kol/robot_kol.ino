#include <VarSpeedServo.h>

VarSpeedServo servoX; // X ekseni için servo nesnesi (MG995 varsayalım)
VarSpeedServo servoY; // Y ekseni için servo nesnesi (MG945 varsayalım)

const int servoXPin = 8;   // X ekseni servosunun bağlı olduğu pin
const int servoYPin = 9;   // Y ekseni servosunun bağlı olduğu pin
const int joystickXPin = A0; // Joystick X ekseninin bağlı olduğu analog pin
const int joystickYPin = A2; // Joystick Y ekseninin bağlı olduğu analog pin

const int joystickOrtaMin = 460; // Joystick'in ortada olduğu minimum değer
const int joystickOrtaMax = 560; // Joystick'in ortada olduğu maksimum değer

int hedefAcisiX = 90; // X ekseni için başlangıç hedef açısı
int hedefAcisiY = 90; // Y ekseni için başlangıç hedef açısı

// Joystick ekseninden okunan değeri alıp, ilgili servoyu kontrol eden fonksiyon
void kontrolServo(int joystickDegeri, VarSpeedServo& servo, int& hedefAcisi, bool surekliDonus) {
  if (joystickDegeri < joystickOrtaMin) {
    hedefAcisi = map(joystickDegeri, 0, joystickOrtaMin, 0, 90);
    hedefAcisi = constrain(hedefAcisi, 0, 90);
    servo.write(hedefAcisi, 50);
  } else if (joystickDegeri > joystickOrtaMax) {
    hedefAcisi = map(joystickDegeri, joystickOrtaMax, 1023, 90, 180);
    hedefAcisi = constrain(hedefAcisi, 90, 180);
    servo.write(hedefAcisi, 50);
  } else {
    if (surekliDonus) {
      servo.write(90); // Sürekli dönüşlü servo için durma komutu
    } else {
      servo.stop(); // Pozisyonel servo için hareketi durdur
    }
  }
}

void setup() {
  servoX.attach(servoXPin); // X ekseni servosunu bağla
  servoY.attach(servoYPin); // Y ekseni servosunu bağla
  servoX.write(hedefAcisiX); // X ekseni servosunu başlangıç pozisyonuna al
  servoY.write(hedefAcisiY); // Y ekseni servosunu başlangıç pozisyonuna al
  Serial.begin(9600);       // Seri iletişimi başlat (debug için)
}

void loop() {
  int joystickXValue = analogRead(joystickXPin); // Joystick X ekseninden değer oku
  int joystickYValue = analogRead(joystickYPin); // Joystick Y ekseninden değer oku
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

  // X ekseni servosunu kontrol et (MG995 olduğunu varsayıyoruz)
  kontrolServo(joystickXValue, servoX, hedefAcisiX, true);

  // Y ekseni servosunu kontrol et (MG945 olduğunu varsayıyoruz)
  kontrolServo(joystickYValue, servoY, hedefAcisiY, false);

  delay(50); // Okumalar arasında kısa bir gecikme
}
