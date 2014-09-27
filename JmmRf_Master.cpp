#ifdef ARDUINO_ARCH_SAM
// Do not remove the include below
#include "JmmRf_Master.h"
#include "MasterNode.h"
#include "JmmRF.h"

MasterNode node("C-00", {}, true); // Id, Comandos e Debug
//JmmRf rf(2,3,0,true);

//The setup function is called once at startup of the sketch
void setup()
{
	node.setup();
}

// The loop function is called in an endless loop
void loop()
{
	node.loop();
	delay(10000);
}
#endif /* ARDUINO_ARCH_SAM */
