#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define largo 14

// Function prototypes
void subscribeReceive(char* topic, byte* payload, unsigned int length);
 
// Set your MAC address and IP address here
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 101);
 
// Make sure to leave out the http and slashes!
//const char* server = "192.168.0.100";
IPAddress server(192, 168, 0, 100);
 
// Ethernet and MQTT related objects
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);


long int ID[largo]={0x500,0x501,0x502,0x503,0x504,0x505,0x506,0x507,0x508,0x400,0x401,0x680,0x700,0x701};

byte DLC[largo]={8, 8, 7, 6, 6, 8, 7, 6, 6,8,8,3,8,8};

char data[largo][8] = 
{{0x45, 0x4C, 0x49, 0x54, 0x48, 0x49, 0x4F, 0x4E},//500
{0x32, 0x43, 0x4E, 0x46, 0x32, 0x2E, 0x33, 0x35}, //501
{0xff, 0x02, 0xA1, 0x02, 0x0B, 0x00, 0x80},       //502
{0x00, 0x20, 0x28, 0x05, 0x28, 0x07},             //503
{0x00, 0x00, 0x00, 0x6B, 0x00, 0x5F},             //504
{0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x04}, //505
{0x56, 0x00, 0x05, 0x00, 0x24, 0x00, 0x64},       //506
{0x1D, 0x00, 0x1D, 0x07, 0x1D, 0x07},             //507
{0x00, 0x00, 0x00, 0x07, 0x00, 0x00},             //508
{0x05, 0xCC, 0x9D, 0x9D, 0x00, 0x07, 0x08, 0x08}, //400 Este deberia ir cambiando x cada celda
{0xCC, 0xCC, 0xCC, 0xD0, 0xD0, 0xCC, 0xD0, 0xD0}, //401
{0x25, 0xFF, 0x56},                               //680
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, //700
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}  //701
}; 

void setup() {
  Serial.begin(9600);
  
  // Start the ethernet connection
  Ethernet.begin(mac, ip);              
  
  // Ethernet takes some time to boot!
  delay(3000);                          
 
  // Set the MQTT server to the server stated above ^
  mqttClient.setServer(server, 1883);   
 
  // Attempt to connect to the server with the ID "myClientID"
  if (mqttClient.connect("myClientID")) 
  {
    Serial.println("Connection has been established, well done");
 
    // Establish the subscribe event
    mqttClient.setCallback(subscribeReceive);
  } 
  else 
  {
    Serial.println("Looks like the server connection failed...");
  }
}

char msgString[87];     //Almacena lo que se imprimirá

byte IdByte[2];
void Imprimir(long int Id, byte len, char Byte[8]){
    IdByte[0]=Id>>8;
    IdByte[1]=Id-(IdByte[1]<<8);
    Serial.print(char(IdByte[0]));
    Serial.print(char(IdByte[1]));
    //Serial.print(char(45));             //**quitar para optimizar**    
    Serial.print(char(len));  
    //Serial.print(char(45));             //**quitar para optimizar**
    
    for(byte i = 0; i<(len); i++){
        Serial.print(char(Byte[i]));
    }
    Serial.println();

   
}


void loop() {
  for(char i = 0; i<(largo); i++){
  Imprimir(ID[i],DLC[i],data[i]);
  //delay(1000);

   // This is needed at the top of the loop!
  mqttClient.loop();
 
  // Ensure that we are subscribed to the topic "MakerIOTopic"
  mqttClient.subscribe("myTopic");
 
  // Attempt to publish a value to the topic "MakerIOTopic"
  if(mqttClient.publish("myTopic", IdByte[i]))
  {
    Serial.println("Publish message success");
  }
  else
  {
    Serial.println("Could not send message :(");
  }
 
  // Dont overload the server!
  delay(1000);

  }
 }
    
  



void subscribeReceive(char* topic, byte* payload, unsigned int length)
{
  // Print the topic
  Serial.print("Topic: ");
  Serial.println(topic);
 
  // Print the message
  Serial.print("Message: ");
  for(int i = 0; i < length; i ++)
  {
    Serial.print(char(payload[i]));
  }
 
  // Print a newline
  Serial.println("");
}
