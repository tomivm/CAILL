
void verificar_timers(unsigned int minutos){
  if(multiplyOf(95,minutos)) //oxigenador HDR
    {
      digitalWrite(Oxigenador, HIGH);
      oxigenador.minutosApagar = minutos + 10;// bomba1.tiempoPrendidoDia;
      Serial.print("prendo OX");
    }
  Serial.print(poa);
  if (poa){
    if(apagaralotrodia){     
      if(minutos>minutosEncendido){
        if(minutos == minutosEncendido || multiplyOf(bomba1.intervaloDia,minutos+bomba1.offsetEncenderDia)){  //en este caso del prender al otro dia usaremos como referencia para calcular el
          digitalWrite(BOMBA, HIGH);                                                                       //offset la hora de encendido
          bomba1.minutosApagar = minutos + bomba1.tiempoPrendidoDia;
          Serial.print("PRENDO BOMBA");
        }
      }
      else{
        if(minutos == minutosEncendido || multiplyOf(bomba1.intervaloDia,minutos+bomba1.offsetApagarDia)){   //en este caso del prender al otro dia usaremos como referencia para calcular el
          digitalWrite(BOMBA, HIGH);                                                                      //offset la hora de apagado
          bomba1.minutosApagar = minutos + bomba1.tiempoPrendidoDia;
          Serial.print("PRENDO BOMBA");
        }   
      }  
    }
    else if (minutos == minutosEncendido || multiplyOf(bomba1.intervaloDia,minutos+bomba1.offsetEncenderDia)){
      digitalWrite(BOMBA, HIGH);                                                                       //en el caso que el momento de luz sea en el mismo dia, usaremos la hora de prender
      bomba1.minutosApagar = minutos + bomba1.tiempoPrendidoDia;                                     //para calcular el offset
      Serial.print("PRENDO BOMBA");
    }     
  }
  if(bomba1.minutosApagar>1439){
    bomba1.minutosApagar=bomba1.minutosApagar-1439;
  }
  if(minutos > bomba1.minutosApagar){
    Serial.print("apago Bomba");
    digitalWrite(BOMBA, LOW);  
  }  
  if(oxigenador.minutosApagar>1439){
    oxigenador.minutosApagar=oxigenador.minutosApagar-1439;
  }
  if(minutos>oxigenador.minutosApagar){
    Serial.print("apago Ox");
    digitalWrite(Oxigenador, LOW);
  }
}

 bool multiplyOf(int number2,int number1)
 {
  if (number1==0)
    {
      return 0;
    }
  int resto;
  resto = number1%number2;  // el resto de la division de number 2 sobre number 1
if(resto==0)
  {
  return 1;
  }
else
  {
  return 0;  
  }
 }  

void configurarBomba1(void){ 
   EEPROM.write(disparosDiaB1Pos, bomba1.disparosDia);
   EEPROM.write(tiempoPrendidoDiaB1Pos, bomba1.tiempoPrendidoDia);
  bomba1.intervaloDia = minutosDeLuz / bomba1.disparosDia;
  int resto;
  resto = minutosEncendido % bomba1.intervaloDia;  // el resto de la division de number 2 sobre number 1
  bomba1.offsetEncenderDia = bomba1.intervaloDia - resto;
  resto = minutosApagar % bomba1.intervaloDia;  // el resto de la division de number 2 sobre number 1
  bomba1.offsetApagarDia = bomba1.intervaloDia - resto;
}

