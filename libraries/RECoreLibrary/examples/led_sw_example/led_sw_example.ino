/*
   RECore Example
   LED and Switch Example
*/

void setup() {
  
}

void loop() {
  if(digitalRead(14) == LOW){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }

}
