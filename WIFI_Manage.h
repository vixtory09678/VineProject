// wifi tcp default IP 192.168.99.9 Gateway 192.168.99.1 Subnet 255.255.255.0

#ifndef WIFI_MANAGE_H
#define WIFI_MANAGE_H

#include "ESP8266WiFi.h"
#include "Arduino.h"

/*typedef enum {
    WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
    WL_IDLE_STATUS      = 0,
    WL_NO_SSID_AVAIL    = 1,
    WL_SCAN_COMPLETED   = 2,
    WL_CONNECTED        = 3,
    WL_CONNECT_FAILED   = 4,
    WL_CONNECTION_LOST  = 5,
    WL_DISCONNECTED     = 6
} wl_status_t;*/

class WIFI_Manage
{
public:
	uint8_t connect(const char* ssid, const char* password);
	wl_status_t isState();
	bool reConnect();

	void setModeWiFiShare();
	void setModeWiFiClient();

};

#endif
