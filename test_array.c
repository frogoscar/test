#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SERIAL_NUMBER_LENGTH      16
#define SimulationNumberOfDevices 20000

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define KPDEFV2_APPLICATION_HELLO               'c'     // 0x63

struct KprotoPcktHeader{
  uint8_t       Type;                           /**< Offset 0  .... 0 */
  uint16_t      Checksum;                       /**< Offset 1  .... 2 */
  uint8_t       Serial[16];   /**< Offset 3  .... (3+16)-1=18 (OPTIONAL!) */
  uint16_t      DataLength;                     /**< Offset 19 .... 20  Hence a packet it at least 21 bytes long if the serial number is included */
}__attribute__ ((packed));

struct KprotoPckt {
  struct KprotoPcktHeader KprotoPcktHeader;  /**< Packet's header */
  uint8_t       Data[484];       /**< Packet's data */
  uint8_t       Pad;                         /**< Set to binary zero if ever we want to process Data as a string. */
}__attribute__ ((packed));

enum KpJob {
  KP_HELLO,
  KP_COMMAND_RESULT,
  KP_GIS_DATA,
  KP_END
};

enum KprotoState {
  KPROTO_STATE_IDLE,
  KPROTO_STATE_SEND_APPLICATION_HELLO,
  KPROTO_STATE_EXPECT_APPLICATION_COMMAND,
  KPROTO_STATE_SEND_GISDATA,
  KPROTO_STATE_SEND_END,
};

void DeviceMakeNumber(uint8_t *Sn,uint16_t Variant,uint32_t Base,uint32_t Number){
  uint32_t v=Base+Number;
  uint32_t Chk=0;
  uint8_t i;

  *(Sn+0x0)=0xFF;         /** This will immediately tag a simulated device */
  *(Sn+0x1)=0x00;         /** Year */
  *(Sn+0x2)=0x00;         /** Month */
  memcpy(Sn+0x3,&v,4);
  *(Sn+0x7)=0xAA;         /** Fake factory / production unit number */
  *(Sn+0x8)=Variant>>8;   /** Variant, high byte */
  *(Sn+0x9)=Variant&0xFF; /** Variant, low byte */
  *(Sn+0xA)=0x0;          /** Production line */
  *(Sn+0xB)=0x0;          /** Random, byte 0 */
  *(Sn+0xC)=0x1;          /** Random, byte 1 */
  *(Sn+0xD)=0x0;          /** Indus software version */
  *(Sn+0xE)=0x0;          /** GSM operator code */

  for(i=0;i<SERIAL_NUMBER_LENGTH-1;i++)
    Chk+=*(Sn+i);

  printf("++++++++++++++++++++++++++++++++++++++++\n");
  printf("Checksum made is %d\n", Chk);

  *(Sn+0xF)=(~((Chk&0xFF)-1))&0xFF;

  printf("The 16 ieme octet made is %d\n", *(Sn+0xF));

  if(*(Sn+0xF)==0){
    (*(Sn+0xB))+=0x1;

    for(i=0;i<SERIAL_NUMBER_LENGTH-1;i++)
      Chk+=*(Sn+i);

    printf("Checksum re-made is %d\n", Chk);

    *(Sn+0xF)=(~((Chk&0xFF)-1))&0xFF;


  }
}

uint8_t DeviceCheckSerial(uint8_t *p){
  uint32_t Chk=0;
  uint8_t i;
  uint8_t s;

  for(i=0;i<SERIAL_NUMBER_LENGTH-1;i++)
    Chk+=*(p+i);



  s=(~((Chk&0xFF)-1))&0xFF;


  if((!Chk)||(!s)||(*(p+(SERIAL_NUMBER_LENGTH-1))!=s))
    return false;

  return true;
}

uint8_t KpInit(enum KprotoState *KprotoState, struct KprotoPckt *KprotoPckt, int i){
  /*
   * Make serial number for all the devices
   */
  DeviceMakeNumber(KprotoPckt[i].KprotoPcktHeader.Serial, 0xFF00,10000,i);
  if(!DeviceCheckSerial(KprotoPckt[i].KprotoPcktHeader.Serial)){
    printf("Serial number error for device %d !\n", i);
    return false;
  }

  KprotoPckt[i].Pad=1;
  /*
   * Base state
   */
  KprotoState[i]=KPROTO_STATE_IDLE;

  return true;
}

uint8_t KpManagement(enum KprotoState *KprotoState, struct KprotoPckt *KprotoPckt, enum KpJob KpJob, int i){

  if(KpJob == KP_HELLO){
    KprotoState[i] = KPROTO_STATE_SEND_APPLICATION_HELLO;
  }

  switch(KprotoState[i]){
  case KPROTO_STATE_IDLE:
    break;

  case KPROTO_STATE_SEND_APPLICATION_HELLO:

    KprotoPckt[i].KprotoPcktHeader.Type=KPDEFV2_APPLICATION_HELLO;
    break;
  }

    return 0;
}

int main(){

  int i, j;

  struct KprotoPckt KprotoPckt[SimulationNumberOfDevices];
  enum KprotoState KprotoState[SimulationNumberOfDevices];

  for(i=0; i<SimulationNumberOfDevices; i++){

    if(!KpInit(KprotoState, KprotoPckt, i)){
      /* printf("Can not initialize k-protocol for transimission for device %d\n", i); */
      return false;
    }

    KpManagement(KprotoState, KprotoPckt, KP_HELLO, i);

  }

  /* for(i=0; i<SimulationNumberOfDevices; i++){ */

  /*   if(KprotoPckt[i].KprotoPcktHeader.Type==KPDEFV2_APPLICATION_HELLO) */
  /*     printf("For KprotoPckt %d , it's Type is KPDEFV2_APPLICATION_HELLO\n", i); */
  /* } */

  /* for(i=0; i<SimulationNumberOfDevices; i++){ */
  /*   for(j=0; j<16; j++){ */
  /*     printf("%.2x", KprotoPckt[i].KprotoPcktHeader.Serial[j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */


  return 0;
}
