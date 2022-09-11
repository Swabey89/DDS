#ifndef __main_h__
#define __main_h__

#define PC_BAUD 115200

#define SD_DIR "/sd/images/"
#define SD_MOSI PA_7
#define SD_MISO PA_6
#define SD_SCLK PA_5
#define SD_CS PA_15
//Card detect

#define CAM_SDA PB_7
#define CAM_SCL PB_6
//#define CAM_XCLK D9
#define CAM_VSYNC PB_3
#define CAM_PCLK PA_10
#define CAM_HREF PA_9
#define CAM_PWDN PH_1
#define CAM_RST PH_0
#define CAM_DATAPORT PortC
#define CAM_PORTMASK 0x00FF

#define SIM_TX PC_10
#define SIM_RX PC_11
#define SIM_BAUD 57600
//#define SIM_LED PC_9
#define SIM_RST PC_12
//#define SIM_KEY PB_4
//#define SIM_PS	PB_10

#define CAMTIMEOUT 60
#define SENDTIMEOUT 120
#define BATTIMEOUT 3600

//DIP SWITCH
#define p0 PB_8
#define p1 PB_9
#define p2 PB_10
#define p3 PB_11
#define p4 PB_12
#define p5 PB_13
#define p6 PB_14
#define p7 PB_15

//#define ledOn 1
//#define setRGB(R,G,B) if(ledOn == 1) {led = ((!R<<2) | (!G<<1) | (!B<<0));} else {led = ~0b000;}


void standby(void);
void wakeup(void);
void sysInit(void);
void updateDir(char* fileName);
void pirISR(void);
void camISR(void);
void sendISR(void);
void batISR(void);
void STM32UID(uint8_t[]);



#endif
