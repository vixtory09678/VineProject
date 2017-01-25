#include "MQTTProtocol.h"

void MQTTProtocol::begin(WiFiClient client){
  _client = new PubSubClient(client);

  _client->setCallback([this](char* topic,byte *payload , unsigned int length){
    this->dataReceiveFromMqtt(topic,payload,length);
  });
}

void MQTTProtocol::handle(){
  _client->loop();
}

bool MQTTProtocol::connectServer(const char* user, const char* password){
  const char* id = "VINE-ID-001";
  return _client->connect(id,user,password);
}

void MQTTProtocol::setServer(const char* host,int port){
	_client->setServer(host,port);
}

void MQTTProtocol::setOnDataReceive(CALLBACK_MQTT){
	this->_callback = _callback;
}


void MQTTProtocol::subscribe(const char* topic){
	_client->subscribe(topic);
}
void MQTTProtocol::publish(const char* topic,String json){

	char* msg = (char*)json.c_str();

	#ifdef DEBUG
		Serial.println(F("----- data publish ------"));
		Serial.print(F("topic -> "));
		Serial.println(topic);
		Serial.print(F("msg -> "));
		Serial.println(msg);
		Serial.println(F("-------------------------"));
	#endif

	_client->publish(topic,msg);
}



void MQTTProtocol::dataReceiveFromMqtt(char* topic , byte *payload , unsigned int length){
	String msg = "";
	StaticJsonBuffer<200> buff;

	for(int i = 0; i < length ; i++)
		msg.concat((char)payload[i]);

	if(msg.indexOf("{") >= 0 && msg.indexOf("}") >=0){
		JsonObject& root = buff.parseObject(msg);
		_callback(root);
	}
	
}

