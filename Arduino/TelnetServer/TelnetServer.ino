/*
 Telnet client

 This sketch connects to a telnet server (http://www.google.com)
 using an Arduino WIZnet Ethernet shield.  You'll need a telnet server
 to test this with.
 Processing's ChatServer example (part of the Network library) works well,
 running on port 10002. It can be found as part of the examples
 in the Processing application, available at
 https://processing.org/

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 14 Sep 2010
 modified 9 Apr 2012
 by Tom Igoe
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 50, 177);
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(23);

#define RST 4

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH Shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet

  pinMode(BUILTIN_LED, OUTPUT);
  Ethernet.init(5); 
  pinMode(RST, OUTPUT);

  // Reset W5500
  digitalWrite(RST, HIGH);
  delay(200);
  digitalWrite(RST, LOW);
  delay(200);
  digitalWrite(RST, HIGH);
  
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Ethernet.begin(mac, ip, gateway, subnet);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  while (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    delay(500);
  }

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  Serial.print(" IP address = ");
  Serial.println(Ethernet.localIP());

  server.begin();

}

void loop() {

}
