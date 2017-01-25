#ifndef TCP_PROTOCOL_H
#define TCP_PROTOCOL_H

#include "ESP8266WiFi.h"
#include <ArduinoJson.h>

#define CALLBACK_ON_DATA_RECEIVE std::function<void(JsonObject&)> _callback

class TCPProtocol
{
	public:
		void setOnDataReceive(CALLBACK_ON_DATA_RECEIVE);
		void handle();
    void begin(WiFiClient);

		uint8_t status();
		void close();
		void beginServer();
	private:
		WiFiClient _client;
		CALLBACK_ON_DATA_RECEIVE;
};

#endif
