// O código abaixo é executado no arduino Ide, no qual o cabo usb deve ser conectado na porta referente
// ao código do python, para poder enviar as informações via monnitor serial.

// FOI FEITA ALTERAÇÕES PARA ESP32


#include <ESP32Servo.h>

#define numOfValRec 5
#define digitsPerValRec 1

Servo servoThumb;    //criação de classes
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValRec];        //criação de parametros
int stringLenght = numOfValRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

void setup() {       //identificação de portas para servos
  Serial.begin(9600);    
  servoThumb.attach(7);
  servoIndex.attach(9);
  servoMiddle.attach(11);
  servoRing.attach(8);
  servoPinky.attach(10);
}
  
void receivedData(){
    while(Serial.available()){       //recebe parametros do código da camera e configura numa string do tipo $00000
      char c = Serial.read();
      if (c=='$'){
        counterStart = true;
       
      }
      if( counterStart){
        if(counter<stringLenght){
          receivedString = String(receivedString+c);
          counter++;
        }
        if(counter >= stringLenght){
          for(int i=0;i < numOfValRec;i++){
            int num = (i*digitsPerValRec)+1;
             valsRec[i]=receivedString.substring(num,num+digitsPerValRec).toInt();
          }
          receivedString = "";
          counter=0;
          counterStart=false;
         }
      }
    }
}

void loop() {     // recebe a string e avalia se dedo aberto ou fechado e envia para servo
  receivedData();
  if(valsRec[0]== 1){servoThumb.write(90);}else{servoThumb.write(0);}   // 180° maximo de rotação 
  if(valsRec[1]== 1){servoIndex.write(90);}else{servoIndex.write(0);}   // alterar qnd tiver parametros da estrutura
  if(valsRec[2]== 1){servoMiddle.write(90);}else{servoMiddle.write(0);}
  if(valsRec[3]== 1){servoRing.write(90);}else{servoRing.write(0);}
  if(valsRec[4]== 1){servoPinky.write(90);}else{servoPinky.write(0);}

}
