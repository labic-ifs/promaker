//====Pinos digitais para acionamento do motor de passo=====
const byte STEPPER_PIN [2][4] =
{ {10, 11, 12, 13},
  { 6,  7,  8,  9}
};
//==========Configuracao de acionamento Full Setp===========
const bool STEP1 [4][4] =
{ {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};
//======================Comunicacao=========================
//Variavel utilizada para recebimento de dados entre os modulos Bluetooth
int state1;
//Variavel destinada para controlar o sentido de rotacao
bool sentido = true;
// Diametro da roda em mm
const int DIAMETRO1 = 50.0; 
//Numero de passos para da uma volta completa
const int PASSOS_VOLTA = 2048.0;
//=========================Inicio===========================
void setup()
{
  //Comunicacao serial para troca de informacoes entre os modulos Bluetooth
  Serial.begin(38400);
  //Configura os pinos digitais do arduino como saidas
  for (int j = 0; j <= 2; j++) {
    for (int l = 0; l <= 3; l++) {
      pinMode(STEPPER_PIN [j][l], OUTPUT);
    }
  }
}
//=======================Para sempre========================
void loop()
{
  //Leitura de dados
  if (Serial.available() > 0)
  {
    state1 = Serial.read();//Retorno de dados
    if (state1 == '1') {
      andar (100, 1);//Mover para frente
    }
    if (state1 == '2') {
      girar (0);//Mover sentido Anti-Horario
    }
    if (state1 == '3') {
      girar (1);//Mover sentido Horario
    }
  } else {
    parar ();
  }
}
//================Sentido de movimentacao===================
void andar (unsigned int distancia1, bool sentido) {
  //Calculo para determinar a precisao do movimento 
  unsigned long num_passos1 = (unsigned long)distancia1 * PASSOS_VOLTA / (3.141592 * DIAMETRO1);
  for (unsigned int i = 0; i < num_passos1; i++) {
    oneStep1 (0, sentido);
    oneStep1 (1, !sentido);
  }
}
void girar (bool sentido) {
  //Numero de passos necessario para o robor girar 90 graus
  const int num_passos2 = 684;
  for (unsigned int i = 0; i < num_passos2; i++) {
    oneStep1 (0, !sentido);
    oneStep1 (1, !sentido);
  }
}
//=======Funcao para acionamento das bobinas ==============
void oneStep1 (bool motor, bool sentido) {
  static int step_number[] = {0, 0};
  for (byte i = 0; i < 4; i++) {
    digitalWrite(STEPPER_PIN[motor][i], STEP1[step_number[motor]][i]);
  }
  step_number[motor] += 2 * sentido - 1;
  if (step_number[motor] > 3) {
    step_number[motor] = 0;
  }
  if (step_number[motor] < 0) {
    step_number[motor] = 3;
  }
  delayMicroseconds(1000);
}
//==========Funcao para desenergizar bobinas ==============
void parar () {
  for ( int E = 0; E <= 1; E++) {
    for (int e = 0; e <= 3; e++) {
      digitalWrite(STEPPER_PIN[E][e], LOW);
    }
  }
}
