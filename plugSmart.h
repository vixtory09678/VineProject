#ifndef PLUG_SMART_H
#define PLUG_SMART_H

#include "ESP8266WiFi.h"
#include "VineCollection.h"

#define VERSION "0.0.1"
#define TYPE "SWITCH_WIFI"

class PlugSmart : public VineCollection
{
public:
	//overide
	PlugSmart(){}
	void handle();
	void setupPinBegin();
	void setupSystem(WiFiClient);

	String getID();
	String getVersion();
	String getType();
};

#endif
