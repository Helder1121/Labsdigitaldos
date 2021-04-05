//Electronica Digital
//Laboratorio 5
//Helder Ovalle ;18349
//Seccion:20

//Librerias a utilizar
#include <SPI.h>
#include <SD.h>
File root;
File myFile;
//Variable para las variantes de las imagenes 
int imag = 0;
void setup(){
  // Open serial communications and wait for port to open:
  Serial.begin(115200);//Baudios a utilizar 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  SPI.setModule(0);//Configuracion para la inicializacion del SPI
  Serial.print("Initializing SD card...");//Inciando la SD
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);//PA_3CS

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");//Conexion fallida
    return;
  }
  Serial.println("initialization done.");//Conexion exitosa
  root = SD.open("/");//Abre los archivos 
  printDirectory(root, 0);//Muestra los archivos (imaganes)
}

void loop(){
if (Serial.available()>0){//Valor rque se ingresara en la ventana 
  imag = Serial.read();//Variable a leer
  //Primera imagen
  if (imag == '1'){
    myFile = SD.open("darkB.txt");//Nombre del archivo .txt
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");//Mensaje de error
    }
  }
}
  //Segunda imagen
  if (imag == '2'){
    myFile = SD.open("mario.txt"); //Nombre del archivo .txt
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");//Mensaje de error
    }
  }
  //Tercera imagen
  if (imag == '3'){
    myFile = SD.open("wason.txt"); //Nombre del archivo .txt
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");//Mensaje de error
    }
  }
}
//La funcion para enseñar los archivos SD
void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
