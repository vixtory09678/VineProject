#include "TCPProtocol.h"

WiFiServer server(2000);

void TCPProtocol::begin(WiFiClient client){
  _client = client;
}

void TCPProtocol::beginServer(){
	server.begin();
}

uint8_t TCPProtocol::status(){
	return server.status();
}

void TCPProtocol::close(){
	server.close();
}

void TCPProtocol::setOnDataReceive(CALLBACK_ON_DATA_RECEIVE){
	this->_callback = _callback;
}

void TCPProtocol::handle(){
	if(_client.connected())
		_client.stop();

	_client = server.available();

	if(_client.available()){
		StaticJsonBuffer<200> jsonBuffer;
    String msg = "";
		while(_client.available()){
			 msg += (char)_client.read();	
		}
   
    if(msg.indexOf("{") >= 0 &&msg.indexOf("}") >= 0){ // parse msg String to jsonObject

       	#ifdef DEBUG
          Serial.println(F("Json read complete"));
       	#endif

        JsonObject& root = jsonBuffer.parseObject(msg);
        _callback(root);
     }
	}
}
