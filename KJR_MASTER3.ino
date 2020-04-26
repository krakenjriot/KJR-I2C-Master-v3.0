/***
 *      _  ______      _    _  _______ _   _       _ ____      ___ ___ _____ 
 *     | |/ /  _ \    / \  | |/ / ____| \ | |     | |  _ \    |_ _/ _ \_   _|
 *     | ' /| |_) |  / _ \ | ' /|  _| |  \| |  _  | | |_) |    | | | | || |  
 *     | . \|  _ <  / ___ \| . \| |___| |\  | | |_| |  _ < _   | | |_| || |  
 *     |_|\_\_| \_\/_/   \_\_|\_\_____|_| \_|  \___/|_| \_(_) |___\___/ |_|  
 *     
 *                         LET THIS BE FREE FOREVER!
 *              DEVELOPER AND CREATOR: ROLLY FALCO VILLACACAN
 *                                YEAR 2020
 *                                                                           
 */

 
// Include Arduino Wire library for I2C
#include <Wire.h>
#include <TroykaDHT.h>

// типы сенсоров: DHT11, DHT21, DHT22
DHT dht(2, DHT22);

// Define Slave I2C Address
#define SLAVE_KJR_ADDR 9

// Define Slave answer size
#define ANSWERSIZE 25

// Initialize sensor variables
float temp, hum;
char Rx_buf[ANSWERSIZE] = "";
char Rx_cached_buf[ANSWERSIZE] = "";
char group_x = 'X';
char group_y = 'Y';
char group_z = 'Z';  
  
void setup() {
  // Initialize I2C communications as Master
  Wire.begin();  
  Serial.begin(9600);
  dht.begin();
  pinMode(8,OUTPUT);
  Serial.println("I Am Master!");  
}




