// Лаборатория электроники и программирования
// Эксперимент 5
// Два светофора на перекрестке.
//

// Выводы Arduino для подключения светодиодов
// список
// [green1,yellow1,red1,green2,yellow2,red2]
int pinleds[6]={7,8,9,10,11,12};

// время горения светодиодов в мсек
// зеленый
#define TIME_GREEN 5000   
// красный
#define TIME_RED 5000
// желтый
#define TIME_YELLOW 3000
// период мигания желтого
#define TIME_BLINK  300
// переменная blink для чередования мигания желтого
boolean blinkyellow=true;

void setup() 
  {
  // настроить выводы Arduino как выходы
  // и потушить все светодиоды
  for(int i=0;i<6;i++)
     {
     pinMode(pinleds[i], OUTPUT);
     }   
  }

// the loop function runs over and over again forever
void loop() 
  {
  // список состояний светодиодов 1-горит, 0- потушен
  // [green1,yellow1,red1,green2,yellow2,red2]
  // 1 - зеленый, 2 - красный
  int leds1[]={HIGH,LOW,LOW,LOW,LOW, HIGH};
  trafficlight(leds1);
  delay(TIME_GREEN);  
  blinkyellow=true;
  // 1 - желтый с зеленым, 2- желтый c красным
  for(int i=0;i<(TIME_YELLOW/TIME_BLINK);i++)
    {
     int leds2[]={HIGH,(int)blinkyellow,LOW,LOW,(int)blinkyellow,HIGH};
     trafficlight(leds2);
     delay(TIME_BLINK);
     blinkyellow=!blinkyellow;
    }
  // 1 - красный, 2 - зеленый
  int leds3[]={LOW,LOW,HIGH,HIGH,LOW,LOW};
  trafficlight(leds3);
  delay(TIME_GREEN);  
  blinkyellow=true;
  // 1- желтый c красным,  2 - желтый с зеленым
  //for(int i=0;i<(TIME_YELLOW/TIME_BLINK);i++)
  for(int i=0;i<TIME_YELLOW;i=i+TIME_BLINK)
    {
     int leds4[]={LOW,(int)blinkyellow,HIGH,HIGH,(int)blinkyellow,LOW};
     trafficlight(leds4);
     delay(TIME_BLINK);
     blinkyellow=!blinkyellow;
    }
  }
 
 // функция зажигания светодиодов светофора
 void trafficlight(int statled[5])
   {
   for(int i=0;i<6;i++)
     {
     digitalWrite(pinleds[i],statled[i]);   
     } 
   }
