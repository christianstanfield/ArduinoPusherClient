#include <Logging.h>

#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PusherClient.h>
#include <WiFi.h>

char ssid[] = ""; //  your network SSID (name)
char pass[] = "";

int status = WL_IDLE_STATUS;
#define LOGLEVEL LOG_LEVEL_DEBUG

// byte mac[] = { 0x78, 0xC4, 0xE, 0x2, 0x51, 0x28 };
PusherClient client;

int led = 8;

void setup() {
  Log.Init(LOGLEVEL, 38400L);

  pinMode(led, OUTPUT);

  Serial.begin(9600);

   if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while(true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");

  if(client.connect("")) {
    client.bind("forward", moveForward);
    client.bind("backward", moveBackward);
    client.bind("turn_left", turnLeft);
    client.bind("turn_right", turnRight);
    client.bind("stop", stopMoving);
    client.subscribe("robot_channel");
    Serial.println("You win");
  }
  else {
    Serial.println("\nSad face");
    while(1) {}
  }
}

void loop() {
 if (client.connected()) {
    client.monitor();
 }
 else {
  client.connect("");
  client.bind("forward", moveForward);
  client.bind("backward", moveBackward);
  client.subscribe("robot_channel");
 }
}

void moveForward(String data) {
  digitalWrite(led, HIGH);
  delay(1000);
}

void moveBackward(String data) {
  digitalWrite(led, LOW);
  delay(1000);
}

void turnLeft(String data) {
}

void turnRight(String data) {
}

void stopMoving(String data) {
}
