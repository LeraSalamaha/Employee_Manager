// Лаборатория электроники и программирования
// Эксперимент 17
// Радуга на RGB-светодиоде 
//

// пауза перед каждым изменением цвета радуги
#define MAX_PAUSE 30
#define MIN_PAUSE 1
// пин подключения среднего вывода потенциометра
const int PIN_POT=A0;
// вывод красной ноги RGB-светодиода 
const int RED=11; 
// вывод зеленой ноги RGB-светодиода 
const int GREEN=10; 
// вывод синей ноги RGB-светодиода 
const int BLUE=9; 
// переменная для хранения значения потенциометра 
int pot; 
// переменная для хранения R-составляющей цвета 
int red; 
// переменная для хранения G-составляющей цвета 
int green; 
// переменная для хранения B-составляющей цвета 
int blue; 

void setup() 
   {;}

void loop() {
   // от красного к желтому
   red=255;green=0;blue=0;
   for(green=0;green<=255;green++)
      setRGB(red,green,blue);
   // от желтому к зеленому
   for(red=255;red>=0;red--)
      setRGB(red,green,blue);
   // от зеленого к голубому
   for(blue=0;blue<=255;blue++)
      setRGB(red,green,blue);
   // от голубого к синему
   for(green=255;green>=0;green--)
      setRGB(red,green,blue);
   // от синего к фиолетовому
   for(red=0;red<=255;red++)
      setRGB(red,green,blue);
   delay(2000);
} 
// функция установки цвета RGB-светодиода
void setRGB(int r,int g,int b) {
   analogWrite(RED,r);
   analogWrite(GREEN,g);
   analogWrite(BLUE,b);
   pot=analogRead(PIN_POT);
   delay(map(pot,0,1023, MIN_PAUSE, MAX_PAUSE));
}

