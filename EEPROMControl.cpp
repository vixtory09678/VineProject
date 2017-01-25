#include "EEPROMControl.h"

EEPROMControl* EEPROMControl::eepromInstance = NULL;

EEPROMControl* EEPROMControl::getInstance(){
	if(!eepromInstance)
		eepromInstance = new EEPROMControl;
	return eepromInstance;
}

EEPROMControl::EEPROMControl(){
  EEPROM.begin(512);
}

void EEPROMControl::clear(){
  for(int i = 0; i < 512 ; i++){
    EEPROM.write(i,0);
  }
}

void EEPROMControl::save(saveType type,char* dataWrite,int size){
	if(size < LENGTH_ADDR){
		switch(type){
			case SSID:
					for(int i = ADDR_SSID; i < size ; i++)
						EEPROM.write(i,(int)dataWrite[i]);
					EEPROM.write(size,'\n');
				break;

			case PASSWORD:
					for(int i = 0; i < size ; i++)
						EEPROM.write((i+ADDR_PASSWORD),(int)dataWrite[i]);
					EEPROM.write((size + ADDR_PASSWORD),'\n');
				break;
		}
	}
}

String EEPROMControl::read(saveType type){
  String dataRead = "";
	switch(type){
		case SSID:
				for(int i = ADDR_SSID; EEPROM.read(i)!='\n' ; i++)
					dataRead += (char)EEPROM.read(i);
			break;

		case PASSWORD:
				for(int i = ADDR_PASSWORD; EEPROM.read(i)!='\n' ; i++){
					dataRead += (char)EEPROM.read(i);
				}
			break;
	}
  return dataRead;
}

