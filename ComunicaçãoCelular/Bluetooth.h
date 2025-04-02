//Não modificar esse código!!!
//Biblioteca Bluetooth
#include "BluetoothSerial.h"

//============================================================================================================
String device_name = "PETEletrica ESP32"; //Nome do ESP 32 na rede Bluetooth

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
//============================================================================================================