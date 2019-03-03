

#define wifi_id "Paylasim"           // Baglanilacak wifi'nin ismi
#define wifi_pw "12345678"     // Baglanilacak wifi'nin sifresi
#define Button1 0x562A // Yukarı Ok Led aç kapa
#define Button2 0x362A // Aşağı Ok Fan aç kapa
#define Button3 0x162A // Sol Ok Kapı aç kapa
#define Button4 0x662A // Sağ Ok Alarm Sistemi Aç Kapa
#define Button5 0x2D2A // Orta Tuş Kapı Kilit Aç Kapa
char Password[5] = {'1','2','3','4','5'};

void alarm();
void alarmoff();
boolean passwordOnaylama();


/* ************************************ Libraries ******************************************** */
#include "DHT.h" // Temperature Humidity Sensor Library
#include <Keypad.h>
#include <Servo.h>              // Servo kutuphanesi projeye dahil edildi.


Servo servoDoor1;                // Servo motor nesnesi yaratildi.

Servo servoDoor2; 
/* ************************************ Pins ******************************************** */ 
int TempHumSensorPin = 53; // Temperature Humidity Pin 53 - 5V
int Flood = 52; // Flood Sensor Pin 52 - 5V
int Fan = 51; // Fan Pin 51 - 5V
int FanReversed=50;//Reversed Fan Pin 50 - 5V
int Photocell = 49; // Photocell Sensor 49 - 5V
int Remote = 48; //Kumanda Pin 48 - 5V
int Microphone = 47; // Mikrofon Pin 47 - 5V
int LightSensor = 46; // LightSensor Pin 46 - 5V
int Lazer = 45; // Lazer Pin 45 - 5V
int LazerIR = 44; // LazerIR Pin 44 - 5V
int SonicDistanceEcho = 42; // SonicDistanceEcho Pin 42 - 5V
int SonicDistanceTri = 40; // SonicDistanceTri Pin 40 - 5V
int FireSensor = 38; // FireSensor Pin 38 - 5V
int MagneticSensor = 36; // Magnetic Sensor Pin 36
int WaterValve =34;
int WaterPump = 32;
int GasValve = 30;
int Buzzer = 4;

int Led1 = 13; // Led Pin 13
int Led2 = 12; // Led Pin 12
int Led3 = 11;  // Ses Kontrol Ledi
int Led4 = 10;  // Işık Sensorü Ledi


int Smoke = A0; // Gas Sensor Pin A0 
int GardenHumidity = A1; // GardenHumidity Sensor Pin A1 


int Door = 47;   // Door Servo Motor - 5V



