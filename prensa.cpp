#ifdef ARDUINO_ARCH_SAM
/*
 * teste.cpp
 *
 *  Created on: 06/08/2014
 *      Author: usuario
 */




/*
Mecanismo de monitoramento DA PRENSA HIDRAULICA


sensores (D2 a D5)s�o ligados em PULL UP detectam a presen�a de GND -
   se ouver contato com o GND o pino vai a zero volts caso contrario o pino vai a 5 volts

Funcionamneto dos Leds  (D9 a D11)

Led verde acesso indica que a alavanca do pist�o pode ser movida para cima ou para baixo

toda a vez que o sensor de caixa fechada for acionado com o o sensor do pist�o acionado
    ascende led verde e os 3 leds vermelhos
    piscam "para cima" indicando o movimento da alavanca do pist�o

toda a vez que o sensor de caixa fechada tiver acionado DEPOIS do stop acionado
    ascende led verde e os 3 leds vermelhos
    piscam "para baixo" indicando o movimento da alavanca do pist�o

toda a vez que a porta aberta e fechada NAO for detectada
    toca sinal sonoro e led verde apaga e leds vermelhos piscam indicando que o o pist�o NAO PODERA ser movido

*/

#include <Arduino.h>

int APAGA = 0;
int ACENDE = 1;
int PISCA = 2;
int SOBE = 3;
int DESCE = 4;



//Estados
int CaixaAberta_PistaoAbaixado = 0;
int CaixaAberta_PistaoLevantado = 1;
int CaixaFechada_PistaoAbaixado = 2;
int CaixaFechada_PistaoLevantado = 3;
int Erro = 4;

//sensores
int sensorCxAberta = 8;   // sensor da maquina com a caixa aberta
int sensorStopPistao =  9; // sensor da caixa com pistao totalmente abaixado
int sensorCxFechada = 10;  // sensor da maquina com a caixa fechada
int sensorStop = 11;   // sensor da maquina com o stop acionado / caixa totalmente levantada


int leds[3] = {3,4,5}; // Led de sinaliza��o da Caixa fechada
int ledVerde = 2;

 // vari�vel para ler o estado do interruptor

void setup() {
    int i;
  // led
  for (i = 0; i<3;i++){
        pinMode(leds[i], OUTPUT);  // declara-se o LED como sa�da
  }
  pinMode(ledVerde, OUTPUT);
  pinMode(6, OUTPUT);
  // sensores
  for (i = sensorCxAberta; i<sensorStop+1;i++){
       pinMode(i, INPUT);    // declara-se o interruptor como entrada
  }

}


int defineEstado(){
  if (digitalRead(sensorCxAberta) == LOW){
    if(digitalRead(sensorStopPistao) == LOW)
        return(CaixaAberta_PistaoAbaixado);
    else if(digitalRead(sensorStop) == LOW)
          return(CaixaAberta_PistaoLevantado);
  }

  if (digitalRead(sensorCxFechada) == LOW){
    if(digitalRead(sensorStopPistao) == LOW)
    	return(CaixaFechada_PistaoAbaixado);
    else if(digitalRead(sensorStop)== LOW)
        return(CaixaFechada_PistaoLevantado);
  }
  return(Erro);
}

void acendeLed(int opcao ){
  int i;
  switch (opcao){
    case 0: //APAGA
        for (i = 0; i<3;i++){
             digitalWrite(leds[i], LOW);
             // declara-se o LED como sa�da
        }
        break;
    case 1: //ACENDE:
        for (i = 0; i<3;i++){
             digitalWrite(leds[i], HIGH);
             // declara-se o LED como sa�da
        }
        break;

    case 2: //PISCA:
        for (i=1;i<4;i++){
            acendeLed(ACENDE);
            digitalWrite(6,HIGH);
            delay(250);
            acendeLed(APAGA);
            digitalWrite(6,LOW);
            delay(250);
        }
        break;

    case 3: //SOBE:
        acendeLed(APAGA);
        for (i = 2; i>-1;i--){
             digitalWrite(leds[i], HIGH);
             delay(250);
        }
        //delay(250);
        acendeLed(APAGA);
        break;

    case 4 : //DESCE:
        acendeLed(APAGA);
        for (i = 0; i<4;i++){
             digitalWrite(leds[i], HIGH);
             delay(250);
        }
        //delay(250);
        acendeLed(APAGA);
        break;
  }

}

void loop(){
  switch (defineEstado()) {
    case 0: //CaixaAberta_PistaoAbaixado: // = 0
        digitalWrite(ledVerde, HIGH);
        acendeLed(SOBE);

        break;
    case 1: //CaixaAberta_PistaoLevantado: // = 1
        digitalWrite(ledVerde, HIGH);
        acendeLed(DESCE);

        break;
    case 2: //CaixaFechada_PistaoAbaixado: // = 2
        digitalWrite(ledVerde, HIGH);
        acendeLed(SOBE);

        break;
    case 3: //CaixaFechada_PistaoLevantado: // = 3
     	//acendeLed(ACENDE);
    	digitalWrite(ledVerde, HIGH);
   	digitalWrite(6,HIGH);
        acendeLed(DESCE);

        break;
    case 4: //Erro: // = 4
        digitalWrite(ledVerde, LOW);
        acendeLed(PISCA);
        break;
  }
}
#endif /* ARDUINO_ARCH_SAM */
