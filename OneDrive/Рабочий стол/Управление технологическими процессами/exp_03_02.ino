// Лаборатория электроники и программирования
// Эксперимент 3
// Бегущий огонек на 8 светодиодах
// Введение констант и переменных
//
#define LED1      2
#define LED2      3
#define LED3      4
#define LED4      6
#define LED5      8
#define LED6      7
#define LED7      5
#define LED8      13
// переменная скорости движения бегущего огня
int t=500;

void setup() {
   // настроить выводы Arduino как OUTPUT
   pinMode(LED1,OUTPUT);
   pinMode(LED2,OUTPUT);
   pinMode(LED3,OUTPUT);
   pinMode(LED4,OUTPUT);
   pinMode(LED5,OUTPUT);
   pinMode(LED6,OUTPUT);
   pinMode(LED7,OUTPUT);
   pinMode(LED8,OUTPUT);
}

void loop() {
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 1 светодиод
  digitalWrite(LED1, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 2 светодиод
  digitalWrite(LED2, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 3 светодиод
  digitalWrite(LED3, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 4 светодиод
  digitalWrite(LED4, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 5 светодиод
  digitalWrite(LED5, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 6 светодиод
  digitalWrite(LED6, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 7 светодиод
  digitalWrite(LED7, HIGH);    
  // пауза  
  delay(t);           
  // выключить 8 светодиодов   
  ledsOff();  
  // включить 8 светодиод
  digitalWrite(LED8, HIGH);    
  // пауза 
  delay(t);  
  t=t+100;         
}
// функция выключения 8 светодиодов
void ledsOff() {
     // код функции
  digitalWrite(LED1, LOW);   
  digitalWrite(LED2, LOW);   
  digitalWrite(LED3, LOW);   
  digitalWrite(LED4, LOW);  
  digitalWrite(LED5, LOW);   
  digitalWrite(LED6, LOW);   
  digitalWrite(LED7, LOW);   
  digitalWrite(LED8, LOW);  
}