/* ************************************ KeyPad ******************************************** */ 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'4','5','6','B'},
  {'1','2','3','A'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {29, 31, 33, 35}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {37, 39, 41, 43}; //connect to the column pinouts of the keypad


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char key;

/* ************************************ Durumlar ******************************************** */ 
int FanScenario = 27; // Oda Sıcaklığı Stabil Değer
int FanControl = 0;   // Eğer 1 is Fan Açık, 0 ise Fan Kapalı
int Led2Control = 1;  // Eğer 1 is Led Kapalı, 0 ise Led Açık
int DoorControl = 0;  // Eğer 1 is Kapı Açık , 0 ise Kapı Kapalı
int AlarmControl = 0; // Eğer 1 is Alarm Açık, 0 ise Alarm Kapalı
int DoorLockControl=0;// Eğer 1 is Kapı Kilitli, 0 ise Kapı Kilitli Değil
DHT dht(TempHumSensorPin, DHT11);

int duration,distance;

void setup() {
  Serial.begin(115200);
  /* ************ Input Pins ******************* */
  
  pinMode(TempHumSensorPin,INPUT);  //Temp Sensor Input 
  pinMode(Flood,INPUT);             // Flood pini Input
  pinMode(Smoke,INPUT);              // Smoke pini Input
  pinMode(Photocell,INPUT);         // Photocell pini Input
  pinMode(LightSensor,INPUT);       // Light Sensor pini Input
  pinMode(Microphone, INPUT);       // Microphone pini Input
  pinMode(SonicDistanceEcho, INPUT);       // SonciDistanceEcho pini Input
  pinMode(LazerIR,INPUT);           //LazerIR Output 
  pinMode(FireSensor,INPUT);       //FireSensor Output 
  pinMode(MagneticSensor,INPUT);       //FireSensor Output 
 

  
  /* ************ Output Pins ****************** */
  pinMode(WaterPump,OUTPUT);
  pinMode(WaterValve,OUTPUT);
  pinMode(GasValve,OUTPUT);
  pinMode(FanReversed,OUTPUT);          //Reverse Fan Output
  pinMode(Fan,OUTPUT);          //Normal Fan Output
  pinMode(Led1,OUTPUT);          //Led1 Output
  pinMode(Led2,OUTPUT);          //Led2 Output
  pinMode(Led3,OUTPUT);          //Led3 Output
  pinMode(Led4,OUTPUT);          //Led3 Output
  pinMode(Lazer, OUTPUT);            // Lazer pini Input
  pinMode(SonicDistanceTri, OUTPUT); // SonciDistanceTri pini Input
   pinMode(Buzzer,OUTPUT);
  

  servoDoor1.attach(7);       // Servo motor 43 numarali pine baglandi.
  servoDoor2.attach(8);
  /* *********** Main Codes ******************** */
  dht.begin();
  
    /*Serial.println("Loading...35 sec");                                               
    Serial.println("AT");                         //ESP modülü ile bağlantı kurulup kurulmadığını kontrol eder.
    delay(3000);                                  //ESP ile iletişim için 3 saniye bekler.
    
    if(Serial.find("OK"))
    {                                             //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
       Serial.println("AT+CWMODE=1");             //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanacak.
       delay(2000);
       //String connection = String("AT+CWJAP=\"")+wifi_id+"\",\""+wifi_pw+"\"";
       String connection = String("AT+CWJAP=\"")+wifi_id+"\",\""+wifi_pw+"\"";
       Serial.println(connection);
       delay(3000);
    }
    else{
      Serial.println("Olmadı");   
    }*/
  
  
}

void loop() {
  
  

  
  /************** Garden Humidity ************************/
  
  int gardenHumidityValue = analogRead(GardenHumidity);
  //Serial.println(gardenHumidityValue);
  if(gardenHumidityValue>800){
      Serial.println("Garden Dry");
      digitalWrite(WaterPump, HIGH);
  }
  else{
      Serial.println("Garden Wet");
      digitalWrite(WaterPump, LOW);
  }
  


  
  /************** Magnetic Sensor ************************/
  int magneticValue = digitalRead(MagneticSensor);
  //Serial.println(magneticValue);
  
  /************** FireSensor ********************/
  int FireValue = digitalRead(FireSensor);
  //Serial.println(FireValue);
  if(FireValue != 1){
    digitalWrite(FanReversed, LOW);
    //alarm();
  }
  else if(FireValue == 1){
    digitalWrite(FanReversed, HIGH);
  }
  
  /************* Sonic Distance *****************/
  if(DoorControl == 0){
    digitalWrite(SonicDistanceTri,LOW);
    delayMicroseconds(2);
    digitalWrite(SonicDistanceTri,HIGH);
    delayMicroseconds(10);
    digitalWrite(SonicDistanceTri,LOW);
    duration = pulseIn(SonicDistanceEcho,HIGH);
    distance = duration*0.034/2;
    if(distance <= 5){
       digitalWrite(Led3, HIGH);
    }
    if(distance > 5){
       digitalWrite(Led3, LOW);
    }
  }
  
  
  
  
  /* *********** Microphone ******************** */
  boolean val = digitalRead(Microphone);
  if (val==HIGH && AlarmControl == 1) { // Mikrofon Güvenlik Kullanımı
    alarm();                            // Alarm açık ve mikrofon ses alırsa alarmı aktif et
  }
  /* *********** Photocell ******************** */
  
  int PhotocellValue = digitalRead(Photocell);
  // Serial.println(PhotocellValue);
  
  if(PhotocellValue && DoorLockControl == 1){
    alarm();
  }
  else if(PhotocellValue){
     digitalWrite(Led3, HIGH);
  }
  else if(!PhotocellValue){
    digitalWrite(Led3, LOW);
  }
  /* *********** Smoke ******************** */
  int SmokeValue = analogRead(Smoke);
  //Serial.println(SmokeValue);
  if(SmokeValue > 10){
    digitalWrite(FanReversed, HIGH);
    //alarm();
  }
  else if(SmokeValue < 10){
    digitalWrite(FanReversed, HIGH);
  }
  
  /* *********** Flood ******************** */
  int FloodValue = digitalRead(Flood);
  //Serial.println(FloodValue);
  if(FloodValue){
      digitalWrite(WaterValve, LOW);
      //alarm();      
  }
  else{
    digitalWrite(WaterValve, HIGH);
  }
  /* *********** Temperature Humidity ******************** */
  float HumidityValue = dht.readHumidity();
  float TemperatureValue = dht.readTemperature();
 // Serial.println(TemperatureValue);
  
  if((int)TemperatureValue > FanScenario){
        digitalWrite(Fan, LOW); // TemperatureValue büyükse fanı çalıstır.
  }
  else if(FanControl == 0 && (int)TemperatureValue < FanScenario){
         digitalWrite(Fan, HIGH); // TemperatureValue küçükse fanı durdur. 
  }
  /* ************* Light Sensor *************************** */  
  int lightValue = digitalRead(LightSensor);
  //Serial.println(lightValue);
  if(lightValue == 1){
        digitalWrite(Led4, HIGH); 
  }
  if(lightValue == 0){
        digitalWrite(Led4, LOW); 
  }
  
  
  /* ************* Remote *************************** */
  key = keypad.getKey();
  if (key) {
    if(key == '*'){ //Led aç Kapa (Yukarı Ok)
      if(Led2Control == 0){
        Led2Control=1;
        digitalWrite(Led2, HIGH);
      }
      else if(Led2Control == 1){
        Led2Control=0;
        digitalWrite(Led2, LOW);
      }
    }
    if(key == '#'){ //Fan aç Kapa (Aşağı Ok)
      if(FanControl == 0){
        FanControl=1;
        digitalWrite(Fan, LOW);
      }
      else if(FanControl == 1){
        FanControl=0;
        digitalWrite(Fan, HIGH);
      }
    }
    if(key == 'A'){ //Kapı aç kapa (Sol Ok)
        if(servoDoor1.read() != 0){ // Kapı Açık
              servoDoor1.write(0);  //Kapıyı Kapat
              DoorControl = 1;     //Kapıyı Kapalı
              Serial.println("Door Close")  ;          
        }   
        
        else if(servoDoor1.read() != 90 && DoorLockControl == 0){ //Kapı Kapalı
              DoorControl = 0;      //Kapıyı Açıldı
              servoDoor1.write(90);  // Kapı Açık
              Serial.println("Door Open") ;          
        } 
    } 
    if(key == '0'){ //Kapı aç kapa (Sol Ok)
        if(servoDoor2.read() != 0){ // Kapı Açık
              servoDoor2.write(0);  //Kapıyı Kapat
              DoorControl = 1;     //Kapıyı Kapalı
              Serial.println("Door Close")  ;          
        }   
        
        else if(servoDoor2.read() != 90 && DoorLockControl == 0){ //Kapı Kapalı
              DoorControl = 0;      //Kapıyı Açıldı
              servoDoor2.write(90);  // Kapı Açık
              Serial.println("Door Open") ;          
        } 
    } 
    if(key == 'B'){ //Alarm Sistemi aç Kapa (Sağ Ok)
        if(AlarmControl == 0){ //Alarm sistemini aç
              AlarmControl = 1; 
              Serial.println("Alarm Control On");
        }   
        
        else if(AlarmControl == 1){ //Alarm sistemini Kapat
              AlarmControl = 0; 
              Serial.println("Alarm Control Off");
        }
    }
    if(key == 'C'){ //Kapı kilit aç kapa (Orta Tuş)
        if(DoorLockControl==1 && passwordOnaylama()){
              DoorLockControl = 0;
              Serial.println("Door Unlocked");
        }   
        
        else if(DoorLockControl == 0 && DoorControl == 1){
              DoorLockControl = 1;
              Serial.println("Door Locked");
        }
    }
  }
}
void alarmoff(){
  digitalWrite(Led2, LOW);
  digitalWrite(Led1, LOW);
  digitalWrite(Led3, LOW); 
  Serial.println("Alarm Off");
}
boolean passwordOnaylama(){
  int i=0;  
  int counter = 0;
  key = '0';
  while(key != '*'){
      key = keypad.getKey();
      if(key){
          Serial.println(key);
          if(key == Password[i]){
              counter++;
              Serial.print("Counter:");
              Serial.println(counter);
              i++;  
          } 
      }
          
  }
  if(counter == 5){
    
    return true;
  }
  return false;
}
void alarm(){
 AlarmControl = 1;
  while(AlarmControl != 0){
    digitalWrite(Led2, HIGH);
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    tone(Buzzer,500,2000);
    if(passwordOnaylama()){
          alarmoff();
          AlarmControl = 0;
          noTone(Buzzer);
    }
    
  }
}
