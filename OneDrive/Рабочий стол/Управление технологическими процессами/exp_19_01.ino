// Лаборатория электроники и программирования
// Эксперимент 19
// Воспроизводим звуки разных октав. 
//

// длительность воспроизведения ноты
unsigned long duration;
// номер воспроизводимой октавы
int octave;
// номер динамика
int speaker;
// max и min значение длительности
#define MAX_DURATION 3000
#define MIN_DURATION 300
// пины подключения динамиков
const int pinSpeakers[]={4,5};
// массив частот для нот 
// {до, ре, ми, фа, соль, ля, си} 
int octaves [4][7]={
   {130,146,165,175,196,220,247}, // малая октава
   {261,293,329,349,392,440,494}, // первая октава
   {523,587,659,698,784,880,988}, // вторая октава
   {1047,1175,1319,1397,1568,1760,1975} // третья октава
};
 
// пин подключения потенциометра длительности
const int pinPot=A0;
// пин подключения потенциометра выбора октав
const int pinChoiceOctaves=A1;


void setup() {
   // сконфигурировать контакты динамиков как выход
   pinMode(pinSpeakers[0],OUTPUT);
   pinMode(pinSpeakers[1],OUTPUT);
}
void loop() {
   // последовательное воспроизведение звуков
   for(int i=0;i<7;i++) {
      // вычисляем скорость воспроизведения
      int val=analogRead(pinPot);
      duration=map(val,0,1023,MIN_DURATION,MAX_DURATION);
      // вычисляем номер октавы
      val=analogRead(pinChoiceOctaves);
      octave=map(val,0,1023,0,3); 
      // номер динамика
      speaker=pinSpeakers[octave%2];
      // воспроизведение ноты
      tone(speaker,octaves[octave][i],duration);
      delay(duration);
      delay(duration/2);
   }
   // пауза перед следующим воспроизведением звукоряда
   delay(duration*2);
} 

