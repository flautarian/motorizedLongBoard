// RECEPTOR (Chip grande)
#include <VirtualWire.h>
char *velocity = "";
//Creamos un mensaje
//La constante VW_MAX_MESSAGE_LEN viene definida en la libreria
byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;
int noReceptionCounter =0;
const int receive_pin = 11, lento = 2, rapido = 3;
const char *lentoVal = "1", *rapidoVal = "2", *stopVal = "0";
void setup()
{
 Serial.begin(9600); //Iniciamos la comunicacion serial
  pinMode(13, OUTPUT); //Configuramos el pin 13 como salida
  pinMode(lento, OUTPUT); //Configuramos el pin 13 como salida
  pinMode(rapido, OUTPUT); //Configuramos el pin 13 como salida
  vw_set_rx_pin(receive_pin);
  vw_setup(2000);
  vw_rx_start();
  digitalWrite(lento,HIGH);// Apagamos lento
  digitalWrite(rapido,HIGH);// Apagamos rapido
}
void loop()
{
 if (vw_get_message(message, &messageLength))
 {
     if(comparar(stopVal) == 0){
        digitalWrite(13,LOW);// Apagamos led
        digitalWrite(lento,HIGH);// Apagamos lento
        digitalWrite(rapido,HIGH);// Apagamos rapido
        Serial.println("STOP");  
     }
     else if(comparar(lentoVal) == 0)
     {
        digitalWrite(13,HIGH);// Apagamos led
        digitalWrite(lento,LOW);// Encendemos lento
        digitalWrite(rapido,HIGH);// Apagamos rapido
        Serial.println("LENTO");  
     }
     else if(comparar(rapidoVal) == 0){
        digitalWrite(13,HIGH);// Apagamos led
        digitalWrite(lento,HIGH);// Apagamos lento
        digitalWrite(rapido,LOW);// Encendemos rapido
        Serial.println("RAPIDO");  
     }
     else{
        digitalWrite(13,LOW);// Apagamos led
        digitalWrite(lento,HIGH);// Apagamos lento
        digitalWrite(rapido,HIGH);// Apagamos rapido
        Serial.println("MALA SEÑAL (CASO IMPOSIBLE CONTROLADO)");  
     }
     noReceptionCounter =0;
 }
 else {
  Serial.println("no recibo señal");  
  if(noReceptionCounter >= 5){
    digitalWrite(13,LOW);// Apagamos led
        digitalWrite(lento,HIGH);// Apagamos lento
        digitalWrite(rapido,HIGH);// Apagamos rapido
        Serial.println("EMISOR APAGADO");
  }
  else noReceptionCounter++;
 }
 
 delay(150); //Pausa de 0.15 segundos 
}

char comparar(char* cadena) {
 //Esta funcion compara el string cadena con el mensaje recibido.
 //Si son iguales, devuelve 1. Si no, devuelve 0.
 for(int i = 0; i<messageLength; i++)
 {
   if(message[i] != cadena[i])
   {
     return 1;
   }
 }
   return 0;
}
