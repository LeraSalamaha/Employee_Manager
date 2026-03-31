// Лаборатория электроники и программирования
// Эксперимент 14
// Регулятор показаний светодиодной шкалы 
//

// Аналоговый вход A0 для подключения потенциометра 
const int POT=0; 
// переменная для хранения значения потенциометра 
int valpot = 0; 
// список контактов подключения светодиодной шкалы
const int pinsled[10]={4,5,6,7,8,9,10,11,12,13};
// переменная для хранения значения шкалы 
int countleds = 0; 

void setup() {
   // запуск последовательного порта
   Serial.begin(9600);   
   for(int i=0;i<10;i++) {
      // Сконфигурировать контакты подсоединения шкалы как выходы
      pinMode(pinsled[i],OUTPUT);
      digitalWrite(pinsled[i],LOW);
   }
}

void loop() {
   // чтение данных потенциометра 
   valpot = analogRead(POT); 
   // масштабируем значение к интервалу 0-10
   countleds=map(valpot,0,1023,0,10);
   Serial.print("valpot =");
   Serial.println(valpot); 
   Serial.print("countleds =");
   Serial.println(countleds); 
   // зажигаем количество полосок на шкале, равное countled
   for(int i=0;i<10;i++) {
      if(i<countleds) // зажигаем светодиод шкалы
         {digitalWrite(pinsled[i],LOW);}
      else // гасим светодиод шкалы
         {digitalWrite(pinsled[i],HIGH);}
   }
}

