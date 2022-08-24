//Inicia Config del Bluetooth
#include <Adafruit_INA260.h> //incluir librería del INA260
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

Adafruit_INA260 ina260 = Adafruit_INA260();

String Enviados[] = {"0","0","0"}; //Hacemos un arreglo para los datos a enviar

double entrada; //Declaramos una variables para los datos de entrada
 
int periodo = 300000000; //El tiempo que se demora en enviar un nuevo dato a la aplicacion
unsigned long TiempoAhora = 0; //Variable para determinar el tiempo transcurrido
//Termina config del Bluetooth

//Inicia Config del sleep
#define uS_TO_S_FACTOR 1000000  /* us to s */
int TIME_TO_SLEEP = 2700;        /* sleep time seconds */

RTC_DATA_ATTR int bootCount = 0;

void programa(){
  if(millis() > TiempoAhora + periodo){ //Hacemos el ciclo para la emision de datos a la aplicacion
        
       
if (SerialBT.available()>0){ //Si hay datos enviados por la aplicacion
    entrada=SerialBT.read(); //Leemos los datos recibidos
    

    if(entrada=='A') {  //Si el dato recibido es B, se apaga el led
      Enviados[0] = ina260.readBusVoltage(); //Localizar el dato de voltaje que retorna el INA260
      Enviados[1] = ina260.readCurrent();//Localizar el dato de corriente que retorna el INA260
      Enviados[2] = ina260.readPower();//Localizar el dato de potencia que retorna el INA260
    }
    
  }
  
        
        TiempoAhora = millis();
        SerialBT.println(Enviados[0]);
        SerialBT.println(",");
        SerialBT.println(Enviados[1]);
        SerialBT.println(",");
        SerialBT.println(Enviados[2]);
        Serial.println();
    }

  }
  


void setup(){
  Serial.begin(115200);
  delay(1000);

  //Increment boot number and print it every reboot
++bootCount;

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  /*
  By default, ESP32 will automatically power down the peripherals
  not needed by the wakeup source,
  */
  if(bootCount=1){
  delay(1000);
  programa();
  delay(900*uS_TO_S_FACTOR);
   Serial.flush(); 
  esp_deep_sleep_start();
    }

  if(bootCount=2){
  delay(1000);
  programa();
  delay(900*uS_TO_S_FACTOR);
   Serial.flush(); 
  esp_deep_sleep_start();
    }

    if(bootCount=3){
  delay(1000);
  programa();
  delay(900*uS_TO_S_FACTOR);
   Serial.flush(); 
  esp_deep_sleep_start();
    }

    if(bootCount=4){
  delay(1000);
  programa();
  delay(900*uS_TO_S_FACTOR);
   Serial.flush(); 
  esp_deep_sleep_start();
    }

   if(bootCount=5){
  delay(1000);
  programa();
  delay(900*uS_TO_S_FACTOR);
   Serial.flush(); 
  esp_deep_sleep_start();
    }
    
   if(bootCount=6){
  delay(1000);
  programa();
  delay(900*uS_TO_S_FACTOR);
  TIME_TO_SLEEP = 2700+64800; //Se setea el tiempo de sleep mode a 18 horas + 45 minutos
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  bootCount=0;
  Serial.flush(); 
  esp_deep_sleep_start();
    }
  
}

void loop() {
  //This is not going to be called
}
