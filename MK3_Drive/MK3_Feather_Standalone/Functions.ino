void recRemote(){
    digitalWrite(LED_BUILTIN, LOW);
    if (radio.receiveDone()) {
      if(radio.SENDERID == uint8_t(REMOTE_ADDRESS)){
        if (radio.DATALEN != sizeof(recFromRemote)){
          Serial.print("Invalid payload received, not matching Payload struct!");
        }else{
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println(recFromRemote.Joy1X); 
          Serial.println(recFromRemote.Joy2X); 
          Serial.println(recFromRemote.Joy3X); 
          Serial.println(recFromRemote.Joy4X); 
          Serial.println("-----------");
          Serial.println(recFromRemote.lBut1); 
          Serial.println(recFromRemote.lBut2); 
          Serial.println(recFromRemote.lBut3); 
          Serial.println("---------------------------------");
          // Serial.println(recFromRemote.Joy2X); 
        

          recFromRemote = *(recRemoteData*)radio.DATA;
          SendRemote.sendData();
          delay(5);

       }
      }

      lastRec = millis();
      Send = true;
      recBody();
    }
    
  }
    
  
  void recBody(){
 
      if(Serial1.available() > 0){
        SendBody.receiveData();
      memcpy(bodybuf, &recFromBody, sizeof(recFromBody));
      if(recFromRemote.wireless == 1){
        radio.send(DOME_ADDRESS, bodybuf, sizeof(recFromBody)); 
      }else{
        radio.send(REMOTE_ADDRESS, bodybuf, sizeof(recFromBody));
      }
      delay(5);
    }
    lastSent = millis();
  }

