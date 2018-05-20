#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE);


  #if defined(ESP8266)
  #include <pgmspace.h>
  #else
  #include <avr/pgmspace.h>
  #endif
  #include <Wire.h>
  
  #define Lampara D3
  #define BOMBA D4
  #define Oxigenador D5 
  
  #include <RtcDS3231.h>
  RtcDS3231<TwoWire> Rtc(Wire);
  RtcDateTime now; 


  
//****************************************************DHT config*******************************
#include "DHT.h"                                                                            //*
#define DHTPIN D6   //13 del proyecto // Pin donde está conectado el sensor                   *
#define DHTTYPE DHT22   // Sensor DHT22                                                       *
DHT dht(DHTPIN, DHTTYPE);                                                                   //*
//*********************************************************************************************
  
  char contador = 0; //timer para sensar botones
  int contador2 = 0; //timer para sensart TEMP y HUMI
  int minuto = 0;
  unsigned long tiempo_anterior = 0;
  int8_t m = 0; //mantenido y mantener pulsado
  int8_t testear_boton = 0;
  byte mp = 0;
  byte hou = 0, minute = 0, second = 0;
  
  
  
  char variable_display[32];
  char reloj = 0; //timer para reloj
  char horasdeluzf = 0, minutosdeluzf = 0, horasdeluzv = 0, minutosdeluzv = 0;
  char fov;
  byte horasdeluz,  horasencendido;
  unsigned int  minutosDeLuz=0, minutosEncendido=0;
  unsigned int  minutosApagar = 0;
  boolean poa = 0, configuradov = 0, configuradof = 0, apagaralotrodia = 0;
  byte modo = 0;
  String nombrePerfil="";

  struct timer{
  unsigned int intervaloDia = 135;
  unsigned int tiempoPrendidoDia=5;
  unsigned int offsetEncenderDia =100;
  unsigned int offsetApagarDia= 54;
  unsigned int disparosDia;
  //------------------------------------
  unsigned int intervaloNoche;
  unsigned int tiempoPrendidoNoche;
  unsigned int offsetEncenderNoche;
  unsigned int offsetApagarNoche;
  unsigned int minutosApagar;
} bomba1,oxigenador;  
  
  bool flag = 0;

  
  byte hmaxv = 0, hminv = 0, hmaxf = 0, hminf = 0;
  byte tmaxv = 0, tminv = 0, tmaxf = 0, tminf = 0;

  byte diadeinicio, mesdeinicio;
  int anodeinicio;

  long iniciodecultivo=0,diarestar=0, diastotales=0;

  float h; //variable humedad
  float t;  //variable temperatura
  char temperature[5];
  char humidity[5];
  byte vart;
  
  byte tempmax = 24;  //temperatura maxima
  byte tempmin = 20;  //temperatura minima
  byte humedadmin = 30;  //humedad minima
  byte humedadmax = 60;  //humedad maxima
  byte numpromedio = 0;
  float htotal = 0.0;
  float ttotal = 0.0; 
  
  const int extr = D7; //Extractor pine 6
  const int intr = D8; //Intractor pine 5
  
  static enum 
  {
    defecto = 0,
    tmax_hmax = 9,
    tmax_hok = 10,
    tmax_hmin = 12,
    tok_hmax = 17,
    tok_hok = 18,
    tok_hmin = 20,
    tmin_hmax = 33,
    tmin_hok = 34,
    tmin_hmin = 36
  } estado = defecto;

char idcaill [40] = "";
char INSERT_DATA[] = "INSERT INTO CAILL.datos (temperature,humedity) VALUES (%s,%s)";
const char QUERY_POP[] = "SELECT * FROM caill.CAILLlist WHERE idCAILL = %s";
char query[128];

