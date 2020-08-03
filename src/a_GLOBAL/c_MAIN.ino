WiFiClient client;
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

PinButton btnM5(37);
PinButton btnReconnect(39);

char currentState = -1;
char screen = 0;
bool connectedTovMix = false;

char deviceName[32];
int status = WL_IDLE_STATUS;
bool apEnabled = false;
char apPass[64];

// Time measure
int interval = 5000;
unsigned long lastCheck = 0;

void setup()
{
  Serial.begin(115200);
  M5.begin();
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  loadSettings();
  
  Serial.print("SSID: ");
  Serial.println(&(WIFI_SSID[0]));
  Serial.print("PASS: ");
  Serial.println(&(WIFI_PASS[0]));

  start();
}

void loop()
{
  server.handleClient();
  btnM5.update();
  if (btnM5.isClick()) {
    if (screen == 0) {
      showNetworkScreen();
    } else if (screen == 1) {
      showTallyNum();
    } else if (screen == 2) {
      showTallyScreen();
    }
  }
  
  btnReconnect.update();
  if (btnReconnect.isClick()) {
    connectTovMix(false);
  }
  
  while (client.available())
  {
    server.handleClient();
    String data = client.readStringUntil('\r\n');
    handleData(data);
  }
  
  if (!client.connected() && !apEnabled && millis() > lastCheck + interval)
  {
    client.stop();
    connectTovMix(false);
    lastCheck = millis();
  }
}

void cls()
{
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 0);
}

void start()
{
  cls();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(20, 20);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.println("vMix M5Stick-C Tally");
  M5.Lcd.setCursor(35, 40);
  M5.Lcd.println("by Guido Visser");
  delay(2000);

  startWiFi();
}

void resetScreen(){
  cls();
  digitalWrite(LED_BUILTIN, HIGH);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE, BLACK);
}