/*
 * JmmRf_NodeSuite.cpp
 *
 *  Created on: 18/08/2014
 *      Author: usuario
 */


// Do not remove the include below
//#include "JmmRf_Master.h"
#include "Node.h"


/*
 * typedef struct
		{
			int id_objeto;
			int acao;
			int pino;
			int seq_ir_code[];
		} Comando;
 *
 */

Node node("C-S0", {{"01",1,3,{}},{"01",0,3,{}},{"02",0,3,{100,200,300,200,100}}}, true);
// Id, Comandos (String id_objeto, int acao, int pino e int seq_ir_code[]) e Debug

void interrupt(){
  detachInterrupt(node.rf.pinInterrupt);
  node.rf._dataIncoming();
  attachInterrupt(node.rf.pinInterrupt,interrupt,RISING);
}
void setup(){
  attachInterrupt(node.rf.pinInterrupt,interrupt,RISING);

  node.setup();
}

void loop(){
	node.loop();
	delay(10000);
}



