#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
// You have to take care of the pin layout, it might conflict with the Ethernet shield's layout.
// See example code

byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

EthernetClient client;

void setup() {

  lcd.begin(16, 2);
  lcd.print("START");
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  
  printIPAddress();
}

void loop() {

  switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      printIPAddress();
      lcd.setCursor(0, 1);
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      printIPAddress();
      break;

    default:

      lcd.setCursor(0, 1);
      lcd.print("Uptime: ");
      lcd.print(millis() / 1000);
      
      break;

  }
}

void printIPAddress()
{
  lcd.clear();
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
    lcd.print(Ethernet.localIP()[thisByte], DEC);
    lcd.print(".");
  }

  Serial.println();
}
