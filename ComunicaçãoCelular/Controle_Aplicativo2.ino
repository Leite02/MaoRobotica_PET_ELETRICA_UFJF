//Bibliotecas e segmentações do código
#include <ESP32Servo.h>
#include "BluetoothSerial.h"
#include "Bluetooth.h"
#include "Controle.h"

//Variável de controle dos componentes
char sinal; 

void setup() 
{
  //Monitor Serial e SerialBT
  Serial.begin(9600);
  Serial.println ("Pronto");
  SerialBT.begin(device_name); //Nome do dispositivo Bluetooth

  //Conexão dos ServoMotores
  servo_POL.attach(servoPOL_pin);
  servo_IND.attach(servoIND_pin);
  servo_MED.attach(servoMED_pin);
  servo_ANE.attach(servoANE_pin);
  servo_MIN.attach(servoMIN_pin);

  //Definir posição inicial nos motores
  pos_inicial ();
}

void loop() 
{
  //Leitura da informação enviada por Bluetooth
  sinal = SerialBT.read();
  Serial.print("Sinal recebido: ");
  Serial.println(sinal);

  //Chamada da função de controle
  controle (sinal);

  delay (1000);
}
