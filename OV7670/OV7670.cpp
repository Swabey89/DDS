#include "mbed.h"
#include <stdint.h>
#include "OV7670.h"
#include "SDFileSystem.h"


//Constructor

OV7670::OV7670(PinName sda, PinName scl, PinName vsync, PinName pclk, PinName href, PinName pwdn, PinName rst, PortName port, uint16_t mask) : _i2c(sda,scl), _vsync(vsync), _pclk(pclk), _href(href), _pwdn(pwdn), _rst(rst), _data(port, mask){
	//Test Printf's. Can be removed
	pc.printf("Camera initialisation started.\n\r");
		
	//Initialise not in standby and not in reset
	_rst = 1;
	_pwdn = 0;
	
//	//Start the 8MHz clock, XCLK
//	_xclk->period_us(0.125f);
//	_xclk->write(0.50f);
	
	//Enable the I2C interface for 100KHz
  	_i2c.frequency(100000);	
}

OV7670::~OV7670(void){
}

void OV7670::camInit(void){
//    wrReg(0x12, 0x80); //Reset the camera
//    wrSensorRegs8_8(ov7670_default_regs); 
//    wrReg(REG_COM10, 32);   

//		setRes();
//		setColour();
//		
//		wrReg(0x11, 9);
	

	wrReg(0xff, 0x01);  
	wrReg(0x12, 0x80); //*
	wait_ms(100);
	
	//Format is JPEG
	pc.printf("JPEG_INIT\n\r");
	wrSensorRegs8_8(OV2640_JPEG_INIT);
	pc.printf("YUV422\n\r");
	wrSensorRegs8_8(OV2640_YUV422);
	pc.printf("JPEG\n\r");
	wrSensorRegs8_8(OV2640_JPEG);
	wrReg(0xff, 0x01);
	wrReg(0x15, 0x00);
	pc.printf("Resolution\n\r");
	wrSensorRegs8_8(OV2640_320x240_JPEG);
//	wrSensorRegs8_8(OV2640_640x480_JPEG);
	pc.printf("Camera Initialised\n\r");	
}

void OV7670::standby(void){
	_pwdn = 1;	
}

void OV7670::wakeup(void){
	_pwdn = 0;
}
//void OV7670::setRes(void){
//    wrReg(REG_COM3, 4);
//    wrSensorRegs8_8(qvga_ov7670);        
//}

//void OV7670::setColour(void){
//    wrSensorRegs8_8(yuv422_ov7670);  
//}

void OV7670::wrSensorRegs8_8(const struct regval_list reglist[]) {
	const struct regval_list *next = reglist;
	for(;;){
			uint8_t reg_addr = next->reg_num;
			uint8_t reg_val = next->value;
			if((reg_addr==255)&&(reg_val==255))
					break;
			wrReg(reg_addr, reg_val);
			next++;
	}    
}

//void OV7670::captureImg(uint16_t wg, uint16_t hg){
//	
//	
//	
//    uint16_t y, x;
//		//uint8_t pixels[320*240];
//		int i = 0;
//    
//    //wait for VSYNC to go high then low
//    while(!_vsync->read());
//    while(_vsync->read());  
//	
//    y = hg;
//    while(y--)
//    {
//        x = wg;
//				//Wait for HREF to go high
//				while(!_href->read());
//        while(x--)
//        {
//					//wait for LOW on PCLK   
//					while(_pclk->read());

//					//Store each Y value in an array. Quicker than real time streaming 
//					uint16_t dat = _data->read();
//					_pixels[i] = ((dat >> 2 & 0x1) | (dat >> 2 & 0x2) | (dat >> 4 & 0x4) | (dat >> 5 & 0xF8));
//					i++;	
//				
//					//Disregard chromincance information
//					//while(!_pclk->read());
//					while(_pclk->read());
//					while(!_pclk->read());
//        }     
//				//Wait for HREF to go low
//				while(_href->read());
//    }	
//		pc->printf("Image captured\n\r");
//}


