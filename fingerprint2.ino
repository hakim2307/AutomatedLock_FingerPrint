#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();
SoftwareSerial mySerial(2, 3);// tx, rx
const int buttonPin = 9;
int buttonState = 0;  
const int buttonPin2 = 10;//tukar mana port yang available
int buttonState1 = 0;  
const int buttonPin3 = 11;//tukar mana port yang available
int buttonState2 = 0;  


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


 void doorOpen()
{
  lcd.clear();
  lcd.print("WELOME");
  buttonState = digitalRead(buttonPin);
 if(finger.fingerID==0)
  {
  Serial.println("Welcome Amirul Hakim");//i enroled ID no 1 as Nidhi'sfingerprint, so used this line to display corresponding name
  
  lcd.setCursor(0, 1);
  lcd.print("Hakim");
  delay(500);
  lcd.clear();
//=======================================================first button  
   if (buttonState == HIGH)
   {
   Serial.println("Open");
   lcd.print("Door Open");
  digitalWrite(8,LOW);
  delay(5000);
 
  }
  else if(buttonState== LOW ){
    Serial.println("Closed");
    //doorClose();
    }
// =======================================================second button   
     if (buttonState1 == HIGH)
   {
   Serial.println("Open");
   lcd.print("Door Open");
  digitalWrite(9,LOW);
  delay(5000);
 
  }
  else if(buttonState1== LOW ){
    Serial.println("Closed");
    //doorClose();
   }
//  ======================================================third button
      if (buttonState2 == HIGH)
   {
   Serial.println("Open");
   lcd.print("Door Open");
  digitalWrite(9,LOW);
  delay(5000);
 
  }
  else if(buttonState2== LOW ){
    Serial.println("Closed");
    //doorClose();
    }   
   }
 if(finger.fingerID==3)
  {
  Serial.println("Welcome Lydia");//i enroled ID no 1 as Nidhi'sfingerprint, so used this line to display corresponding name
  
  lcd.setCursor(0, 1);
  lcd.print("Lydia");
  delay(500);
  lcd.clear();
  
   if (buttonState == HIGH)
   {
   Serial.println("Open");
   lcd.print("Door Open");
  digitalWrite(8,LOW);
  delay(5000);
 
  }
  if(buttonState== LOW ){
    Serial.println("Closed");
    //doorClose();
    }
    // =======================================================second button   
     if (buttonState1 == HIGH)
   {
   Serial.println("Open");
   lcd.print("Door Open");
  digitalWrite(9,LOW);
  delay(5000);
 
  }
  else if(buttonState1== LOW ){
    Serial.println("Closed");
    //doorClose();
   }
//  ======================================================third button
      if (buttonState2 == HIGH)
   {
   Serial.println("Open");
   lcd.print("Door Open");
  digitalWrite(9,LOW);
  delay(5000);
 
  }
  else if(buttonState2== LOW ){
    Serial.println("Closed");
    //doorClose();
    }
   }
}


void doorClose()
{
   lcd.clear();
  digitalWrite(8,HIGH);
  digitalWrite(14,HIGH);
  digitalWrite(15,HIGH);
  lcd.print("No valid finger");
  lcd.setCursor(0, 1);
  lcd.print("on the sensor");
   
}





void setup()  
{
 pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
   pinMode(buttonPin3, INPUT);

  lcd.begin(16, 2);
  Serial.begin(38400);
  Serial.println("fingertest");
  finger.begin(57600);
  pinMode(8,OUTPUT);//Pin connectet to relay
   digitalWrite(8,HIGH);
    pinMode(14,OUTPUT);//jangan lupa tukar mana pin yang available(yang ini untuk relay)
   digitalWrite(14,HIGH);
    pinMode(15,OUTPUT);//jangan lupa tukar mana pin yang available
   digitalWrite(15,HIGH);
  
  if (finger.verifyPassword())
  {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.print("Sensor not Found");
    while (1);
  }
  Serial.println("No valid finger found,waiting for valid finger...");
  lcd.print("Welcome Finger ");
  lcd.setCursor(0, 1);
  lcd.print("prt Lock Sys");
  }

  
  
  void loop()                     // run over and over again
{
      
  if(getFingerprintIDez()>=0)
  {
        doorOpen();
        delay(1000);
        doorClose();
  }
  
    
}
uint8_t getFingerprintID()
{
  uint8_t p = finger.getImage();
  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
        default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) 
  {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
