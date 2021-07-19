#include <SoftwareSerial.h>
#include <TinyGPS.h>

int state = 0;
const int pin = 9;
float gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);

void setup()
{
  sgsm.begin(9600);
  sgps.begin(9600);
}

void loop()
{
sgps.listen();
  while (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
    if (digitalRead(pin) == HIGH && state == 0) {
      Serial.print("True");
      sgsm.listen();
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      /*Replace XXXXXXXXXX to 10 digit mobile number &
        ZZ to 2 digit country code*/
      sgsm.print("AT+CMGS=\"+91XXXXXXXXXX\"\r"); //Add Your Phone Number 
      delay(1000);
      //The text of the message to be sent.
      sgsm.print("HELP ME OUT!,I AM IN DANGER");
      sgsm.println();
      sgsm.print("http://maps.google.com/maps?q=loc:");	
      //sgsm.print("Latitude :");
      sgsm.println(gpslat, 6);
      sgsm.print(",");
      //sgsm.print("Longitude:");
      sgsm.println(gpslon, 6);
      Serial.print("Working");
      delay(1000);
      
      sgsm.write(0x1A);
      delay(1000);
      state = 1;
    }
  if (digitalRead(pin) == LOW) {
      state = 0;
    }
  }
