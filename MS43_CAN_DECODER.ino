// CAN Receive Example
//

#include <mcp_can.h>
#include <SPI.h>

INT32U rxId = 0x000;
unsigned char len = 0;
unsigned char rxBuf[8];
bool show_rpm_data = true;

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10
#define DEBUG_MODE 0

void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  while(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) != CAN_OK)
    CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ);
    //Serial.println("MCP2515 Initialized Successfully!");
  //else
    //Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
  
  //Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
     CAN0.readMsgBuf(&rxId, &len, rxBuf);
     if (rxId == 0x316 && show_rpm_data){
      show_data();
      show_rpm_data = false;
      return;
     }
     if (rxId == 0x316 && !show_rpm_data){
      show_rpm_data = true;
      return;
     }
     show_data();
     delay(10);
  }
}

void show_data(){
  Serial.print(rxId);
  Serial.print(",");
  for(int i = 0; i<len; i++){
    Serial.print(rxBuf[i]);
      if (i != (len - 1))
        Serial.print(",");
  }
  Serial.println();
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
