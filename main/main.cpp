#include "mbed.h"
#include "main.h"
#include "SDFileSystem.h"
#include "OV7670.h"
#include "SIM800H.h"


Serial pc(PA_2, PA_3);
SDFileSystem sd(SD_MOSI, SD_MISO, SD_SCLK, SD_CS, "sd");
OV7670 cam(CAM_SDA, CAM_SCL, CAM_VSYNC, CAM_PCLK, CAM_HREF, CAM_PWDN, CAM_RST, CAM_DATAPORT, (uint16_t)CAM_PORTMASK);
Sim800H sim800(SIM_TX, SIM_RX, SIM_BAUD, SIM_RST);	
FILE* fp;
DigitalOut testled(PC_8);
//Test to get camera trigger. 
//DigitalIn trig(PA_12, PullDown);
InterruptIn pir(PA_12);


uint8_t uid[12];
string id;

//Ticker Capture;
//BusIn DIPRep(p0, p1);
//BusIn DIPTrig(p2, p3);
//BusIn DIPIR(p4, p5);
//BusIn DIPExtTrig(p6, p7);

//BusOut led(A2,A1,A0);
//
//Test to check dip switches
BusIn input(PB_8,PB_9,PB_10,PB_11,PB_12,PB_13,PB_14,PB_15);


char fileName[20];
char directory[30];
//string identifier;
//int imigIndex = 0;


//PIR interrupt
//InterruptIn pir(PB_7);

//Timeout camTO;
//Timeout sendTO;
//Ticker batTick;
//bool camFlag = 0;
//bool sendFlag = 0;
int batFlag = 0;

//Fix variable names, especially where you have fname, filename, fileName etc
//Get rid of globals where poss.

//Comments and tidy

/*
int DipRepRate() {

	switch (DIPRep) {
		case 0x0:	return 1;	
			break;//1 sec pics
		case 0x1:	return 5;
			break;//5 sec pics
		case 0x2:	return 10;
			break;//10 sec pics
		case 0x3:	return 30;
			break;//30 sec pics
	}
}

void DipTrigConfig() {

	switch (DIPTrig) {
		case 0x0:;
			break; //PIR only
		case 0x1:;
			break; //PIR & vib
		case 0x2:;
			break; //PIR & acoustic
		case 0x3:;
			break; //PIR & vib & acoustic
	}
}

void DipIRPower() {

	switch (DIPIR) {
		case 0x0:;
			break; //1 powers
		case 0x1:;
			break; //4 powers
		case 0x2:;
			break; //16 powers
		case 0x3:;
			break; //32 powers
	}
}

void DipExternalTrigger() {

	switch (DIPExtTrig) {
		case 0x0:;
			break;
		case 0x1:;
			break;
		case 0x2:;
			break;
		case 0x3:;
			break;
		}
}

string getIdentifier(){
	return identifier;
}

void TakeImage() {
	Capture.detach();

	
}
*/

void PirIsr(void)
{
//Do nothing, just wakes micro
}

void sysInit(void)
{			
	pc.printf("Initialisaton starting....\n\r");		
	cam.camInit();
	//Capture.attach(&TakeImage, DipRepRate());
	//Capture.attach(&TakeImage, 2);
	sim800.simInit(); //Commented out to test camera output
	
	pc.printf("Initialisaton complete\n\r");	
	pir.rise(PirIsr);

	//pir.rise(pirISR);	
	//batTick.attach(batISR, BATTIMEOUT);
	//setRGB(0,0,0);
}

void standby(void)
{
	//Put the camera into standby
	cam.standby();	
	//sim800.standby();
	pc.printf("Standby\n\r");
	wait(1);
	sleep();	
}

void wakeup(void)
{	
	cam.wakeup();
	//Temp commented out
	//sim800.wakeup();
}

//void pirISR(void)
//{
//	camFlag = 1;
//}

//void camISR(void)
//{
//	pir.enable_irq();
//}

//void sendISR(void)
//{
//	sendFlag = 1;
//}

//void batISR(void)
//{
//	batFlag = 1;
//}

