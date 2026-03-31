// Лаборатория электроники и программирования
// Эксперимент 12
// Матрица 4-разрядная из 7-сегментных индикаторов 
// Секундомер с точностью 0.1 сек
//

// список выводов Arduino для подключения к разрядам a-g
// семисегментного индикатора
int pins[8]={9,13,4,6,7,10,3,5};
// значения для вывода цифр 0-9
byte numbers[10] = { B11111100, B01100000, B11011010,
B11110010, B01100110, B10110110,
B10111110, B11100000, B11111110,
B11110110};
// переменная для хранения и обработки текущего значения  
// семисегментного индикатора
int number=0;
int number1=0;
int number2=0;
// список выводов Arduino для выбора матрицы 0-3 
int pindigits[4]={2,12,11,8};
// переменная для хранения текущего разряда
int digit=0;
// для отмеривания 100 мс
unsigned long millis1=0;
// режим 1 - секундомер работает
int mode=0;
// Контакт 14(A0) для подключения кнопки
const int BUTTON=14; 
// Переменная для сохранения текущего состояния кнопки
int tekButton = LOW; 
// Переменная для сохранения предыдущего состояния кнопки
int prevButton = LOW; 

void setup() {
   // Сконфигурировать контакт кнопки как вход
   pinMode (BUTTON, INPUT);
   // Сконфигурировать контакты как выходы
   for(int i=0;i<8;i++)
      pinMode(pins[i],OUTPUT);
   // выключить все контакты выбора матриц
   for(int i=0;i<4;i++) {
      pinMode(pindigits[i],OUTPUT);
      digitalWrite(pindigits[i],HIGH);
   }
}
int current = 0;
void loop() {
   tekButton = debounce(prevButton);
   // если нажатие...
   if (tekButton == HIGH) {
      // изменение режима
  
         
     current = millis();
     if(current-millis1>=100) {
        millis1=millis1+current;
        number=number+1;
        if(number==10000)
           number=0;
     }
     number1=number;
     
     for(int i=0;i<4;i++) {
       for(int j=0;j<4;j++)
         digitalWrite(pindigits[j],LOW);
  
        number2=number1%10;
        number1=number1/10;
        setNumber(number2,i);
  
        digitalWrite(pindigits[i],HIGH);
        delay(1);
        
     }
  } else {
     number1=number;
     for(int i=0;i<4;i++) {
       for(int j=0;j<4;j++)
         digitalWrite(pindigits[j],LOW);
  
        number2=number1%10;
        number1=number1/10;
        setNumber(number2,i);
  
        digitalWrite(pindigits[i],HIGH);
        delay(1);
        
     }
  }
}
// функция вывода цифры на семисегментный индикатор
void setNumber(int num,int dig) {
   for(int i=0;i<8;i++) {
      if(bitRead(numbers[num],7-i)==HIGH) // зажечь сегмент
         digitalWrite(pins[i],LOW);
      else // потушить сегмент
         digitalWrite(pins[i],HIGH);
   }
   if(dig==1) // десятичная точка для второго разряда
      digitalWrite(pins[7],HIGH);
}
// Функция сглаживания дребезга. Принимает в качестве
// аргумента предыдущее состояние кнопки и выдает фактическое.
boolean debounce(boolean last) {
   // Считать состояние кнопки, если изменилось...
   boolean current = digitalRead(BUTTON); 
   return current;
   if (last != current) {
      delay(5); // ждем 5 мс
      // считываем состояние кнопки
      current = digitalRead(BUTTON); 
      // возвращаем состояние кнопки
      return current; 
   }
}
