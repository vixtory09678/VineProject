#ifndef VINE_COLLECTION_H
#define VINE_COLLECTION_H

#include "ESP8266WiFi.h"
#include "Arduino.h"

#include "WIFI_Manage.h"
#include "TCPProtocol.h"
#include "MQTTProtocol.h"

#include "EEPROMControl.h"

#define TIMEOUT 3000
#define TIMEOUT_TCP 20000

#define DEBUG_PRINT(str) Serial.print(str)
#define DEBUG_PRINTLN(str) Serial.println(str)


typedef enum {
	NORMAL,
	CONFIG_WITH_WIFI,
	WORKING
}SystemMode;

class VineCollection
{
public:
	VineCollection(){}
	uint8_t _buttonPin;
	unsigned long time_button;
	unsigned long timeout_tcp;
	SystemMode mode;

	void setupSystem(WiFiClient);
	virtual void handle() = 0;
	void setupPinBegin();

	WIFI_Manage wifi;
	TCPProtocol tcp;
	MQTTProtocol mqtt;
private:
	

	//tcp call back
	void onTcpDataReceive(JsonObject& json);

	//mqtt call back
	void onMqttDataReceive(JsonObject& json);

protected:
	

	void changeModeService();
  	

	String ssid;
	String password;
};

#endif
