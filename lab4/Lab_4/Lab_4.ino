//Electronica Digital
//Laboratorio 4
//Helder Ovalle ;18349
//Seccion:20

//Pines del jugador 1
int led1 = PB_0;
int led2 = PB_1;
int led3 = PB_2;
int led4 = PB_3;
int led5 = PB_4;
int led6 = PB_5;
int led7 = PB_6;
int led8 = PB_7;
//Pines del jugador 2
int led9 = PA_5;
int led10 = PD_7;
int led11 = PD_2;
int led12 = PD_3;
int led13 = PC_4;
int led14 = PC_5;
int led15 = PC_6;
int led16 = PC_7;
//Pines del semaforo
int ledR = RED_LED;
int ledG = GREEN_LED;
int ledB = BLUE_LED;
//Indicadores de ganador (azules)
int led17 = PA_6;
int led18 = PA_7;

//Variables
int avanzar = PUSH1; 
int avanzar2 = PUSH2; 
//Puertos de la tiva push1 y push2 
int presionado = 0;
int presionado2 = 0; 
//variable para antirebote 
int cont = 0;
int cont2 = 0;
//Variables de cont1 y cont2

//Funciones a llamar 
void jugador1(void);
void jugador2(void);
void semaforo(void);
void ganador(void);

void setup() {
//Leds de ambos jugadores
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(led6, OUTPUT);
pinMode(led7, OUTPUT);
pinMode(led8, OUTPUT);
pinMode(led9, OUTPUT);
pinMode(led10, OUTPUT);
pinMode(led11, OUTPUT);
pinMode(led12, OUTPUT);
pinMode(led13, OUTPUT);
pinMode(led14, OUTPUT);
pinMode(led15, OUTPUT);
pinMode(led16, OUTPUT);
//Semaforo
pinMode(ledR, OUTPUT);
pinMode(ledG, OUTPUT);
pinMode(ledB, OUTPUT);
//Indicador del ganador
pinMode(led17, OUTPUT);
pinMode(led18, OUTPUT);
//Push
pinMode(avanzar, OUTPUT);
pinMode(avanzar2, OUTPUT);

semaforo();
}

void loop(){
jugador1();
jugador2();
ganador();
}  
//Funciones 
void jugador1(void){
  //Aumentando el conta
if (digitalRead(avanzar) == LOW){
  presionado = 1; //Cambiara el estado del push1
}
if (digitalRead(avanzar) == HIGH && presionado1 == 1){
  presionado = 0;//se reinicia la variable del antirrebote
  delay(100);
  cont++;//Incrementa el contador
}

    
void semaforo(void){
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  delay(1000);
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  delay(1000);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  delay(1000);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}
void ganador(void);
if (contador>8){
  digitalWrite(led17, HIGH);
  digitalWrite(led8, LOW);
}
if (contador2>8){
  digitalWrite(led18, HIGH);
  digitalWrite(led16, LOW); 
}
}
