// Лаборатория электроники и программирования
// Эксперимент 1
// Светодиодный маячок на 4 светодиодах
//
void setup() {
   // настроить выводы 8, 9, 10, 11 Arduino как OUTPUT
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
}

void loop() {
  // включить светодиоды   
  digitalWrite(8, HIGH);   
  digitalWrite(9, HIGH);   
  digitalWrite(10, HIGH);   
  digitalWrite(11, HIGH);   
  // пауза 1000 мсек (1 сек)
  delay(1000);           
  // выключить светодиоды 
  digitalWrite(8, LOW);    
  digitalWrite(9, LOW);    
  digitalWrite(10, LOW);    
  digitalWrite(11, LOW);    
  // пауза 1000 мсек (1 сек)
  delay(1000);              
}

