#include "plugSmart.h"

void PlugSmart::handle(){
	switch(mode){
		case NORMAL:
				//do nothing
				changeModeService();
			break;

		case CONFIG_WITH_WIFI:  //should have time out
				if(millis() - timeout_tcp < TIMEOUT_TCP){
					tcp.handle();
				}else{  //timeout will close socket and return to normal mode
					tcp.close();
					mode = NORMAL;
				}
			break;

		case WORKING:
				//this here for implement main code working each type

				if(wifi.isState() != WL_CONNECTED){
					wifi.reConnect();
				}else{
					mqtt.subscribe("vine/plug/0.1");
				}
				//do something
				changeModeService();
			break;
	}
}

void PlugSmart::setupPinBegin(){
	VineCollection::setupPinBegin(); 
}

void PlugSmart::setupSystem(WiFiClient client){
	VineCollection::setupSystem(client);
}

String PlugSmart::getID(){
	String vineId = "Vine-";
	vineId.concat(String(ESP.getChipId()));
	return vineId;
}

String PlugSmart::getVersion(){
	return String(VERSION);
}

String PlugSmart::getType(){
	return String(TYPE);
}
