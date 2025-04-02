//É necessário definir quais movimentos serão realizados e programa-los nos [Case '':]

//Defines
#define POL 1000 // Atraso na movimentação do polegar (Recurso contra falhas)
#define res 2000 // Atraso no início do movimento solicitado (Recurso contra falhas)
#define servoPOL_pin 13 // Dedo Polegar
#define servoIND_pin 12 // Dedo Indicador
#define servoMED_pin 14 // Dedo Médio
#define servoANE_pin 27 // Dedo Anelar
#define servoMIN_pin 26 // Dodo Mínimo

//Declaração de funções
void pos_inicial ();
void pos_fechada ();

//Classes e Objetos
Servo servo_POL;
Servo servo_IND;
Servo servo_MED;
Servo servo_ANE;
Servo servo_MIN;

void controle (char sinal) //Controle dos dedos com base na variável char sinal
{
  switch (sinal)
  {
    case 'B':
      //Movimento: Beleza (Seleção dedo Polegar)
      pos_inicial ();
      servo_IND.write(90);
      servo_MED.write(90);
      servo_ANE.write(90);
      servo_MIN.write(90);
    break;
    case 'H':
      //Movimento: Hang-loose
      pos_inicial ();
      servo_IND.write(90);
      servo_MED.write(90);
      servo_ANE.write(90);
    break;
    case 'R':
      //Movimento: Rock&Roll
      pos_inicial ();
      servo_MED.write(90);
      servo_ANE.write(90);
    break;
//============================================================================================================
    case '0':
      //Movimento: Número 0 (Mão fechada)
      pos_inicial ();
      pos_fechada ();
    break;
    case '1':
      //Movimento: Número 1 (Seleção dedo Indicador)
      pos_inicial ();
      servo_MED.write(90);
      servo_ANE.write(90);
      servo_MIN.write(90);
      delay (POL);
      servo_POL.write(90);
    break;
    case '2':
      //Movimento: Número 2 (V de vitória)
      pos_inicial ();
      servo_ANE.write(90);
      servo_MIN.write(90);
      delay (POL);
      servo_POL.write(90);
    break;
    case '3':
      //Movimento: Número 3
      pos_inicial ();
      servo_MIN.write(90);
      delay (POL);
      servo_POL.write(90);
    break;
    case '4':
      //Movimento: Número 4
      pos_inicial ();
      delay (POL);
      servo_POL.write(90);
    break;
    case '5':
      //Movimento: Número 5 (Reset de posição (Mão aberta))
      pos_inicial ();
    break;
//============================================================================================================
    case 'M':
      //Movimento: Seleção dedo Médio
      pos_inicial ();
      servo_ANE.write(90);
      servo_MIN.write(90);
      servo_IND.write(90);
      delay (POL);
      servo_POL.write(90);
    break;
    case 'A':
      //Movimento: Seleção dedo Anelar
      pos_inicial ();
      servo_MED.write(90);
      servo_MIN.write(90);
      servo_IND.write(90);
      delay (POL);
      servo_POL.write(90);
    break;
    case 'm':
      //Movimento: Seleção dedo mínimo
      pos_inicial ();
      servo_IND.write(90);
      servo_MED.write(90);
      servo_ANE.write(90);
      delay (POL);
      servo_POL.write(90);
    break;
  }
}

/*============================================================================================================
Funções de controle úteis */

void pos_inicial () //Reinicia para a posição inicial de movimentação (Mão aberta)
{
  servo_POL.write(0);
  delay (POL);
  servo_IND.write(0);
  servo_MED.write(0);
  servo_ANE.write(0);
  servo_MIN.write(0);
}

void pos_fechada () //Contração de todos os dedos (Mão fechada, número 0)
{
  servo_IND.write(90);
  servo_MED.write(90);
  servo_ANE.write(90);
  servo_MIN.write(90);
  delay (POL);
  servo_POL.write(90);
}