 #include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
//#include <MySQL_Encrypt_Sha1.h>
//#include <MySQL_Packet.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
WiFiServer server(80);

bool wifiConect=0; //leer la eeprom
bool passwordSave=0;
const char *ssid = "CAILL420";
const char *password = "420420420";
const char* host = "160.153.36.4";//"192.168.43.137";//"192.168.43.109";//"172.20.10.2";//"192.168.0.16";
const int httpsPort = 3306;
  

String search_next_word(String string,String Word,String fin);
//void AP_on(void);
String Token="";//leer EEPROM
String ID="";//leer EEPROM
String postData(String data);

IPAddress server_addr(192,168,20,60);//IPAddress server_addr(192,168,1,104);  // IP of the MySQL *server* here
char user[] = "tomivm";              // MySQL user login username
char passwordMySQL[] = "Lofeagtopa1";        // MySQL user login password

// Sample query
bool postID=EEPROM.read(postIDPos); //leer EEPROM

WiFiClient client;
MySQL_Connection conn((Client *)&client);

String response[2][20];
byte colsNumber=0;

void AP_on (void) //encender el modo AP para poder conectar nuestro caill a la red WiFi
  { 
  u8g2.clearDisplay(); 
  u8g2.clearBuffer();  
  u8g2.drawStr( 2, 15,"\tRed Wifi:");
  u8g2.drawStr( 60, 25,"CAILL420");
  u8g2.drawStr( 4, 35,"Clave: ");
  u8g2.drawStr( 60, 47,"420420420");  
  u8g2.drawStr( 50, 55,"cancelar");
  u8g2.sendBuffer();
  WiFi.mode(WIFI_AP_STA);  
  Serial.print("Configuring access point..."); 
  WiFi.softAP("CAILL420","420420420");
  server.begin();
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  Serial.println("HTTP server started");
  wifiConect=1;
  passwordSave=0;
  WiFiClient client;
  //WiFiClient client = server.available();
  String clave = "";
  String ssidWiFi = "";
  while(!client){
   client = server.available();
   testear_botones();  
   if(enter)
    {
    enter=0;  
    return;
    }
   }
  Serial.println("somebody has connected :)");
  String request = client.readString();
  //ssid=Fibertel WiFi718,clave=0141650064,
  Serial.println(request);
  ssidWiFi = search_next_word(request,"ssid=",",");
  clave = search_next_word(request,"clave=",",");
  Serial.println(ssidWiFi);
  Serial.println(clave);
  client.println("conectando");
  if (clave=="NO"){
    WiFi.begin(ssidWiFi.c_str());
  } 
  else   {
   WiFi.begin(ssidWiFi.c_str(),clave.c_str());
  }
  bool conect=1;
  static int timeOut=0;  
  while (WiFi.status() != WL_CONNECTED) {    
    delay(500);
    timeOut++;
    if(timeOut==35){
      WiFi.disconnect();
      client.println("contraseña erronea"); 
      Serial.print("Contraseña erronea");        
      timeOut=0;
      conect=0;
      break;
    }
    Serial.print(timeOut); 
    Serial.print("."); 
  } 
  Serial.print(conect); 
  if(conect==1)
    {
    //passwordSave=1;
    //escribir en la eEprom 
    client.print("wifi conectado");
    client.println();
    //delay(1500);
    //client.stop();
    server.stop();
   // WiFi.mode(WIFI_STA);
    Serial.println("");
    Serial.println("WiFi connected");
//    Serial.println("IP address: ");
//    Serial.println(WiFi.localIP());
//    // Use WiFiClientSecure class to create TLS connection
//    //postData("title=foo&body=bar&userId=1&t=50");
    if(postID==1)
      {
      strcpy (INSERT_DATA,"INSERT into caill.CAILLlist (idcaill) value ('%s')");  
      String convert = WiFi.macAddress();
      convert.toCharArray(idcaill,35);
      sprintf(query, INSERT_DATA,idcaill);//idcaill);
      while(!insertData()) 
      postID=0;
      EEPROM.write(postIDPos , postID);
      EEPROM.commit();
      u8g2.clearDisplay()  ; 
      u8g2.clearBuffer();
      u8g2.drawStr(3, 1,"ya estas registrado :)"); 
      delay(1500);
      }
    }  
  }      
//      String response = "";  
//      response=postData("title=PING&body=getToken");
//      if(response == "error")
//        {
//        Serial.println("error de servidor");
//        }
//      else
//        {  
//        Token=search_next_word(response,"Token",",");
//        ID=search_next_word(response,"ID",",");
//        getToken=0; //guardar en eeprom      
//        Serial.print(Token);
//        }
//      }  
//      else
//      {
//      String response = "";
//      response = postData("title=PING");
//      if(response == "error")
//        Serial.println("error de servidor");
//      }


bool insertData(void)
  {
//    if (conn.connect(server_addr, 3000, user, passwordMySQL)) {
//    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Save    
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    Serial.println("Data recorded.");
//    return 1;
//  }
//  else
//  {
//    Serial.println("Connection failed.");
//    return 0;
//  }  
//  conn.close();
  }