int main() 
{ 	
	testled.write(1);

	pc.baud(115200);
	
	//Set the PLL source mux to HSI
	RCC->PLLCFGR |= 0x00000002;
	
	
	//set system clock source to PLL
	RCC->CFGR |= 0x00000003;
	
	
	
	sysInit();	//Initialise the system
//	identifier = sim800.getIdentifier();
	
	STM32UID(uid);

	//Should be moved, perhaps into the STM22UID function
	char buff[3];
	for(uint8_t i=0; i<12; i++) {
		snprintf(buff, 3, "%02X", uid[i]);
		id.append(buff);
	}	

	while(1)
	{
		pir.disable_irq();
		cam.wakeup();
		pc.printf("Capturing image...\n\n\r");	

		//Image captured in memory	
		cam.captureImg(320,240);
		//Store image with temporary name "latest.jpg"
		cam.storeImg();	
	
		bool ret = sim800.sendEXTFTP(SD_DIR, "latest.jpg");
		if(ret)
		{
			pc.printf("Send successfull\n\r");
		}
		else
		{
			pc.printf("Send failed\n\r");

		}
		cam.standby();
		pir.enable_irq();
		sleep();
	}	
/*	
	while(1){
			Send images
			
//			testled.write(1);
			cam.wakeup();
			cam.captureImg(320, 240);
			const char * c = identifier.c_str();
			if (cam.storeImg(c, imigIndex)){
				imigIndex++;
			}
//			testled.write(0);
			pc.printf("1.\n\r");
		
			sim800.wakeup();			
			wait(1);
			DIR* pDIR;
			pc.printf("2.\n\r");
			struct dirent* entry;
			pDIR = opendir("/sd/images");
			
			if((pDIR) == NULL) {
				pc.printf("Directory could not be opened. Check SD card.\n\r");
				return 0;
			}
			else
			{
				while((entry = readdir(pDIR)) != NULL)
				{
					if(entry->d_name[0] != 's' && strcmp(entry->d_name,".jpg") != NULL)
					{
						char file[30];
						const char * c = identifier.c_str();
						sprintf(file, "%.20s(%05i).jpg",c ,imigIndex-1);
						bool ret = sim800.sendFTP(SD_DIR, file);
						if(ret) {
							pc.printf("Send successful.\n\r");
							sim800.standby();
							sim800.wakeup();
						}
						else
						{	
							pc.printf("Send failed.\n\r");
							sim800.standby();
							sim800.wakeup();
							break;
						}
					}
				}	
				pc.printf("Finished sending.\n\r");
			
			}
			closedir(pDIR);
			//pc->printf("Send rate: %i\r\n",DipRepRate());
			
		 if(batFlag > 100)
		{
			Update webpage with battery level
			batFlag = 0;
			sim800.wakeup();
			int batlevel = sim800.getBattery();
			
			if(batlevel != 0)
			{				
				sim800.sendBat(batlevel);
			}
			else
			{
				pc.printf("Bat level failed\n\r");
			}
			
		}
			batFlag++;
			
			//replace 3 with DipRepRate when hardware is fixed
			//Capture.attach(&TakeImage, 3);
			sleep();
		
		
		
	}

*/

//All of this was to accound for multiple images that are to be sent
//Remind me to explain this if necessary 

//	while(1)
//	{		
//		standby();	//put the system into low power state
//		
//		/* AWAKE */
//		__disable_irq();
//		
//		if(camFlag)
//		{
//			/* Take Image*/
//			pir.disable_irq();
//			camFlag = 0;
//			cam->wakeup();
//			wait(1);
//			setRGB(0,0,1);
//			cam->captureImg(320,240);
//			setRGB(0,0,0);
//			sim800->wakeup();	
//			updateDir(fileName);
//			setRGB(0,1,0);
//			cam->storeImg();	
//			setRGB(0,0,0);
//			sendTO.attach(sendISR, SENDTIMEOUT);
//			camTO.attach(camISR, CAMTIMEOUT);
//		}
//		else if(sendFlag)
//		{
//			/*Send images*/
//			sendFlag = 0;
//			sim800->wakeup();			
//			DIR* pDIR;
//			struct dirent* entry;
//			pDIR = opendir("/sd/images");
//			
//			if((pDIR) == NULL) {
//				pc->printf("Directory could not be opened. Check SD card.\n\r");
//				return 0;
//			}
//			else
//			{
//				while((entry = readdir(pDIR)) != NULL)
//				{
//					if(entry->d_name[0] != 's' && strcmp(entry->d_name,".bmp") != NULL)
//					{
//						bool ret = sim800->sendFTP(SD_DIR, entry->d_name);
//						if(ret) {
//							pc->printf("Send successful.\n\r");
//							sim800->standby();
//							sim800->wakeup();
//						}
//						else
//						{	
//							pc->printf("Send failed.\n\r");
//							break;
//						}
//					}
//				}	
//				pc->printf("Finished sending.\n\r");
//			}
//			closedir(pDIR);
//		}
//		else if(batFlag)
//		{
//			/*Update webpage with battery level*/
//			setRGB(1,1,0);
//			batFlag = 0;
//			sim800->wakeup();
//			int batlevel = sim800->getBattery();
//			
//			if(batlevel != 0)
//			{				
//				sim800->sendBat(batlevel);
//			}
//			else
//			{
//				pc->printf("Bat level failed\n\r");
//			}
//			
//		}
//		setRGB(0,0,0);
//		__enable_irq();
//	}
}

//void updateDir(char* fileName)
//{
//	//string response = sim800->getTime();
//	//char y[3],m[3],d[3],h[3],mn[3],s[3];		
//	//sscanf(response.c_str(), "%*s \"%[^/]%*c%[^/]%*c%[^,]%*c%[^:]%*c%[^:]%*c%[^+]%*c", y,m,d,h,mn,s);	
//	//sprintf(fileName, "%s%s%s%s%s%s.bmp", y,m,d,h,mn,s);
//	//strcpy(directory, SD_DIR);
//	//strcat(directory, fileName);
//	
//}

//uint8_t uid[12];

void STM32UID(uint8_t uid[]) {
	for(uint8_t i = 0; i<12; i++) {
		uid[i] = *(volatile uint8_t*)(0x1FFF7590 + i);
	}
}
