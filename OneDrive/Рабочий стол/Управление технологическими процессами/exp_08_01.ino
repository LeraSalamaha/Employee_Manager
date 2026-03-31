// пины для подключения кнопок
int pinButtons[]={2,3,4,5};
// для сохранения предыдущих состояний кнопок
int lastButtons[]={0,0,0,0};
// для сохранения текущих состояний кнопок
int currentButtons[]={0,0,0,0};
// пины подключения светодиодов red,yellow,green
int pinLeds[]={8,9,10};
void setup() {
// запуск последовательного порта
 Serial.begin(9600);
// Сконфигурировать пины подключения кнопок как вход
 for(int i=0;i<4;i++) {
  pinMode (pinButtons[i], INPUT);
 }  
// Сконфигурировать пины подключения светодиодов
// как выход и выключить
 for(int i=0;i<3;i++) {
  pinMode (pinLeds[i], OUTPUT);
  digitalWrite (pinLeds[i], LOW);
 }  
}
void loop() {
// проверка нажатия кнопок выбора программ
 for(int i=0;i<4;i++)
 {
// борьба с дребезгом
 currentButtons [i] = debounce(lastButtons [i],pinButtons [i]);
// если нажатие...
 if (lastButtons [i] == 0 && currentButtons [i] == 1)
  {
// для отладки
  Serial.println("click!");
// функция перехода при нажатии кнопки
  doButtons(i);
  }
 lastButtons[i] = currentButtons[i];
 }
}
// обработка клавиш выбора программ
void doButtons(int but)
 {
 switch(but)
   {
   case 0: Serial.println("case for button 0");
       digitalWrite(pinLeds[0],HIGH);
      break;
   case 1: Serial.println("case for button 1");
       digitalWrite(pinLeds[1],HIGH);
      break;
   case 2: Serial.println("case for button 2");
       digitalWrite(pinLeds[2],HIGH);
     break;
   case 3: Serial.println("case for button 3");
       for(int i=0;i<3;i++) {
         digitalWrite (pinLeds[i], LOW);
       }  
      break;
   default: 
      break;
  }
 }
// Функция сглаживания дребезга
int debounce(int last,int pin1) {
 int current = digitalRead(pin1);
//return current;   
 if (last != current) 
  {
  delay(5);
  current = digitalRead(pin1);
  return current;
  }
  else
  {
   return last;
  }
}