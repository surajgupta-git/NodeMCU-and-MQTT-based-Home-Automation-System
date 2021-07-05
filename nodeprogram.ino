#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.
const char* ssid = "linksys";
const char* password = "9052345605";
const char* mqtt_server = "m23.cloudmqtt.com";
const char* mqttUser="froismwo";
const char* mqttPass="arzUtf1RHPMu";
int var1=0;
int var2=0;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
void setup_wifi() {
delay(10);
// We start by connecting to a WiFi network
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
randomSeed(micros());
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
if(strcmp(topic,"BULB")==0)
{
for (int i = 0; i < length; i++) {
Serial.print((char)payload[i]);
}
Serial.println();
// Switch on the LED if an 1 was received as first character
if ((char)payload[0] == '1') {
digitalWrite(D3, LOW);
client.publish("checkBULB","BULB IS ON IN HOUSE");
// Turn the LED on (Note that LOW is the voltage level but actually the LED is
on; this is because it is acive low on the ESP-01)
} else {
digitalWrite(D3, HIGH);
client.publish("checkBULB","BULB IS OFF IN HOUSE"); // Turn the LED off
by making the voltage HIGH
} }
if(strcmp(topic,"FAN") == 0)
{ for (int i = 0; i < length; i++) {
Serial.print((char)payload[i]);
}
// Switch on the LED if an 1 was received as first character
if ((char)payload[0] == '0') {
analogWrite(D1 , 0);
digitalWrite(D2 , LOW);
client.publish("checkFan","Fan is OFF");
} else if((char)payload[0] == '1') {
analogWrite(D1,204);
digitalWrite(D2,LOW);
client.publish("checkFan","Fan is ON and speed is 1"); // Turn the LED off by
making the voltage HIGH
}
else if((char)payload[0] == '2') {
digitalWrite(D2,LOW);
analogWrite(D1, 408);
client.publish("checkFan","Fan is ON and speed is 2");// Turn the LED off by
making the voltage HIGH
}
else if((char)payload[0] == '3') {
analogWrite(D1, 612);
digitalWrite(D2,LOW);
client.publish("checkFan","Fan is ON and speed is 3");// Turn the LED off by
making the voltage HIGH
}
else if((char)payload[0] == '4') {
analogWrite(D1,816);
digitalWrite(D2,LOW);
client.publish("checkFan","Fan is ON and speed is 4");// Turn the LED off by
making the voltage HIGH
}
else if((char)payload[0] == '5') {
analogWrite(D1, 1023 );
digitalWrite(D2, LOW);
client.publish("checkFan","Fan is ON and speed is 5");// Turn the LED off by
making the voltage HIGH
} } }
void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
// Create a random client ID
String clientId = "ESP8266Client-";
clientId += String(random(0xffff), HEX);
// Attempt to connect
if (client.connect(clientId.c_str(),mqttUser,mqttPass)) {
Serial.println("connected");
// Once connected, publish an announcement and resubscribe
client.subscribe("BULB");
Serial.println("subs");
client.subscribe("FAN");
} else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 5 seconds");
// Wait 5 seconds before retrying
delay(5000);
} } }
void setup() {
pinMode(D3, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
digitalWrite(D3, HIGH);
digitalWrite(D2, LOW);
digitalWrite(D0, HIGH);
// Initialize the D3 pin as an output
Serial.begin(115200);
setup_wifi();
client.setServer(mqtt_server,18771);
client.setCallback(callback);
}
void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();
long now = millis();
if (now - lastMsg > 50000) {
lastMsg = now;
snprintf (msg, 75, "Server OK ");
Serial.print("Publish message: ");
Serial.println(msg);
client.publish("checkServer", msg);
var1=digitalRead(D0);
 }
}