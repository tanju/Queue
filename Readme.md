# Queue

This is a queue (circular buffer) that may be used as a communication buffer
on an Arduino

'''
Queue commQueue<byte, 20>;

void loop(){
  commQueue.write( Serial.read() );

  (...)

  while( commQueue.available() ){
    Serial.print( commQueue.read() );
  }
}
'''
