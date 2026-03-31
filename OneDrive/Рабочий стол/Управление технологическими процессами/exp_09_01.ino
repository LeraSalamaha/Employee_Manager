  // Лаборатория электроники и программирования
  // Эксперимент 9
  // управляем скоростью и направлением "бегущего огня" 
  // с помощью кнопок.
  //

  // пины для подключения кнопок
  int pinButtons[]={2,3,4,5};
  // для сохранения предыдущих состояний кнопок
  int lastButtons[]={0,0,0,0};
  // для сохранения текущих состояний кнопок
  int currentButtons[]={0,0,0,0};
  // пины подключения светодиодов red,yellow,green
  int pinLeds[]={6,7,8,9,10,11,12,13};
  // скорость бегущего огня
  unsigned long interval=100;
  unsigned long t=0;
  // текущий горящий светодиод
  int tekled=0;
  // направлени бегущего огня
  int dir=1;

  void setup() {
    // Сконфигурировать пины подключения кнопок как вход
    for(int i=0;i<4;i++) {
      pinMode (pinButtons[i], INPUT);
    }    
    // Сконфигурировать пины подключения светодиодов
    // как выход 
    for(int i=0;i<8;i++) {
      pinMode (pinLeds[i], OUTPUT);
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
      // функция перехода при нажатии кнопки
      doButtons(i);
      }
    lastButtons[i] = currentButtons[i]; 
    }
    
    // переключения светодиодов
    if(millis()-t>=interval) {
      for (int i=0;i<8; i=i+1) {
        if(i==tekled)
          {digitalWrite(pinLeds[i],HIGH);}
        else
          {digitalWrite(pinLeds[i],LOW);}
      }
      tekled=(tekled+dir)%8;
      if(tekled<0) {

          tekled = 8;
      }
      t=millis();
    }
    
  }
  // обработка клавиш выбора программ
  void doButtons(int but)
    {
    switch(but)
        {
        case 0:
              Serial.println("case for button 1");  
              dir=1;
              break;
        case 1:  
              Serial.println("case for button 2");
              dir=-1;
              break;
        case 2:  
              Serial.println("case for button 3");
              interval -= 200;
              break;
        case 3:  
              Serial.println("case for button 4");
              interval += 200;   
              break;
        default:  
              break;
      }
    }

  // Функция сглаживания дребезга
  int debounce(int last,int pin1) {
    int current = digitalRead(pin1);   
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

