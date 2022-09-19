

#include <ESPTelnetClient.h>

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266WiFiMulti.h>
#endif

//Enter your Wifi details here (multiple SSIDs possible)
#ifndef STASSID
#define STASSID "**********"
#define STAPSK  "**********"
#define STASSID2 "*********"
#define STAPSK2  "*********"
#endif

//put here your raspi ip address, and login details
IPAddress mikrotikRouterIp (192, 168, 1, 2);
const char* user = "************";
const char* pwd = "***********"; 

const char* ssid     = STASSID;
const char* password = STAPSK;
const char* ssid2     = STASSID2;
const char* password2 = STAPSK2;


ESP8266WiFiMulti WiFiMulti;

WiFiClient client;
                                 
ESPtelnetClient tc(client); 

    

void setup () { 

                                       
  Serial.begin (9600);                              
// We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  WiFiMulti.addAP(ssid2,password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connecting.... ");

  //WHICH CHARACTER SHOULD BE INTERPRETED AS "PROMPT"?
  tc.setPromptChar('>');

  //this is to trigger manually the login 
  //since it could be a problem to attach the serial monitor while negotiating with the server (it cause the board reset)
  //remove it or replace it with a delay/wait of a digital input in case you're not using the serial monitors
  char key = 0;
  Serial.println("\r\npress Enter to begin:");
  do{
    key = Serial.read();
  }while(key<=0);
  
  //PUT HERE YOUR USERNAME/PASSWORD
  if(tc.login(mikrotikRouterIp, "admin", "")){        //tc.login(mikrotikRouterIp, "admin", "", 1234) if you want to specify a port different than 23
    tc.sendCommand("ip");
    tc.sendCommand("address");
    tc.sendCommand("print");
         
  }
  else{
    Serial.println("login failed");
  }
  tc.disconnect();
}

void loop () {                                         //  run your loop routine
}
