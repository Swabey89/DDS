#ifndef __SIM800H__
#define __SIM800H__
#include <string>
#include "main.h"

//#define FILESIZE 102400 //was 103836
#define FILESIZE 25600

#define SEND_RETURN 1
#define OMIT_RETURN 0
#define WAIT_REPLY 1
#define IGNORE_REPLY 0
#define ECHO 1
#define DONT_ECHO 0

#define DEBUG 1

extern Serial pc;
extern FILE* fp;
extern char directory[30];
extern char fileName[20];
extern BusOut led;
extern string id;


//`static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
//`                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
//`                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
//`                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
//`                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
//`                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
//`                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
//`                                '4', '5', '6', '7', '8', '9', '+', '/'};

//static int mod_table[] = {0, 2, 1};

const char b64_alphabet[] = 	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
				"0123456789+/";


class Sim800H 
{
	public:
		Sim800H(PinName TX, PinName RX, int baud, PinName rst);
		~Sim800H(void);
		string  getTime(void);
		string getReply(const char* expected, unsigned short timeout);
		bool sendFTP(const char* dir, const char* filename);
		bool sendEXTFTP(const char* dir, const char* filename);
		bool sendBat(const unsigned short level);
		void simInit(void);
		void standby(void);
		bool wakeup(void);
		void togglePower(void);
//		bool powerStatus(void);
		int getBattery(void);
		string getIdentifier();
	
	private:
		//DigitalOut* _led;
		DigitalOut _rst;
		//DigitalIn* _ps;
		Serial _sim;
		string _cmdResponse;
		string _ipAddress;	
		string simSendCmd(const char* command, const char* expected, unsigned short timeout, bool AppendReturn = true, bool waitReply = true, bool echoCmd = true);
		unsigned short b64_encode(const unsigned char*, unsigned short num, char* out);		
//		int base64_encode(const unsigned char *data,
//                    size_t input_length,
//                    char* encoded_data);
		unsigned short clearBuffer(void);	
		void simReset(void);		
		bool gprsInit(void);	
		bool FTPInit(const char* fname);
		bool _gprsSet;
		
};	


#endif
