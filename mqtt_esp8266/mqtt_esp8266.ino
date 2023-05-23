#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "MMK";
const char* password = "onepiece";
const char* mqtt_server = "91.121.93.94";//broker.mqtt-dashboard.com

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(120)
// char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(D2, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(D2, LOW);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("device/zoro", "connected to server");
      // ... and resubscribe
      client.subscribe("device/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(D2, OUTPUT);  
  pinMode(A0, INPUT);     // Initialize the BUILTIN_LED pin as an output
     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
}
char m1[MSG_BUFFER_SIZE];
char m2[MSG_BUFFER_SIZE];

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Serial.print(Serial.read());
  unsigned long now = millis();
    if (Serial.available()>0) {
    Serial.readBytesUntil('?',m1,120);


    }
  String msg=String(m1);
  if (now - lastMsg > 1000) {

    lastMsg = now;
    value=analogRead(A0);
    // snprintf (msg, MSG_BUFFER_SIZE, "The output is :%ld", value);
    // Serial.print("Publish message: ");
    // Serial.println(msg);
    // msg=string(Serial.read());
    // snprintf (msg, MSG_BUFFER_SIZE, "Arduino output is :%ld", Serial.read());
    // Serial.print("Publish message: ");
    // Serial.println(msg);
    client.publish("device/zoro", (char*) msg.c_str());

    // else{
    // client.publish("device/temp", msg);
    // }
  }
}

