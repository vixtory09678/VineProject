#include "VineCollection.h"

void VineCollection::setupPinBegin(){
	_buttonPin = D2; //you can change pin this hear
	pinMode(_buttonPin,INPUT);
}

void VineCollection::setupSystem(WiFiClient client){
  	this->tcp = TCPProtocol();
  	this->mqtt = MQTTProtocol();
    tcp.begin(client);
    mqtt.begin(client);

  	time_button = 0; //init time current of button
	timeout_tcp = 0; //init time current of tcp timeout

  	//check wifi connect on start
  	ssid = EEPROMControl::getInstance()->read(SSID);
  	password = EEPROMControl::getInstance()->read(PASSWORD);
  	if(ssid.length() >0){
  		if(wifi.connect((char*)ssid.c_str(),(char*)password.c_str())){
  			mode = WORKING;
  		}
  	}else{
  		mode = NORMAL;
  	}
	mqtt.setOnDataReceive(
	  [this](JsonObject& json){
		  this->onMqttDataReceive(json);
	  });

	tcp.setOnDataReceive(
	  [this](JsonObject& json){
		  this->onTcpDataReceive(json);
	  });
}

void VineCollection::changeModeService(){
	if(digitalRead(_buttonPin) == LOW){ //check button (pullup)
		if(millis()-time_button > TIMEOUT){
			mode = CONFIG_WITH_WIFI;
			wifi.setModeWiFiShare();

			//-- start server --
			if(tcp.status() == LISTEN)
				tcp.close();

			tcp.beginServer();
			if(tcp.status() == LISTEN){
				//do something
				#ifdef DEBUG
					DEBUG_PRINTLN(F("Server started."));
				#endif
			}
		}
	}else{
		time_button = millis();
	}
}

//tcp callback
void VineCollection::onTcpDataReceive(JsonObject& json){


	// change mode
	tcp.close();
	wifi.setModeWiFiClient();

	String ssidRaw = json["ssid"];
	String passwordRaw = json["password"];
	
	ssid = ssidRaw;
	password = passwordRaw;

	if(wifi.connect((char*)ssid.c_str(),(char*)password.c_str()) == WL_CONNECTED){
		EEPROMControl::getInstance()->save(SSID,(char*)ssid.c_str(),ssid.length());
		EEPROMControl::getInstance()->save(PASSWORD,(char*)password.c_str(),password.length());
		mode = WORKING;
	}else{
		#ifdef DEBUG
			DEBUG_PRINTLN(F("connection faile\n"));
		#endif
	}
}

//mqtt callback
void VineCollection::onMqttDataReceive(JsonObject& json){

}
