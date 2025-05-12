#include <VarSpeedServo.h>

VarSpeedServo servoA; // Tutamaç için servo nesnesi (SG90)
VarSpeedServo servoX; // X ekseni için servo nesnesi (MG945)
VarSpeedServo servoY; // Y ekseni için servo nesnesi (MG945)
VarSpeedServo servoZ; // Z ekseni için servo nesnesi (MG995)

const int servoAPin = 7;   // Tutamaç servosunun bağlı olduğu pin //SG90
const int servoXPin = 8;   // X ekseni servosunun bağlı olduğu pin //MG945
const int servoYPin = 9;   // Y ekseni servosunun bağlı olduğu pin //MG945
const int servoZPin = 10;  // Z ekseni 360 derece servosunun bağlı olduğu pin //MG995

const int joystick1XPin = A0; // Joystick X ekseninin bağlı olduğu analog pin
const int joystick1YPin = A1; // Joystick Y ekseninin bağlı olduğu analog pin
const int joystick1Btn = 3; // Joystick X ekseninin bağlı olduğu Buton
const int joystick2Btn = 2; // Joystick X ekseninin bağlı olduğu Buton
const int joystick2XPin = A2; // Joystick X ekseninin bağlı olduğu analog pin
const int joystick2YPin = A3; // Joystick Y ekseninin bağlı olduğu analog pin

int btn1Durum=0;
int btn2Durum=0;

const int joystickOrtaMin = 400; // Joystick'in ortada olduğu minimum değer
const int joystickOrtaMax = 600; // Joystick'in ortada olduğu maksimum değer

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
      servo.write(90); // Sürekli dönüşlü servo için durma komutu     ==> MG995 <==    için
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
  joystickDegeri = 1023 - joystickDegeri;

  if (joystickDegeri < joystickOrtaMin) {


    hedefAcisi = map(joystickDegeri, 0, joystickOrtaMin, 0, 55);
    hedefAcisi = constrain(hedefAcisi, 0, 55);
    servo.write(hedefAcisi, 50);
  } else if (joystickDegeri > joystickOrtaMax) {
    hedefAcisi = map(joystickDegeri, joystickOrtaMax, 1023, 55, 90);
    hedefAcisi = constrain(hedefAcisi, 55, 90);
    servo.write(hedefAcisi, 50);
  } else {
      servo.stop(); // Pozisyonel servo için hareketi durdur MG945 içim
  }
}

void setup() {
  servoA.attach(servoAPin); // Tutamaç ekseni servosunu bağla
  servoX.attach(servoXPin); // X ekseni servosunu bağla
  servoY.attach(servoYPin); // Y ekseni servosunu bağla
  servoZ.attach(servoZPin); // Z ekseni servosunu bağla
  
  servoA.write(hedefAcisiA); // Y ekseni servosunu başlangıç pozisyonuna al
  servoX.write(hedefAcisiX); // X ekseni servosunu başlangıç pozisyonuna al
  servoY.write(hedefAcisiY); // Y ekseni servosunu başlangıç pozisyonuna al
  servoZ.write(hedefAcisiZ); // Y ekseni servosunu başlangıç pozisyonuna al

  pinMode(joystick1Btn, INPUT_PULLUP);
	pinMode(joystick2Btn, INPUT_PULLUP);

  Serial.begin(9600);       // Seri iletişimi başlat (debug için)
}

void tutamac()
{
  btn1Durum = digitalRead(joystick1Btn);
  btn2Durum = digitalRead(joystick2Btn);
  Serial.print(btn1Durum);
  Serial.print("\t");
  Serial.print(btn2Durum);
  Serial.print("\t");
  
  if(btn1Durum==false || btn2Durum==false )
  {
    servoA.write(90);
    Serial.print("Basıldı \t");
  }
  else
  {
    servoA.write(0);

    Serial.print("Bırakıldı \t");
  }

  Serial.println(servoA.read());

}

void loop() {
  int joystick1X = analogRead(joystick1XPin); // Joystick X ekseninden değer oku
  int joystick1Y = analogRead(joystick1YPin); // Joystick Y ekseninden değer oku
  int joystick2X = analogRead(joystick2XPin); // Joystick Y ekseninden değer oku
  int joystick2Y = analogRead(joystick2YPin); // Joystick Y ekseninden değer oku
 // tutamac();

/*
  Serial.print("Joystick X Değeri: ");
  Serial.print(joystick1X);
  Serial.print("\tJoystick Y Değeri: ");
  Serial.print(joystick1Y);
*/
  Serial.print("\t\tServo X Değeri: ");
  Serial.print(servoX.read());
  Serial.print("\tServo Y Değeri: ");
  Serial.println(servoY.read());
  

  // X ekseni servosunu kontrol et (MG945 olduğunu varsayıyoruz)
  kontrolServoSAG(joystick1X, servoX, hedefAcisiX);

  // Y ekseni servosunu kontrol et (MG945 olduğunu varsayıyoruz)
  kontrolServoSOL(joystick2X, servoY, hedefAcisiY);

  kontrolServoMERKEZ(joystick2Y, servoZ, hedefAcisiZ);

  delay(50); // Okumalar arasında kısa bir gecikme
}