//------------------------------------------------------posociones de memoria eeprom-------------------------------
#include <EEPROM.h>                                                                                              //
byte minutosDeLuzFPos = 0;                                                                                       //   
byte minutosDeLuzVPos = 2;                                                                                       //
byte minutosEncendidoPos = 100;                                                                                  //
byte poaPos = 6;                                                                                                 //
byte modoPos = 7;                                                                                                //
byte tempMaxFPos = 8;                                                                                            //
byte tempMinFPos = 9;                                                                                            //          
byte humedadMaxFPos = 10;                                                                                        //
byte humedadMinFPos = 11;                                                                                        //
byte tempMaxVPos = 12;//10
byte tempMinVPos = 13;
byte humedadMaxVPos = 14; //14
byte humedadMinVPos = 15; //12
byte disparosDiaB1Pos = 16;
byte tiempoPrendidoDiaB1Pos = 17;
bool postIDPos = 255;

uint8_t numero = 1;
byte ptrdisplay =3;  
char ls = 0, li = 0;

  void setup() {
    pinMode(Lampara, OUTPUT);
    pinMode(BOMBA, OUTPUT);
    pinMode(Oxigenador, OUTPUT);
    delay(1000);
    bomba1.disparosDia=5; //predefinir un valor o cargar junto con el perfil
    u8g2.begin();
    analogWrite(extr,800); // 100
    analogWrite(intr,0);    // 0
    
    tiempo_anterior = millis();
  
    Serial.begin(115200);
  
    Rtc.Begin();

    EEPROM.begin(512);
    poa = EEPROM.read(poaPos);
    modo = EEPROM.read(modoPos);   

    long four = EEPROM.read(15);
    long three = EEPROM.read(16);
    long two = EEPROM.read(17);
    long one = EEPROM.read(18);
    iniciodecultivo = ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);

    dht.begin();
    pinMode(extr,OUTPUT);  //Declarar el pin del Extractor 1 como salida
    pinMode(intr,OUTPUT);   //Declarar el pin del Extractor 2 como salid a   
    
    Serial.println(idcaill);
    now = Rtc.GetDateTime();  //get the time from the RTC
    EEPROM.get(minutosEncendidoPos,minutosEncendido);
    delay(1000);

  }
  
  void loop()
  {    
    while(true) {
    digitalWrite(Lampara,LOW);
    digitalWrite(BOMBA,LOW);
    digitalWrite(Oxigenador,LOW);
    Serial.println("si2"); 
    delay(5000);
    Serial.println("si3"); 
    digitalWrite(Lampara,HIGH);
    digitalWrite(BOMBA,HIGH);
    digitalWrite(Oxigenador,HIGH);
    delay(5000);
    }
    li=0;
    ls=4;
    testear_botones();
    ptrdisplay=numero;
    if (mp == 4)
    {
      menu();
      numero = 1;
    }
  
    if (reloj >= 2)
    {          
      now = Rtc.GetDateTime();  //get the time from the RTC       
      reloj = 0 ;
      char str[15] = "";   //declare a string as an array of chars
      Serial.println("si2"); 
      Serial.println(ptrdisplay); 
      switch (ptrdisplay)
      {    
        default :
        {
        ptrdisplay=1;  
        }
        case 1: //temp y h
        {              
          u8g2.setFont(u8g2_font_ncenB14_tr);   
          u8g2.clearBuffer();
          sprintf(str, "T= %sº",
            temperature
            );
          u8g2.drawStr( 5, 16,str);   
          sprintf(str, "H= %s",
            humidity
            );  
          u8g2.drawStr( 5, 34,str);   
          if (modo=1)
          {  
            u8g2.drawStr( 2, 50, "VEGETACION"); 
          }
          else
          {           
            u8g2.drawStr( 2, 50,"FLORACION");  
          } 
          u8g2.sendBuffer();
          break;
        }
        case 2://hora
        { 
          u8g2.setFont(u8g2_font_ncenB14_tr);   
          u8g2.clearBuffer(); 
          //printear 
          sprintf(str, "%02d:%02d:%02d",     //%d allows to print an integer to the string
              now.Hour(),
              now.Minute(),
              now.Second()  //get second method              
             );           
          u8g2.drawStr( 20, 25,str);
          sprintf(str, "%02d/%02d/%02d",     //%d allows to print an integer to the string
              now.Day(),
              now.Month(),
              now.Year()
              //get second method
             );
          diarestar = ConvierteFechaEnNumero( now.Year(),now.Month(),now.Day());
          diastotales = diarestar - iniciodecultivo;   
          u8g2.drawStr( 10,40,str); 
          sprintf(str, "%02d dias de cultivo",   //%d allows to print an integer to the string
             diastotales
             );
          u8g2.drawStr( 10, 55,str);   
          u8g2.sendBuffer();  
          break; 
        }
        case 3: //config
        {
          u8g2.setFont(u8g2_font_t0_17b_mf);   
          u8g2.clearBuffer(); 
          //printear     
          sprintf(str, "Hs encender\n %02d:%02d",     //%d allows to print an integer to the string
              minutosEncendido/60,
              minutosEncendido%60          
             );           
          u8g2.drawStr( 5, 15,str);
          sprintf(str, "Hs de luz\n %02d/%02d",     //%d allows to print an integer to the string
              minutosDeLuz/60,
              minutosDeLuz%60
             );          
          u8g2.drawStr( 10, 40,str);    
          u8g2.sendBuffer();  
          break;     
        }
      }        
      if (modo == 2) // Floración
      {
        Serial.print("FLORA");
        if (configuradof == 0)
        {
          configurarBomba1(); 
          EEPROM.get (minutosDeLuzFPos,minutosDeLuz);
          tempmax = EEPROM.read(tempMaxFPos); //9
          tempmin = EEPROM.read(tempMinFPos);//7
          humedadmax = EEPROM.read(humedadMaxFPos);//13
          humedadmin = EEPROM.read(humedadMinFPos);//11
          apagaralotrodia = 0;          
          minutosApagar = minutosEncendido + minutosDeLuz;
          Serial.println("config" );
          Serial.println(minutosApagar );
          
          if (minutosApagar >= 23*60+59)
          {
            minutosApagar = minutosApagar - 23*60-59;
            apagaralotrodia = 1;
          }
          
          configuradof = 1;            
        }
  
      }
      else
      {
        Serial.print("VEGE");
        if (configuradov == 0) //configuracion y calvulos de la etapa vegetativa
        {
          EEPROM.get(minutosDeLuzVPos,minutosDeLuz);       
          tempmax = EEPROM.read(tempMaxVPos);//10
          tempmin = EEPROM.read(tempMinVPos);//8
          humedadmax = EEPROM.read(humedadMaxVPos);//14
          humedadmin = EEPROM.read(humedadMinVPos); //12
          configurarBomba1();
          Serial.println("si5"); 
          apagaralotrodia = 0;
          minutosApagar = minutosEncendido + minutosDeLuz;
          Serial.println("config" );
          Serial.println(minutosApagar );
          if (minutosApagar >= 24*60)
          {
            minutosApagar = minutosApagar - 24*60;
            apagaralotrodia = 1;
          }
          configuradov = 1;
        }
  
      }
  
      sprintf(str, "%02d : %02d",     //%d allows to print an integer to the string
              horasdeluz,
              minutosDeLuz
              //get second method
             );
      //u8g2.drawStr(str, 4, 1);

      unsigned int minutosParciales = now.Hour()*60+now.Minute();
      verificar_timers(minutosParciales);     
      Serial.print("minutos parciales:"); 
      Serial.println(minutosParciales); 
      Serial.print("minutos encendido:"); 
      Serial.println(minutosEncendido);
      Serial.print("minutos de luz v");
      Serial.println(minutosDeLuz);
      Serial.print("minutos apagar:"); 
      Serial.println(minutosApagar);  
      if (apagaralotrodia == 1) //manera en que la lampara identifica su estado, si su momento de apagar esta al otro dia del momento de prender
      {        
        if(minutosParciales>=minutosEncendido || minutosParciales <=minutosApagar )
          {
            digitalWrite(Lampara, HIGH);
            poa = 1;
          }
        else
          {
          digitalWrite(Lampara, LOW);
          poa = 0;   
          }
        
      }
      else
      {
        if((minutosParciales >= minutosEncendido) && (minutosParciales <minutosApagar))
          {
            digitalWrite(Lampara, HIGH);
            poa = 1;
          }
        else
          {
            digitalWrite(Lampara, LOW);
            poa = 0;  
          }
      }
      EEPROM.write(poaPos , poa);
      EEPROM.commit();
    }
    // temperaturaaaaaaa y humedaaaaaad
    if(contador2 >= 20)
    {
      contador2 = 0;
      h = dht.readHumidity(); //Leemos la Humedad
      t = dht.readTemperature(); //Leemos la temperatura en celisius
      if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
      }
      numpromedio++;
      htotal = h + htotal;
      ttotal = t + ttotal;
      //Serial.print("Humedad ");
      //Serial.println(h);
      //Serial.print("Tempe ");
      //Serial.println(t);
      if(numpromedio == 10)
      {
          t = 0.0;
          h = 0.0;
          numpromedio=0;
          t = ttotal / 10;
          h = htotal /10;
          ttotal=0;
          htotal=0;
          Serial.print("Humedad final ");
          Serial.print(h);
          Serial.print("  ");
          Serial.print("Tempe final");
          Serial.println(t);
          dtostrf(t, 2, 1, temperature);
          dtostrf(h, 2, 1, humidity);
          vart = 0;
          
          if( t < tempmin )//Temperatura menores a lo seteado
          {
            vart |= 32;
          } else if( (tempmin < t) && (t < tempmax) ) //Temperatura correcta
            {
              vart |= 16;
            } else {  //humedad son mayores a lo setiado
              vart |= 8;
            }
            
          
          if(h<humedadmin)//Humedad menores a lo setiado
          {
            vart |= 4;
          } else if (h>humedadmin && h<humedadmax)//Humedad correcta
            {
               vart |= 2;
            } else //humedad son mayores a lo setiado
              {
                vart |= 1;
              }
          Serial.print(vart);
          switch (vart)
            {
             case tmax_hmax:
             {
              analogWrite(extr,1024); // 100
              analogWrite(intr,0);    // 0
             }
             break;
              
             case tmax_hok:
             {
                analogWrite(extr,1024); //100
                analogWrite(intr,307);  //30
             }
             break;
              
             case tmax_hmin:
             {
                analogWrite(extr,768); //75
                analogWrite(intr,819); //80
             }
             break;
              
             case tok_hmax:
             {
                analogWrite(extr,307);  //30
                analogWrite(intr,0);    //0
             }
             break;
              
             case tok_hok:
             {
                analogWrite(extr,307);  //0
                analogWrite(intr,307);  //0 
             }
             break;
              
             case tok_hmin:
             {
                analogWrite(extr,307);  //30
                analogWrite(intr,1024); //100  
             }
             break;
              
             case tmin_hmax:
             {
                analogWrite(extr,512); //0
                analogWrite(intr,0); //0     
             }
             break;
              
             case tmin_hok:
             {
                analogWrite(extr,307); //0
                analogWrite(intr,0); //0     
             }
             break;
              
             case tmin_hmin:
             {
                analogWrite(extr,307); //0
                analogWrite(intr,307); //0     
             }
             break;    
            }
            if( WiFiIsConected ()) 
            {
              if (connectionOpen()) 
              {
                delay(1000);
                Serial.print("conect2");                 
                strcpy (INSERT_DATA,"INSERT INTO caill_db.main_sample (temperature, humedity, id, date) values ('%s','%s','%s','%02d','%02d','%02d','%02d','%02d','%02d')");
                Serial.print(INSERT_DATA);
                sprintf(query, INSERT_DATA,temperature,humidity,idcaill,now.Year(),now.Month(),now.Day(),now.Hour(),now.Minute(),now.Second());
                insertData();
                const char QUERY_POP[] = "SELECT * FROM caill_db. WHERE id = %s";
                select();
                connectionClose();
                SetAll();  
              }
              else
              {
                Serial.println("Connection failed.");  
                //**************************************Mensaje de error*******************
              }            
           }
    } 
   }
  }


