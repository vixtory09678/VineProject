#include "plugSmart.h"
#include "VineCollection.h"

PlugSmart plug;
WiFiClient client;
void setup(){
  plug.setupPinBegin();
  plug.setupSystem(client);
}

void loop(){
  plug.handle();
}

