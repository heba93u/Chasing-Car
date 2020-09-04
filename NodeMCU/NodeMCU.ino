//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "chasing-car.firebaseio.com" 
#define FIREBASE_AUTH "ypWUWkAwlsF9tjCDotfI3ztpscuDBf9UjxHTvhYe" 
#define WIFI_SSID "Home_"
#define WIFI_PASSWORD "0525344440"


//Define FirebaseESP8266 data object
FirebaseData firebaseData;

 String ID;
 String lastID = "99";
 String wantedPerson;
#define TRIG_PIN A4 
#define ECHO_PIN A5 


const int motorPin1  = 5;  
const int motorPin2  = 4;  
//Motor B
const int motorPin3  = 0; 
const int motorPin4  = 2;  


void setup()
{
  pinMode(5,OUTPUT);   //left motors forward
pinMode(4,OUTPUT);   //left motors reverse
pinMode(0,OUTPUT);   //right motors forward
pinMode(2,OUTPUT);   //right motors reverse
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

    if (Firebase.getString(firebaseData, "/wantedPerson"))
  {
     if (firebaseData.dataType() == "string")
     {
      wantedPerson=firebaseData.stringData();
      Serial.println(wantedPerson);
      Serial.println();
     }
       
  }
  else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
}
void loop()
{

  if (Firebase.getString(firebaseData, "/ID"))
  {
     if (firebaseData.dataType() == "string")
     {
      ID=firebaseData.stringData();
      if(ID == "NULL"){
//        delay(500);
        return;
      }
      Serial.println(ID);
      Serial.println();
      if(ID != lastID){
        lastID = ID;
        Serial.println("CHANGE");
        if(ID == wantedPerson){
          //ro7 l3ndo
           moveForward();
           delay(500);
          moveStop();
//            myservo.write(90);              // tell servo to go to position in variable 'pos'
//            delay(15); 
//            myservo.write(0);              // tell servo to go to position in variable 'pos'
//            delay(15); 
           }else{
            //ro7 shmal
            turnLeft();  turnLeft();
          
//            delay(100);
//            turnRight();
            moveStop();
            }
       }
     }
       
  }
  else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }


  delay(500);

}


void moveStop() {
  digitalWrite(motorPin1, 0);
    digitalWrite(motorPin2, 0);
    digitalWrite(motorPin3, 0);
    digitalWrite(motorPin4, 0);
  } 
  
void moveForward() {


    digitalWrite(motorPin1, 180);
    digitalWrite(motorPin2, 0);
    digitalWrite(motorPin3, 180);
    digitalWrite(motorPin4, 0);  
  
}

void moveBackward() {
    
    digitalWrite(motorPin1, 0);
    digitalWrite(motorPin2, 180);
    digitalWrite(motorPin3, 0);
    digitalWrite(motorPin4, 180);   
  
}  

void turnRight() {
  digitalWrite(motorPin1, 180);
  digitalWrite(motorPin2, 0);
  digitalWrite(motorPin3, 0);
  digitalWrite(motorPin4, 180);    
  delay(300);
 moveForward();      
  
} 
 
void turnLeft() {
  digitalWrite(motorPin1, 0);
  digitalWrite(motorPin2, 180);   
  digitalWrite(motorPin3, 180);
  digitalWrite(motorPin4, 0);     
  delay(300);
   moveForward();
}  