void OV7670::captureImg(uint16_t wg, uint16_t hg){	

		int i = 0;
    
		//pc.printf("Capture starting\n\r");
    //wait for VSYNC to go high then low
		while(_vsync.read());
		//pc->printf("VSYNC LOW\n\r");
    while(!_vsync.read());
		//pc->printf("VSYNC HIGH\n\r");
		//int j = 0;
	
    while(_vsync.read()) { 
			//j++;
			//Wait for HREF to go high	
			//while(!_href->read()); //Test to see if href causes issues
			while(_href.read()) {
				//pc->printf("HREF HIGH\n\r");
				//wait for LOW on PCLK   
				while(!_pclk.read());
				//pc->printf("PCLK LOW\n\r");
				//Store each Y value in an array. Quicker than real time streaming 
				//uint16_t dat = _data->read();
				//_pixels[i] = ((dat >> 2 & 0x1) | (dat >> 2 & 0x2) | (dat >> 4 & 0x4) | (dat >> 5 & 0xF8));
				_pixels[i] = _data.read();
				i++;	
				
				//Disregard chromincance information
				while(_pclk.read());
			}							
		}	
		//pc.printf("Number of pixels: %d\n\n\r", i);
		//pc.printf("Image captured\n\r");
}

void OV7670::wrReg(uint8_t reg, uint8_t dat){  
    char cmd[2] = {reg, dat};
    _i2c.write(camAddr_WR, cmd, 2);   
    wait_ms(2);
		
		//test
		/*
		uint8_t readback = rdReg(reg);
		if (readback != dat) {
			pc.printf("\033[0;31m"); 
			pc.printf("%X, %X....reads %X, %X\n\r", reg, dat, reg, readback);
		}
		else {
			//readback in red if the register did not contain the value i set it to. 
			pc.printf("\033[0m"); 
			pc.printf("%X, %X\n\r", reg, dat);
		}
		*/
}

char OV7670::rdReg(uint8_t reg) {
		char val = reg;
	
		_i2c.write(camAddr_WR, &val, 1);
		
		int ret = _i2c.read(camAddr_RD, &val, 1);
		if(!ret) {
			wait_ms(50);
			return val;
		}
		else pc.printf("Failed\n\r");
		return 0;
}

/*
void wrColourTable(void){
	//Write colour table to the file
	for(int i=0;i<256;i++)
	{
		unsigned char c = (unsigned char)i;
		fputc(c, fp);
		fputc(c, fp);
		fputc(c, fp);
		fputc(0x00, fp);
	}	
}
*/

/*
int OV7670::base64_encode(const unsigned char* data,
                    size_t input_length,
                    char* encoded_data) {

  int output_length = 4 * ((input_length + 2) / 3);

	//encoded_data = malloc(output_length + 1);
  //if (encoded_data == NULL) return NULL;

  for (int i = 0, j = 0; i < input_length;) {

    uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
    uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
    uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
  }

  for (int i = 0; i < mod_table[input_length % 3]; i++)
    encoded_data[output_length - 1 - i] = '=';

  return output_length;
}
*/

//bool OV7670::storeImg(const char* uniqueIdentifier, int photoIndex){
bool OV7670::storeImg(){
//	//Open file and write data
	mkdir(SD_DIR, 0777);
	
	fp = fopen("/sd/images/latest.jpg","wb"); 
	if(fp == NULL)
	{
		pc.printf("File could not be opened.\n\r");
		return 0;
	}
	
	//write the pixels to the SD card
	uint8_t templast = 0;
	uint8_t temp = 0;
	
	for (unsigned int i=0; i<sizeof(_pixels); i++)
	{		
		templast = temp;
		temp = _pixels[i];
		fputc(_pixels[i], fp);
		if((templast == 0xFF) && (temp == 0xD9))
			break;
	}
	
	
	fclose(fp);
	
	pc.printf("File successfully written\n\r"); //Commented out to test sending image over serial to processing
	return 1;	
}




