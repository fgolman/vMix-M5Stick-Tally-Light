#include <WiFi.h>
#include <M5StickC.h>
#include <PinButton.h>
#include <WebServer.h>
#include <Preferences.h>

#define LED_BUILTIN 10

Preferences preferences;

//DON'T CHANGE THESE VARIABLES, YOU CAN CHANGE THEM IN THE WEB UI
String WIFI_SSID = "";
String WIFI_PASS = "";
String VMIX_IP = "";
String M_TALLY = "";
int VMIX_PORT = 8099; //USES THE TCP API PORT, THIS IS FIXED IN VMIX
int TALLY_NR = 1;
int BRIGHTNESS = 12; //100%