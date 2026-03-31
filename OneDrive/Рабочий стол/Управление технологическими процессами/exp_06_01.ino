// Лаборатория электроники и программирования
// Эксперимент 6
// Подключаем к Arduino кнопку.
//

// Контакт 13 для подключения светодиода
int LED=13;         
// Контакт 2 для подключения кнопки
int BUTTON=2;       
// переменная статуса кнопки buttonState
boolean buttonState;      
    
void setup() {
  // определяем вывод LED (светодиод) как выход
  pinMode(LED, OUTPUT);        
  // определяем вывод BUTTON (кнопка) как вход
  pinMode(BUTTON, INPUT);  
}

void loop() {
  // считываем состояние BUTTON входа  и записываем в buttonState
  buttonState = digitalRead(BUTTON);
  // инверсия переменной buttonState
  // для схемы с подтягивающим резистором  
  buttonState = ! buttonState;
  // записываем состояние из buttonState на выход LED (светодиод)     
  digitalWrite(LED, buttonState);  
}

