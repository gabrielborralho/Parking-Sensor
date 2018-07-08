/** ##############################################################
**
**  Filename  : Parking_Sensor.ino
**  Project   : Parking Sensor
**  Processor : ATMega328/P
**  Version   : 1.0
**  Compiler  : Arduino IDE
**  Date/Time : 01/02/2014
**  Aluno     : Gabriel Borralho
**  Last Mod  : 15/02/2014
**
** ##############################################################*/

#include <Ultrasonic.h>     //Carrega a biblioteca Ultrasonic
#include <LiquidCrystal.h>  //Carrega a biblioteca LCD

//Define o pino do Arduino a ser utilizado com o pino Trigger do sensor
#define PINO_TRIGGER  8 

//Define o pino do Arduino a ser utilizado com o pino Echo do sensor
#define PINO_ECHO     7

//Define o pino do BUZZER
#define BUZZER        10
#define NOTE  1000

//Inicializa o sensor ultrasonico
Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO); 

//Define os pinos que serão ligados ao LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void Led_Pisca(int tempo)
{
  int i;
  if(tempo < 75)
  {
    digitalWrite(13, HIGH);
    tone(BUZZER, NOTE);
    delay(tempo*5);            
    digitalWrite(13, LOW);
    noTone(BUZZER);
    delay(tempo*5);
  }
}

void setup()
{
  Serial.begin(9600); //Inicializa a serial
  lcd.begin(16,2); //Inicializa LCD
  lcd.clear();     //Limpa o LCD
  pinMode(13, OUTPUT); //Pino do Led
  pinMode(BUZZER,OUTPUT); //Pino do buzzer
}

void loop()
{
  float cmMsec, inMsec;

  //Le os dados do sensor, com o tempo de retorno do sinal
  long microsec = ultrasonic.timing();  

  //Calcula a distancia em centimetros
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); 

  //Calcula a distancia em polegadas
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN); 

  //Apresenta os dados, em centimetros, no LCD e na Serial
  lcd.setCursor(0,0);
  lcd.print("Cent.: ");
  lcd.print("        ");
  lcd.setCursor(7,0);
  lcd.print(cmMsec);

  Serial.print("Cent: ");
  Serial.print(cmMsec);

  //Apresenta os dados, em polegadas, no LCD e na Serial  
  lcd.setCursor(0,1);
  lcd.print("Pol. : ");
  lcd.print("        ");
  lcd.setCursor(7,1);
  lcd.print(inMsec);

  Serial.print(", Pol. : ");
  Serial.println(inMsec);
  Led_Pisca((int)cmMsec);

  delay(50);
}
