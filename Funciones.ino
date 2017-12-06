  
  char posiciondemenu = 0; //
  
  int8_t a = 0;
  bool flagprint = 0;
  char sw = 0, sw1 = 0; //,sw1=0; //crear variable local para salir dl while
  
  byte dia, mes, anio;
  
  bool confirmacion;
  byte derecha = 0, enter = 0, s = 0, izquierda = 0;

#define u8g_logo_width 128
#define u8g_logo_height 64

static const unsigned char u8g2_logo_bits[] U8X8_PROGMEM =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x0C, 0x00, 0x00, 0x00, 0x70, 0x18, 0x14, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1C, 0x0C, 0x00, 0x00, 0x00, 0x78, 0x38, 0x34, 0x20, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x0E, 0x00, 0x00, 0x00, 
  0x58, 0x38, 0x34, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 
  0x0E, 0x10, 0x01, 0x00, 0x0C, 0x3C, 0x3E, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x6C, 0xCE, 0xB3, 0x1B, 0x01, 0x0C, 0x6C, 0x34, 0x60, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0xCB, 0xF6, 0x9E, 0x01, 
  0x0C, 0x6C, 0x36, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 
  0x5B, 0xF7, 0x9E, 0x01, 0x06, 0xCC, 0x34, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xCC, 0xD9, 0x73, 0x9E, 0x01, 0x06, 0xE6, 0x3F, 0x60, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xF9, 0x78, 0x9E, 0x01, 
  0x86, 0xFF, 0x3D, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0xD8, 0x78, 0x9C, 0x01, 0x86, 0x9F, 0x35, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0xD8, 0x7C, 0x9C, 0x01, 0xC6, 0x82, 0x35, 0x7C, 
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xD8, 0x3C, 0xFE, 0x01, 
  0x7E, 0x83, 0xFD, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
  0x98, 0x37, 0x74, 0x03, 0x3C, 0x03, 0xFF, 0xE1, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x04, 0x01, 0x00, 0x02, 0x01, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0x00, 
  0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xE0, 0x30, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x06, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xC0, 0x00, 0x00, 
  0x00, 0x00, 0x06, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x18, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0C, 0x80, 0x01, 0x00, 0x00, 0x00, 0x01, 0x10, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x01, 0x00, 
  0x00, 0x80, 0x01, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x03, 0x00, 0x00, 0x80, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x03, 0x00, 0x00, 0xC0, 0x00, 0x60, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x00, 
  0x00, 0xC0, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x57, 0x6A, 0x06, 0x00, 0x00, 0xC0, 0xAA, 0xEA, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x07, 0x00, 0x00, 0xE0, 0xFF, 0x7F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x4B, 0x07, 0x00, 
  0x00, 0x40, 0x55, 0xF5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x02, 0x06, 0x00, 0x00, 0x40, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x06, 0x00, 0x00, 0x60, 0x00, 0x5F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x06, 0x00, 
  0x00, 0x60, 0x00, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x0C, 0x06, 0x00, 0x00, 0xC0, 0x07, 0xC3, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x1E, 0x06, 0x00, 0x00, 0x40, 0x8C, 0xC7, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE2, 0x7F, 0x02, 0x00, 
  0x00, 0x40, 0xFC, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x26, 0x7E, 0x02, 0x00, 0x00, 0xC0, 0x80, 0x43, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3E, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x00, 0x65, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x03, 0x00, 
  0x00, 0x80, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x03, 0x00, 0x00, 0x80, 0x01, 0x34, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFD, 0x3F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x80, 0x01, 0x00, 
  0x00, 0x00, 0x07, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x06, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0xF8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, };
  
  void menu(void)  //menu de configuracion CAILL
  {
    char posiciondemenu = 0; //
    u8g2.setFont(u8g2_font_6x10_tf);
    noInterrupts();
    enter = 0;
    mp = 0;
    u8g2.clearDisplay()  ; 
    u8g2.clearBuffer();
    u8g2.drawStr( 5, 4,"MENU CAILL");
    u8g2.sendBuffer();
    Serial.println("ClearLCD()");
    Serial.println("Menu CAILL");
    contador = 0;
    interrupts();

    u8g2.clearBuffer();
    u8g2.drawXBM( 0, 0, u8g_logo_width, u8g_logo_height, u8g2_logo_bits);
    u8g2.sendBuffer();
    while (contador <= 3)
    {
      revisar_timer();
      yield();
    }
    contador=0;
    u8g2.clearDisplay() ;
    Serial.println("ClearLCD()");
    posiciondemenu = 1;
    numero = 0;
    enter = 0;
    const char menuList[] = 
      "\tConectar a WiFi\n"  //1
      "\tEtapa\n"            //2
      "\tFecha\n"            //3
      "\tHora\n"             //4
      "\tHora de encendido\n"//5
      "\tHoras de luz ☼\n"  //6
      "\tInicio del cultivo\n"//7          
      "\tRiego\n"             //8
      "\tTemperatura y Humedad\n"//9
      "\tSALIR";              //10

    const char menuListStage[] = 
      "\tVegetación\n"
      "\tFloración\n"
      "\tSALIR";
    
    const char menuListIrrigation[] = 
      "\tDiurnos\n"
      "\tNocturno\n"
      "\tSALIR";       
    const char *menuListPtr = menuList;

    //const char riegos = "Riegos"
    //const char *title; 
    posiciondemenu =u8g2.userInterfaceSelectionList("Menu CAILL", posiciondemenu, menuListPtr);
    u8g2.clearDisplay();
    Serial.print("posicion de menu=");
    Serial.println(posiciondemenu);
    Serial.println("ClearLCD();");
    byte stage = 1;
    delay(500);
    switch(posiciondemenu)
    {     
      case 1:
      {
        AP_on();
        u8g2.clearDisplay();  
        break;
      }
      case 2:
      {
        menuListPtr = menuListStage;
        stage=u8g2.userInterfaceSelectionList("Valores para", stage, menuListPtr);
        modo=stage;
        EEPROM.write(modoPos,modo);
        break;
      }
      case 3:
      {
        numero = 0;
          flagprint = 1;
          sw = 0;
          while (sw == 0)
          {
            yield();
            ls = 32;
            li = -1;
            testear_botones();
            dia = numero;
            if (flagprint = 1)
            {             
              flagprint = 0;
              u8g2.setFont(u8g2_font_helvB18_tf);
              u8g2.clearBuffer();
              u8g2.drawStr( 26, 27,"Dia:");
              sprintf(variable_display, "%02d/00/2000", dia);
              u8g2.setFont(u8g2_font_t0_22b_tn);
              u8g2.drawStr( 1, 55,variable_display);
              u8g2.sendBuffer();
            }
            if (enter == 1)
            {
              enter = 0;
              sw = 1;
            }
          }
          sw = 0;
          numero = 0;
  
          while (sw == 0)
          {
            revisar_timer();
            yield();
            ls = 13;
            li = -1;
            testear_botones();
            mes = numero;
            if (flagprint = 1)
            {
              flagprint = 0;
              u8g2.setFont(u8g2_font_helvB18_tf);
              u8g2.clearBuffer();
              u8g2.drawStr( 26, 27,"Mes:");
              sprintf(variable_display, "%02d/%02d/2000", dia, mes);
              u8g2.setFont(u8g2_font_t0_22b_tn);
              u8g2.drawStr( 5, 55,variable_display);
              u8g2.sendBuffer(); 
            }
            if (enter == 1)
            {
  
              enter = 0;
              sw = 1;
              numero = 0;
            }
          }
          sw = 0;
          numero = 0;
  
          while (sw == 0)
          {
            revisar_timer();
            yield();
            ls = 99;
            li = -1;
            testear_botones();
            anio = numero;
            if (flagprint = 1)
            {
              flagprint = 0;
              u8g2.setFont(u8g2_font_helvB18_tf);
              u8g2.clearBuffer();
              u8g2.drawStr( 26, 27,"Año:");
              sprintf(variable_display, "%02d/%02d/20%02d", dia, mes, anio);
              u8g2.setFont(u8g2_font_t0_22b_tn);
              u8g2.drawStr( 1, 55,variable_display);
              u8g2.sendBuffer();
            }
            if (enter == 1)
            {
              enter = 0;
              sw = 1;
              numero = 0;
            }
          }
          sw = 0;
          u8g2.clearDisplay();
          RtcDateTime now = Rtc.GetDateTime();    //get the time from the RTC
          byte hou = now.Hour();
          byte minute = now.Minute();
          byte sec = now.Second();
          RtcDateTime compiled = RtcDateTime(anio , mes, dia, hou, minute, sec);
          Rtc.SetDateTime(compiled);
        break;
      }
      case 4 :
      {
        unsigned int timeInMinutes = hour_minutes(); 
        //minutesToHourMin(timeInMinutes);
        //**************************************************************************************************************
        RtcDateTime compiled = RtcDateTime(now.Year(), now.Month(), now.Day(), timeInMinutes/60, timeInMinutes%60, 0);
        Rtc.SetDateTime(compiled);
        break;
      }
      case 5 :
      {
        minutosEncendido = hour_minutes();
        EEPROM.put(minutosEncendidoPos,minutosEncendido);
        break;  
      }
      case 6:
      {
        stage=1;
        menuListPtr = menuListStage;
        stage=u8g2.userInterfaceSelectionList("Valores para", stage, menuListPtr);
        delay(500);
        minutosDeLuz = hour_minutes();
        Serial.print("minutos de Luz:");
        Serial.println(minutosDeLuz);
        Serial.println(stage);
        delay(5000);
        if (stage)//VEGETA
          {
            EEPROM.put(minutosDeLuzVPos,minutosDeLuz);
            configuradov=0;
          }
          else // FLORA
          {            
            EEPROM.put(minutosDeLuzFPos,minutosDeLuz);
            configuradof=0;
          }
        break;
      }
      case 7 :
      {
        stage=1;
        u8g2.setFont(u8g2_font_t0_17b_mf );
        stage=u8g2.userInterfaceMessage("Esta","seguro",""," SI \n NO " );
         if(stage == 1)
              {
              diadeinicio = 0;
              mesdeinicio = 0;
              anodeinicio = 0;
              diadeinicio = now.Day();
              mesdeinicio = now.Month();
              anodeinicio = now.Year();
              char str[17];
              sprintf(str, "%02d / %02d / %02d",     //%d allows to print an integer to the string
                  diadeinicio,
                 mesdeinicio,
                 anodeinicio
  
                  //get second method
                 );
  
              iniciodecultivo = ConvierteFechaEnNumero( anodeinicio,mesdeinicio,diadeinicio);
              Serial.println(str);
              byte four = (iniciodecultivo & 0xFF);
              byte three = ((iniciodecultivo >> 8) & 0xFF);
              byte two = ((iniciodecultivo >> 16) & 0xFF);
              byte one = ((iniciodecultivo >> 24) & 0xFF);
        
              //Write the 4 bytes into the eeprom memory.
              EEPROM.write(15, four);
              EEPROM.write(16, three);
              EEPROM.write(17, two);
              EEPROM.write(18, one);
              EEPROM.commit();
              }
        posiciondemenu = 0; 
        u8g2.clearDisplay();
        break;
      }
      case 8 :  
      {   
        menuListPtr = menuListIrrigation;
        stage=u8g2.userInterfaceSelectionList("Riegos", stage, menuListPtr);
        u8g2.setFont(u8g2_font_t0_17b_mf );
        u8g2.userInterfaceInputValue("cantidad ", "de riegos:", &numero, 0, 50, 2, " Veces");
        if (stage) //riego diurno
            {
              bomba1.disparosDia = numero-1;                                
              EEPROM.write(disparosDiaB1Pos, bomba1.disparosDia); //Diurno******************************************************************pa queesto
            }
            else
            {
              //tminv = numero;
             // EEPROM.write(8, tminv);
            }
            numero=0;
            u8g2.userInterfaceInputValue("Minutos ", "de riego:", &numero, 0, 300, 3, " ´´");
            if (fov) //riego diurno
            {
              bomba1.tiempoPrendidoDia = numero;
              EEPROM.write(tiempoPrendidoDiaB1Pos, bomba1.tiempoPrendidoDia);
            }
            else //riego nocturno
            {

            }
        break;      
      }     
      
      case 9:
      {         
        stage=1;
        menuListPtr = menuListStage;
        stage=u8g2.userInterfaceSelectionList("T° y H%", stage, menuListPtr);
        u8g2.setFont( u8g2_font_t0_22b_mf);
        u8g2.userInterfaceInputValue("Temperatura", "minima: ", &numero, 0, 140/*range sensor*/, 3, " °"); 
        byte lo;
        if (stage)
            {
              tminf = numero;
              EEPROM.write(tempMinFPos, tminf); //Floracion*******************************************************************pa queesto
              lo=numero;
            }
            else
            {
              tminv = numero;
              EEPROM.write(tempMinVPos, tminv);
              lo=numero;
            }
        numero=0;    
        u8g2.userInterfaceInputValue("Temperatura", "maxima: ", &numero, lo, 140/*range sensor*/, 3, " °");
        if (stage)
            {
              tmaxf = numero;
              EEPROM.write(tempMaxFPos, tmaxf); //Floracion*******************************************************************pa queesto
              lo=numero;
            }
            else
            {
              tmaxv = numero;
              EEPROM.write(tempMaxVPos, tmaxv);
              lo=numero;
            }
        numero=0;    
        u8g2.userInterfaceInputValue("Humedad", "minima: ", &numero, 0, 140/*range sensor*/, 3, " %"); 
        if (stage)
            {
              hminf = numero;
              EEPROM.write(humedadMinFPos, hminf); //Floracion*******************************************************************pa queesto
              lo=numero;
            }
            else
            {
              hminv = numero;
              EEPROM.write(humedadMinVPos, hminv);
              lo=numero;
            }
        numero=0;    
        u8g2.userInterfaceInputValue("Humedad", "maxima: ", &numero, lo, 140/*range sensor*/, 3, " %");
        if (stage)
            {
              hmaxf = numero;
              EEPROM.write(humedadMaxFPos, hmaxf); 
            }
            else
            {
              hmaxv = numero;
              EEPROM.write(humedadMaxVPos, hmaxv);
            }  
      }
      default:
      {
      break ;  
      }
    }
    u8g2.clearDisplay();
  }
  
  
  
  void testear_botones(void)
  { 
    revisar_timer();
    if (testear_boton == 1)
    {
      int datoan = analogRead(0);
      //Serial.println("dato an:");
      //Serial.println(datoan);
      if (datoan > 20)
      {
        flagprint = 1;
        if (datoan > 650 && datoan < 1024)//izquierda
        {
          Serial.println("izquierda");
          numero = numero - 1;
          if (numero <= li && numero >ls)
          {
            numero = ls - 1;
          }
          izquierda++;  
          derecha = 0;
          if(izquierda >= 3)
          {
           numero = numero - 2;  
          }
        }
        else if (datoan > 300 && datoan < 650)//enter
        {
          enter = 1;
          m = 1;
          Serial.println("enter");
          izquierda=0;
          derecha=0;
        }
        else if (datoan > 150 && datoan < 300)  //derecha
        {
          Serial.println("derecha");
          numero = numero + 1;
          if (numero >= ls )
          {
            numero = li + 1;
          }
          derecha++;
          izquierda=0;
          if(derecha >= 3)
          {
           numero = numero + 2;  
          }
        }
      }
      else
      {
        m = 0;
        mp = 0;
        derecha=0;
        izquierda=0;
      }
      testear_boton = 0;
    }
  }
  
  
  void revisar_timer(void) {
    if (500 <= (millis() - tiempo_anterior))
    {
      tiempo_anterior = millis();
      contador++;   //timer para sensar botones
      contador2++;  //timer para sensart TEMP y HUMI
      reloj++;   
      testear_boton = 1;
      if (m == 1)
      {
        mp++;
      }
    }
  }
  
  unsigned int hour_minutes(void)
  {
    byte H=0;
    byte M=0;
    numero = 0;
    flagprint = 1;
    sw = 0;
    while (sw == 0)
    {
      revisar_timer();
      yield();
      ls = 24;
      li = -1;
      testear_botones();
      H = numero;
      if (flagprint = 1)
      {
        u8g2.setFont(u8g2_font_helvB18_tf);
        u8g2.clearBuffer();
        flagprint = 0;
        u8g2.drawStr( 27, 27,"Hora:");
        sprintf(variable_display, "%02d:00", H);
        u8g2.drawStr( 25, 55,variable_display);
        u8g2.sendBuffer();
      }
      if (enter == 1)
      {
        enter = 0;
        sw = 1;
      }
    }
    sw = 0;
    numero = 0;
  
    while (sw == 0)
    {
      revisar_timer();
      yield();
      ls = 60;
      li = -1;
      testear_botones();
      M = numero;
      if (flagprint = 1)
      {
        flagprint = 0;
        Serial.print("Minutos:");
        u8g2.clearBuffer();
        u8g2.drawStr( 14, 27,"Minutos:");
        sprintf(variable_display, "%02d:%02d", H, M);
        u8g2.drawStr( 25, 55,variable_display);   
        u8g2.sendBuffer();
      }
      if (enter == 1)
      {  
        enter = 0;
        sw = 1;
        numero = 0;
      }
    }   
    sw = 0;
    u8g2.clearDisplay();
    u8g2.clearBuffer();
    return (H*60+M);
  }


  int tablaMes[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

long ConvierteFechaEnNumero( int ano, int mes, int dia)
{

  long diaNum;
  
  diaNum = (ano-2000)*365 + (ano-2000)/4 + tablaMes[mes-1] + dia;
  if(((ano-2000)%4==0) && (mes<3)) // Es bisiesto y no hemos pasado 29/02
    {
    diaNum--;
    }

  return diaNum;
}


