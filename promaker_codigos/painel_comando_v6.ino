#include <SoftwareSerial.h>
int state1 = 20;
SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {

  Serial.begin(38400);//Comunicação serial
  analogReference(DEFAULT);
  pinMode(12, INPUT_PULLUP);

}

void loop() {

  //Avalia o estado do botao
  if (Serial.available() > 0)
  {
    state1 = Serial.read();
  }
  play();
  delay(100);
}

void play ()
{
  static byte estado = 0;
  bool BT = digitalRead(12);
  switch (estado) {

    case 0://Estado atual
      if (BT  == 1) {//Condição
        estado = 1;//Estado Futuro
      }
      break;

    case 1://Estado atual
      if (BT == 0) {//Condição
        leitura ();
        estado = 0;//Estado Futuro
      }
      break;
  }
}

void leitura () {

  char valor;
  for (int porta = 0; porta <= 5; porta++) {
    valor = ler_comando(porta);
    Serial.write(valor);
  }
}

char ler_comando (byte num_porta) {

  char c = '0';

  int leitura = analogRead(num_porta);

  if (leitura >= 170 && leitura <= 190) {
    c = '1';
  }

  if (leitura >= 320 && leitura <= 340) {
    c = '2';
  }

  if (leitura >= 500 && leitura <= 520) {
    c = '3';
  }

  if (leitura >= 700 && leitura <= 720) {
    c = '4';
  }
  return c;
}
