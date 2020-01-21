/**
 * LemonRx Decoder
 * 
 * The LemonRx seems to use a serial like interface between the main board and RF Board.
 * 
 * From the logic analyzer, the baud rate appears to be around 115384 and the RF Board
 * sends a packet once per pwm cycle with 16 bytes. Each channel seems to have 2 bytes
 * (an upper and lower byte) So far I have mapped out:
 * 
 * Aileron[2-3]
 * Aux[4-5]
 * Elevator[6-7]
 * CH5[8-9]
 * Rudd[10-11]
 * Throttle[14-15]
 * 
 * The upper bit should be masked by 0x7 (the higher bits may be a descriptor of sorts
 * or other data) and the lower bits should be masked by 0xFF (due to the way arduino
 * reads serial data/signing)
 */
char rxData[16] = {0,};

unsigned int AILERON = 0;
unsigned int AUX = 0;
unsigned int ELEVATOR = 0;
unsigned int CH5 = 0;
unsigned int RUDDER = 0;
unsigned int THROTTLE = 0;

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(115384);
  Serial1.flush();
}

void loop() {
  if (Serial1.available()) {
    Serial1.readBytes(rxData, 16);
    AILERON = ((rxData[2]&0x7)*0xFF) + (rxData[3]&0xFF);
    AUX = ((rxData[4]&0x7)*0xFF) + (rxData[5]&0xFF);
    ELEVATOR = ((rxData[6]&0x7)*0xFF) + (rxData[7]&0xFF);
    CH5  = ((rxData[8]&0x7)*0xFF) + (rxData[9]&0xFF);
    RUDDER  = ((rxData[10]&0x7)*0xFF) + (rxData[11]&0xFF);
    THROTTLE = ((rxData[14]&0x7)*0xFF) + (rxData[15]&0xFF);

    Serial.print("AILE:");
    Serial.print(AILERON);
    Serial.print(", ELEV:");
    Serial.print(ELEVATOR);
    Serial.print(", RUDD:");
    Serial.print(RUDDER);
    Serial.print(", THRO:");
    Serial.print(THROTTLE);
    Serial.println();
  }
//  if (Serial.available()) {
//    if (Serial.read() == 'B') {
//      Serial1.print((char)85);
//      Serial1.print((char)213);
//    }
//  }
}
