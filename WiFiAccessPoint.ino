/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/
 // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#include <WiFi.h> //incluir a biblioteca pro wifi
#include <WiFiClient.h> //incluir a biblioteca pro wifi
#include <WiFiAP.h> //incluir a biblioteca pro wifi
#define LEDAZUL1 21 //definir a saida D21 para o ledazul1
#define LEDAZUL2 19 //definir a saida D19 para o ledazul2
#define LEDVERDE1 2 //definir a saida D2 para o ledverde1
#define LEDVERDE2 12 //definir a saida D12 para o ledverde2
#define LEDAMA1 13 //definir a saida D13 para o ledamarelo1
#define LEDAMA2 32 //definir a saida D32 para o ledamarelo2
#define LEDVER1 33 //definir a saida D33 para o ledverde1
#define LEDVER2 25 //definir a saida D25 para o ledverde2
#define LEDBRA1 26 //definir a saida D26 para o ledbranco1
#define LEDBRA2 27 //definir a saida D27 para o ledbranco2
#define LDR 4 //definir a entrada pro sinal LDR
// Set these to your desired credentials.
const char *ssid = "myAP"; //nome do wifi
const char *password = " "; // configuração pra não exigir senha
WiFiServer server(80); //configuração pro wifi

void setup() {
  //nessa parte será definido o que será entrada fisica no ESP32
  pinMode(LDR, INPUT); //LDR como ENTRADA
  pinMode(LEDAZUL1, OUTPUT); //saida pro led
  pinMode(LEDAZUL2, OUTPUT); //saida pro led
  pinMode(LEDAMA1, OUTPUT); //saida pro led
  pinMode(LEDAMA2, OUTPUT); //saida pro led
  pinMode(LEDBRA1, OUTPUT); //saida pro led
  pinMode(LEDBRA2, OUTPUT); //saida pro led
  pinMode(LEDVERDE1, OUTPUT); //saida pro led
  pinMode(LEDVERDE2, OUTPUT); //saida pro led
  pinMode(LEDVER1, OUTPUT); //saida pro led
  pinMode(LEDVER2, OUTPUT);   //saida pro led
  Serial.begin(115200); //velocidade de transferencia em bits por segundo
  Serial.println(); //espaço
  Serial.println("Configurando ponto de acesso..."); 
  WiFi.softAP(ssid, password); //configuração pro wifi
  IPAddress myIP = WiFi.softAPIP(); //configuração pro wifi
  Serial.print("AP IP address: "); //configuração pro wifi
  Serial.println(myIP); //configuração pro wifi
  server.begin(); //inicio do wifi
  Serial.println("Server started");
}

void loop() {
  int ler = analogRead(LDR); //leitura analogica do sinal do LDR
  Serial.print(ler);
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) { //caso a extenção enviada seja H o programa rodará o que estiver nesse "if"        
          int luz = analogRead(LDR);
         if(luz>10){
          digitalWrite(LEDAZUL1, HIGH);
         }
         if(luz>100){
           digitalWrite(LEDAZUL2, HIGH);
         }
          if(luz>200){
           digitalWrite(LEDVERDE1, HIGH);
         }
          if(luz>300){
           digitalWrite(LEDVERDE2, HIGH);
         }
            if(luz>400){
           digitalWrite(LEDAMA1, HIGH);
         }
            if(luz>500){
           digitalWrite(LEDAMA2, HIGH);
         }
            if(luz>600){
           digitalWrite(LEDVER1, HIGH);
         }
            if(luz>700){
           digitalWrite(LEDVER2, HIGH);
         }
            if(luz>800){
           digitalWrite(LEDBRA1, HIGH);
         }
            if(luz>900){
           digitalWrite(LEDBRA2, HIGH);
         }
        }
        if (currentLine.endsWith("GET /L")) { //caso a extenção enviada seja L o programa rodará o que estiver nesse "if"
           digitalWrite(LEDAZUL1, LOW);
           digitalWrite(LEDAZUL2, LOW);
           digitalWrite(LEDVERDE1, LOW);
           digitalWrite(LEDVERDE2, LOW);
           digitalWrite(LEDAMA1, LOW);
           digitalWrite(LEDAMA2, LOW);
           digitalWrite(LEDVER1, LOW);
           digitalWrite(LEDVER2, LOW);
           digitalWrite(LEDBRA1, LOW);
           digitalWrite(LEDBRA2, LOW);          
        }
        if (currentLine.endsWith("GET /K")) { //caso a extenção enviada seja K o programa rodará o que estiver nesse "if"
          
            while(ler<1023){
            digitalWrite(LEDAZUL1, HIGH);              
            delay(250);
            digitalWrite(LEDAZUL2, HIGH); 
            digitalWrite(LEDAZUL1, LOW); 
            delay(250);
            digitalWrite(LEDAZUL2, LOW);
            }
        }
             if (currentLine.endsWith("GET /k")) { //caso a extenção enviada seja K o programa rodará o que estiver nesse "if"
           digitalWrite(LEDAZUL1, HIGH);
           digitalWrite(LEDAZUL2, HIGH);
           digitalWrite(LEDVERDE1, HIGH);
           digitalWrite(LEDVERDE2, HIGH);
           digitalWrite(LEDAMA1, HIGH);
           digitalWrite(LEDAMA2, HIGH);
           digitalWrite(LEDVER1, HIGH);
           digitalWrite(LEDVER2, HIGH);
           digitalWrite(LEDBRA1, HIGH);
           digitalWrite(LEDBRA2, HIGH); 
        }
      }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
 }