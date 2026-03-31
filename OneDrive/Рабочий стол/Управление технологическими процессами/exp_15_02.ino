// Лаборатория электроники и программирования
// Эксперимент 15
// Клавиатура по однопроводной аналоговой линии 
//


// переменная для хранения значения A0 
int valA0 = 0; 
// контактов подключения светодиодов
// RIGHT,UP,DOWN,LEFT,SELECT
const int pinsled[]={8,9,10,11,12};
 

void setup() {
   // запуск последовательного порта
   Serial.begin(9600);   
   for(int i=0;i<10;i++) {
      // Сконфигурировать контакты светодиодов как выходы
      // и выключить
      pinMode(pinsled[i],OUTPUT);
      digitalWrite(pinsled[i],LOW);
   }
}

void loop() {
   // чтение данных A0 
   valA0 = analogRead(A0); 
   // определение нажатия кнопки
   if(valA0<100) { // RIGHT
      setLed(0);
   }
   else if(valA0<200) { // UP
      setLed(1);
   }
   else if(valA0<400) { // DOWN
      setLed(2);
   }
   else if(valA0<600) { // LEFT
      setLed(3);
   }
   else if(valA0<800) { // SELECT
      setLed(4);
   }  
}

// установка горящего светодиода
void setLed(int n) {
   for(int i=0;i<5;i++) {
     if(i==n)
        {digitalWrite(pinsled[i],HIGH);}
     else
        {digitalWrite(pinsled[i],LOW);}
   }
} 

