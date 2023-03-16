


  const int ledPin = 13;

// 점멸횟수 변수 설정
int blinkNumber = 0;

String stringValue[]={"Binary:","Octal:"};

void setup() {
  
  Serial.begin(9600);
  
  pinMode(ledPin,OUTPUT);
}

void loop() {

  if(Serial.available()){      
 
    char val = Serial.read();
   
    if(isDigit(val)) {
    
      blinkNumber = (val - '0');
      
    
    if (blinkNumber <10){
    Serial.print("ENTER NUMBER:");
    Serial.print(blinkNumber);
     Serial.print(", ");
     Serial.print(stringValue[0]);
      Serial.print(blinkNumber,BIN);
      Serial.print(", ");
      Serial.print(stringValue[1]);
      Serial.println(blinkNumber,OCT);
      delay (2000);
      }
    }

    
      for(char i=0; i < blinkNumber; i++){
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(100);
    }
    }
   blinkNumber = 0;
}
