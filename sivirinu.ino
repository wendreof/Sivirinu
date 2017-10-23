//Programa : Modulo Bluetooth HC-05 - Leds - Rodas


//Armazena o caracter recebido
#include <Servo.h>
#define SERVO 11 // Porta Digital 11 PWM
 
Servo s; // Variável Servo
int pos; // Posição Servo

char buf;
int IN1 = 6;
int IN2 = 5;
int IN3 = 4;
int IN4 = 3;


//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 8
#define pino_echo 10

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);


void setup()
{
   Serial.begin(9600);
   Serial.println("Lendo dados do sensor...");             
   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
   s.attach(SERVO);
   s.write(0); // Inicia motor posição zero
}

void loop()
{
   //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
    if(cmMsec <= 30)
         {
           s.write(150);
           delay(300);
           s.write(50);
           delay(300);
         }
          
    if(cmMsec > 30)
        {
          s.write(0);
          delay(50);
        }
        delay(05);
  while(Serial.available() > 0)
  {
buf = Serial.read();
    
                      //Andar para frente
                      if (buf == 'a')
                      {
                        //liga roda esquerda
                         digitalWrite(IN1, HIGH);
                         digitalWrite(IN2, LOW);
                        //liga roda direita
                        digitalWrite(IN3, HIGH);
                        digitalWrite(IN4, LOW);
                      }
    
    //Andar para tras
    if (buf == 'p')
    {
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

                    //virar para esquerda
                     if (buf == 'e')
                    {
                     
                      digitalWrite(IN3, HIGH);
                      digitalWrite(IN4, HIGH);
                      delay (100);
                      digitalWrite(IN1, HIGH);
                      digitalWrite(IN2, LOW);
                      digitalWrite(IN3, HIGH);
                      digitalWrite(IN4, LOW);
                    }
                    
    //Virar para direita
    if (buf == 'd')
    {
      
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, HIGH);
       delay(100);
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
    }
    
                                 //DESLIGAR
                                if (buf == 'x')
                                {
                                   digitalWrite(IN1, LOW);
                                   digitalWrite(IN2, LOW);
                                   digitalWrite(IN3, LOW);
                                   digitalWrite(IN4, LOW);
                                }
      
  }
}