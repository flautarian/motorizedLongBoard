// EMISOR (Chip pequeño)
#include <VirtualWire.h> //incluimos la libreria virtualwire

const int transmit_pin = 12, lento = 2, rapido = 3;
int lentoVal =0, rapidoVal = 0;
char *velocity = "";
void setup()
{
 
 Serial.begin(9600); //Iniciamos la comunicacion serial
 
 vw_set_tx_pin(transmit_pin);
 
 vw_setup(2000);  //Iniciamos la comunicacion con el modulo RF

 pinMode(13, OUTPUT);    //Configuramos el pin del Led como salida
 pinMode(lento, INPUT_PULLUP);
 pinMode(rapido, INPUT_PULLUP);

}


void loop()
{

 //Enviamos "a"
lentoVal = digitalRead(lento);
rapidoVal = digitalRead(rapido);
if(lentoVal == 1 && rapidoVal ==1){
  digitalWrite (13,LOW);
  Serial.println("STOP");  
  velocity = "0";
}
else if(lentoVal == 1){
  digitalWrite (13,HIGH);
  Serial.println("lento");  
  velocity = "1";
}
else if(rapidoVal == 1){
  digitalWrite (13,HIGH);
  Serial.println("rapido");  
  velocity = "2";
}
else{
  //caso imposible pero cubierto con STOP
  velocity = "0";
}
send(velocity);
delay(150);  //Pausa 0.5 segundos
} 

 

//Funcion para enviar el mensaje por RF

void send (char *message)
{
 vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
 vw_wait_tx(); //Espera hasta que se envien los datos
}
