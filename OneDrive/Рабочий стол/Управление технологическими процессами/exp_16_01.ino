// Лаборатория электроники и программирования
// Эксперимент 16
// Балансир яркости двух светодиодов 
//

// контакты подключения потенциометра
const int pinPot=A0;
// контакты подключения светодиодов
const int pinLeftLed=10;
const int pinRightLed=11;
// переменные для хранения значений 
int valPot = 0; 
int valLeft = 0;
int valRight = 0;
 
void setup() {
   pinMode(pinLeftLed,OUTPUT);
   pinMode(pinRightLed,OUTPUT);
}

void loop() {
   // чтение данных A0 
   valPot = analogRead(pinPot); 
   // масштабирование
   valLeft=map(valPot,0,1023,255,0);
   valRight=map(valPot,0,1023,0,255);
   // вывод PWM
   analogWrite(pinLeftLed,valLeft);
   analogWrite(pinRightLed,valRight);
 }

