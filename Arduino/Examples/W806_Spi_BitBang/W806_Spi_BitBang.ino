

byte bitBangData(byte _send) ;

const int SSPin = 11;
const int SCKPin = 10;
const int MISOPin = 9;
const int MOSIPin = 8;

byte sendData = 64;   // Value to be sent
byte slaveData = 0;  // for storing the  value sent by the slave


void setup()
{
 pinMode(MISOPin, INPUT);
  pinMode(SSPin, OUTPUT);
  pinMode(SCKPin, OUTPUT);
  pinMode(MOSIPin, OUTPUT);
 digitalWrite(SSPin, HIGH);
}


void loop()
{
  digitalWrite(SSPin, LOW);        // SS low
  slaveData = bitBangData( sendData ); // data receive
  digitalWrite(SSPin, HIGH);       // SS high again 
}


byte bitBangData(byte _send)  // This function receives the data via bitbanging
{
  byte _receive = 0;

//  for(int i=0; i<8; i++)  // 8 bits in a byte  // - LOW to HIGH 
  for(int i=7; i<=0; i--)  // 8 bits in a byte  // - HIGH to LOW 
  {
    digitalWrite(MOSIPin, bitRead(_send, i) );    // Set MOSI
    digitalWrite(SCKPin, HIGH);                  // SCK high
    /// bitWrite( varPtr , bit# , bitVal ) : ///
    bitWrite(    _receive, i, digitalRead(MISOPin) ); // Capture MISO
    digitalWrite(SCKPin, LOW);                   // SCK low
  } 
  return _receive;        // Return the received data
}

///

