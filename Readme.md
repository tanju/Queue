# Queue

This is a queue (circular buffer) that may be used as a communication buffer
on an Arduino

## Example usage

```
Queue commQueue<byte, 20>;

void loop(){
  commQueue.write( Serial.read() );

  (...)

  while( commQueue.available() ){
    Serial.print( commQueue.read() );
  }
}
```

## Installation

1. Create a folder named Queue in your sketches folder
2. Place the Queue.h file in the folder you have created
3. Restart yor Arduino IDE if it is running