void select (void)
  { 
  Serial.println("> Running SELECT with dynamically supplied parameter");
  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Supply the parameter for the query
  // Here we use the QUERY_POP as the format string and query as the
  // destination. This uses twice the memory so another option would be
  // to allocate one buffer for all formatted queries or allocate the
  // memory as needed (just make sure you allocate enough memory and
  // free it when you're done!).
  sprintf(query, QUERY_POP, idcaill);
  // Execute the query
  cur_mem->execute(query);
  // Fetch the columns and print them
  column_names *cols = cur_mem->get_columns();
  byte y=0;
  colsNumber=cols->num_fields;
  for (int f = 0; f < cols->num_fields; f++) {
    Serial.print(cols->fields[f]->name);
    response[0][f]=cols->fields[f]->name;
    Serial.print(response[0][f]);
    if (f < cols->num_fields-1) {
      Serial.print(',');
    }
  }
  Serial.println();
  y++;
  // Read the rows and print them
  row_values *row = NULL;
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      for (int f = 0; f < cols->num_fields; f++) {
        Serial.print(row->values[f]);
         response[y][f]=row->values[f];
        if (f < cols->num_fields-1) {
          Serial.print(',');
        }
      }
      y++;
      Serial.println();
    }
  } while (row != NULL);
  delete cur_mem;
//  if (y==1)
//    {
//      Serial.println("no hay cambio");
//      return;  
//    }   
  }

bool connectionOpen(void){
  if(conn.connect(server_addr, 3306, user, passwordMySQL))
  {
    delay(1000);
    return 1;
  }
  else
  return 0;
}

bool WiFiIsConected (void){
  if(WiFi.status() == WL_CONNECTED) {
    return 1;
  }
  else{
    return 0;
  }
}

void connectionClose(void){
  conn.close();
}

String postData(String data)
    {
    String PostData = "";  
    WiFiClient client;   
    PostData = data;  
    Serial.print("connecting to ");     
    Serial.println(host);
    if (!client.connect(host, httpsPort)) 
      {
      Serial.println("connection failed");
      return "error" ;
      }
       String url = "/";
    Serial.print("requesting URL: ");
    Serial.println(url);
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n"+
               "Content-Length: " );              
    client.println(PostData.length());
    client.println("\r\n"+
                 PostData);
    client.print("Connection: close\r\n\r\n");
    Serial.println("request sent");
    while (client.connected()) 
      { 
      String line = client.readStringUntil('\n');
      if (line == "\r") 
        {
        Serial.println("headers received");
        break;
        }
      }  
      String line = client.readStringUntil('\n');
      if (line.startsWith("{\"state\":\"success\"")) 
        {
        Serial.println("esp8266/Arduino CI successfull!");
        } 
        else 
        {
        Serial.println("esp8266/Arduino CI has failed");
        }
      Serial.println("reply was:");
      Serial.println("==========");
      Serial.println(line);
      Serial.println("==========");
      Serial.println("closing connection");  
      return line;
   }

void SetAll(void)
  {
    byte x=1;
    while(x < colsNumber)  
              {
              switch (modo) {
              case 1:  
                if(response[0][x] == "min temperature")  
                  {     
                  EEPROM.write(tempMinVPos,response[1][x].toInt());
                  Serial.println();
                  }
                 if(response[0][x] == "max temperature")
                  {
                  EEPROM.write(tempMaxVPos,response[1][x].toInt()); 
                  Serial.println(response[1][x].toInt());
                  Serial.println("tempemaxvcam");   
                  }
                 if(response[0][x] == "min humedity")
                  {
                  EEPROM.write(humedadMinVPos,response[1][x].toInt());   
                  Serial.println("humidityvcam");   
                  } 
                 if(response[0][x] == "max humedity")
                  {
                  EEPROM.write(humedadMaxVPos,response[1][x].toInt());  
                  Serial.println("humiditymaxvcam");   
                  }
               configuradov=0;     
               break;
               case 2:        
                 if(response[0][x] == "min temperature")
                  {
                  EEPROM.write(tempMinFPos,response[1][x].toInt());  
                  Serial.println("tempeminfcam");   
                  } 
                 if(response[0][x] == "max temperature")
                  {
                  EEPROM.write(tempMaxFPos,response[1][x].toInt());  
                  Serial.println("tempemaxvcam");   
                  }
                 if(response[0][x] == "min humedity")
                  {
                  EEPROM.write(humedadMinFPos,response[1][x].toInt());  
                  Serial.println("humidityfcam");   
                  } 
                 if(response[0][x] == "max humedity")
                  {
                  EEPROM.write(humedadMinFPos,response[1][x].toInt());  
                  Serial.println("humiditymaxcam");   
                  }
                 configuradof=0; 
                 break; 
              } 
              if(response[0][x] == "name")
              {
               nombrePerfil = response[1][x];          
              }
              EEPROM.commit();     
              x++;  
              }          
  }
String search_next_word(String string,String Word,String fin)
    {
    int posicion=0;  
    if((posicion = string.indexOf(Word))== -1);
    int offset = Word.length();
    //Serial.println(posicion);
    int Stop = string.indexOf(fin,posicion);
    //Serial.println(string.substring(posicion+offset,Stop));
    return string.substring(posicion+offset,Stop);
    }  
