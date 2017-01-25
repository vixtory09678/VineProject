#include "WIFI_Manage.h"

uint8_t WIFI_Manage::connect(const char* ssid , const char* password){
	WiFi.begin(ssid,password);
	return WiFi.waitForConnectResult();
}

wl_status_t WIFI_Manage::isState(){
	return WiFi.status();
}

bool WIFI_Manage::reConnect(){
	return WiFi.reconnect();
}

void WIFI_Manage::setModeWiFiShare(){
	if(WiFi.mode(WIFI_AP)){
		#ifdef DEBUG
			Serial.println(F("Change mode to WIFI_AP"));
		#endif
	}

	if(WiFi.softAPConfig(IPAddress(192,168,99,9) , IPAddress(192,168,99,1) , IPAddress(255,255,255,0))){
		#ifdef DEBUG
			Serial.println(F("AP setup success!."));
		#endif
    WiFi.softAP("VINE-WIFI-SETTING");
	}else{
		#ifdef DEBUG
			Serial.println(F("AP setup fail!."));
		#endif
	}

}

void WIFI_Manage::setModeWiFiClient(){
	if(WiFi.mode(WIFI_STA)){
		#ifdef DEBUG
			Serial.println(F("Change mode to WIFI_STA"));
		#endif
	}
}
