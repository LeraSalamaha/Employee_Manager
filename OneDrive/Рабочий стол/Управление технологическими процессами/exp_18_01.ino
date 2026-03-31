// Лаборатория электроники и программирования
// Эксперимент 18
// До-ре-ми-фа-соль-ля-си. Воспроизводим звуки на Arduino 
//

// длительность воспроизведения ноты
unsigned long duration;
// max и min значение длительности
#define MAX_DURATION 3000
#define MIN_DURATION 300
// пин подключения динамика
const int pinSpeaker=4;
// массив частот для нот первой октавы
// {до, ре, ми, фа, соль, ля, си} 
int octave1[]={261,293,329,349,392,440,494}; 
// пин подключения потенциометра
const int pinPot=A0;


void setup() {
   // сконфигурировать контакт как выход
   pinMode(pinSpeaker,OUTPUT);
}
void loop() {
   // последовательное воспроизведение звуков
   for(int i=0;i<7;i++) {
      // вычисляем скорость воспроизведения
      // (длительность ноты)
      int val=analogRead(pinPot);
      duration=map(val,0,1023,MIN_DURATION,MAX_DURATION);
      // воспроизведение ноты
      tone(pinSpeaker,octave1[i],duration);
      delay(duration);
      delay(duration/2);
   }
   // пауза перед следующим воспроизведением звукоряда
   delay(duration*5);
} 

