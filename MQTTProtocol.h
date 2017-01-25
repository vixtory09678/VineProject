#ifndef MQTT_PROTOCOL_H
#define MQTT_PROTOCOL_H

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
  
#define CALLBACK_MQTT std::function<void(JsonObject&)> _callback

class MQTTProtocol
{
	public:
    void begin(WiFiClient client);
		void publish(const char*,String);
		void subscribe(const char* topic);

		void setOnDataReceive(CALLBACK_MQTT);
		void setServer(const char* host,int port);
    bool connectServer(const char* user, const char* password);

    void handle();
	private:
		PubSubClient *_client;
		CALLBACK_MQTT;

		void dataReceiveFromMqtt(char* topic , byte *payload , unsigned int length);
};

#endif