void loop() {
	
    // считывание данных с датчика
  dht.read();
  // проверяем состояние данных
  switch(dht.getState()) {
    // всё OK
    case DHT_OK:
      // выводим показания влажности и температуры
      Serial.print("Temperature = ");
      Serial.print(dht.getTemperatureC());
      temp = dht.getTemperatureC();
      Serial.println(" C \t"); 
      Serial.print("Humidity = ");
      Serial.print(dht.getHumidity());
      hum = dht.getHumidity();
      Serial.println(" %");
      break;
    // ошибка контрольной суммы
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    // данных нет, датчик не реагирует или отсутствует
    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;
  }  

    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    Wire.requestFrom(SLAVE_KJR_ADDR,ANSWERSIZE); int i;  for (i=0; i < ANSWERSIZE; i++)  {    Rx_buf[i] = Wire.read();  }	Rx_buf[i] = '\0';
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********


    //RULES
    //TO SEND DATA TO KJR
    //COMMA DELIMITTED
    //FIRST COLUMN SHOULD BE X, OR Y,
    //SHOULD BE TERMINATED WITH x,
    //TO SEND DIGITAL INPUT should start with m ie. m12345678
    //
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********    
    float value; //DONT CHANGE
    char buff_b[10]; //DONT CHANGE  
    char result[80]; //DONT CHANGE
    char board_id = '2'; //board number #1-KJR #2-SLAVE
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY********** 

    //DIGITAL OUTPUT!!!!!!!!!!
    //char od8[8] = "8:1:2,"; //od#:board#:pin#
    digitalWrite(8, Rx_cached_buf[0] == '1'?true:false); 
    //Serial.print("PIN8 = ");
    //Serial.println(Rx_cached_buf[2]);  
    //DIGITAL OUTPUT!!!!!!!!!!
    

    

    
  

    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //if(Rx_buf[0] == 'S'){ 
      
        //Serial.println("KRAKEN SAID STOP SENDING!"); 
        //strcpy( Rx_buf, "" );
      
      //}
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    
    
	//SLAVE SAID PLEASE SEND ME DATA
  //XXXXXXXXX
  if(Rx_buf[0] == group_x){ //*******DO NOT MODIFY**********
    //DIGITAL INPUT FORMATTING
    bool x_id1 = 1;
    bool x_id2 = 0;
    bool x_id3 = 1;
    bool x_id4 = 1;
    bool x_id5 = 1;
    bool x_id6 = 1;
    bool x_id7 = 0;
    bool x_id8 = 1;
    char m_x[8];    
    sprintf(m_x,"%c%i%i%i%i%i%i%i%i",'m',x_id1,x_id2,x_id3,x_id4,x_id5,x_id6,x_id7,x_id8);
        
    //*******DO NOT MODIFY**********
    sprintf(result,"%c%c", group_x, ',');//*******DO NOT MODIFY**********
    Wire.beginTransmission(SLAVE_KJR_ADDR);//*******DO NOT MODIFY**********
    Wire.write(result);//*******DO NOT MODIFY**********
    Wire.endTransmission(); //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    
    //value = random(99);
    //value = 121;    
    dtostrf(temp, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '1',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 122;    
    dtostrf(hum, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '2',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 123;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '3',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 124;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '4',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 125;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '5',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 126;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '6',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 127;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '7',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 128;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '8',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission();   
        
    //digital input group  
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(m_x);
    //Wire.write("m11111111");
    Wire.endTransmission(); 
    
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //every transmission should be terminated, with last transmit with x letter
    Wire.beginTransmission(SLAVE_KJR_ADDR);//*******DO NOT MODIFY**********
    Wire.write("x");//*******DO NOT MODIFY**********
    Wire.endTransmission();//*******DO NOT MODIFY**********     
    strcpy( Rx_cached_buf, Rx_buf );//*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********  
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    Serial.print("Rx_cached_buf = ");
    Serial.println(Rx_cached_buf);    
  } //*******DO NOT MODIFY********** 
  
  //YYYYYYYYYYY
  else if(Rx_buf[0] == group_y){ //*******DO NOT MODIFY**********
    //DIGITAL INPUT FORMATTING
    bool y_id1 = 0;
    bool y_id2 = 0;
    bool y_id3 = 1;
    bool y_id4 = 1;
    bool y_id5 = 0;
    bool y_id6 = 1;
    bool y_id7 = 1;
    bool y_id8 = 1;
    char m_y[8];    
    sprintf(m_y,"%c%i%i%i%i%i%i%i%i",'m',y_id1,y_id2,y_id3,y_id4,y_id5,y_id6,y_id7,y_id8);
        
    //*******DO NOT MODIFY**********
    sprintf(result,"%c%c", group_y, ',');//*******DO NOT MODIFY**********
    Wire.beginTransmission(SLAVE_KJR_ADDR);//*******DO NOT MODIFY**********
    Wire.write(result);//*******DO NOT MODIFY**********
    Wire.endTransmission(); //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    
    value = random(99);
    //value = 121;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '1',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 122;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '2',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 123;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '3',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 124;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '4',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 125;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '5',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 126;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '6',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 127;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '7',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 128;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '8',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission();     
        
    //digital input group  
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    //Wire.write("m11111111");
    Wire.write(m_y);
    Wire.endTransmission(); 
    
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //every transmission should be terminated, with last transmit with x letter
    Wire.beginTransmission(SLAVE_KJR_ADDR);//*******DO NOT MODIFY**********
    Wire.write("x");//*******DO NOT MODIFY**********
    Wire.endTransmission();//*******DO NOT MODIFY**********     
    strcpy( Rx_cached_buf, Rx_buf );//*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********  
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    Serial.print("Rx_cached_buf = ");
    Serial.println(Rx_cached_buf);    
  } //*******DO NOT MODIFY**********      
  

  //ZZZZZZZZZZZZZZZZZZZ
  else if(Rx_buf[0] == group_z){ //*******DO NOT MODIFY**********
    //DIGITAL INPUT FORMATTING
    bool y_id1 = 0;
    bool y_id2 = 0;
    bool y_id3 = 1;
    bool y_id4 = 1;
    bool y_id5 = 0;
    bool y_id6 = 1;
    bool y_id7 = 2;
    bool y_id8 = 2;
    char m_z[8];    
    sprintf(m_z,"%c%i%i%i%i%i%i%i%i",'m',y_id1,y_id2,y_id3,y_id4,y_id5,y_id6,y_id7,y_id8);
        
    //*******DO NOT MODIFY**********
    sprintf(result,"%c%c", group_z, ',');//*******DO NOT MODIFY**********
    Wire.beginTransmission(SLAVE_KJR_ADDR);//*******DO NOT MODIFY**********
    Wire.write(result);//*******DO NOT MODIFY**********
    Wire.endTransmission(); //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    
    value = random(99);
    //value = 121;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '1',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 122;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '2',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 123;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '3',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 124;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '4',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 125;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '5',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 126;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '6',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 

    value = random(99);
    //value = 127;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '7',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission(); 
    
    value = random(99);
    //value = 128;    
    dtostrf(value, 3, 2, buff_b);  
    sprintf(result,"%c%c%s%c", '8',board_id, buff_b, ',');
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    Wire.write(result);
    Wire.endTransmission();     
        
    //digital input group  
    Wire.beginTransmission(SLAVE_KJR_ADDR);
    //Wire.write("m11111111");
    Wire.write(m_z);
    Wire.endTransmission(); 
    
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    //every transmission should be terminated, with last transmit with x letter
    Wire.beginTransmission(SLAVE_KJR_ADDR);//*******DO NOT MODIFY**********
    Wire.write("x");//*******DO NOT MODIFY**********
    Wire.endTransmission();//*******DO NOT MODIFY**********     
    strcpy( Rx_cached_buf, Rx_buf );//*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********  
    //*******DO NOT MODIFY**********
    //*******DO NOT MODIFY**********
    Serial.print("Rx_cached_buf = ");//
    Serial.println(Rx_cached_buf);
  } //*******DO NOT MODIFY**********   
   
  else {
    Serial.println("KRAKEN SAID STOP SENDING!"); 
    strcpy(Rx_buf, ""); 
  }  

	
	//RESET

	
	//Serial.println("Sleeping...for 10 seconds!");
	
	delay(2000);
	
}
