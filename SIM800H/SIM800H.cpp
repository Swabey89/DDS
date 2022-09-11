#include "mbed.h"
#include <string>
#include "SIM800H.h"
#include "SDFileSystem.h"
#include "math.h" //This is for ceiling

Sim800H::Sim800H(PinName TX, PinName RX, int baud, PinName rst) : _sim(TX, RX), _rst(rst){	
	_sim.baud(115200);
	this->_cmdResponse = "";
	this->_ipAddress = "";	
	_gprsSet = false;	
	_rst = 1;
}

Sim800H::~Sim800H(void){	
}

string Sim800H::getTime(void){
	return simSendCmd("AT+CCLK?", "CCLK", 5);	
}

void Sim800H::simInit(void){

	//Test
	wakeup();
	
	//Set band. Waiting for SMS Ready
	simSendCmd("AT+CBAND=\"ALL_BAND\"", "SMS Ready", 10);
	
	//Set baudrate to autobauding, was 57600
	simSendCmd("AT+IPR=0", "OK", 5);
	
	//Disable echoing
	simSendCmd("ATE0", "OK", 5);	
	
	//Turn on local time stamping
	simSendCmd("AT+CLTS=1", "OK", 5);
	
	//Store the profile
	simSendCmd("AT&W","OK",5);
	
	//Reset	
	simSendCmd("AT+CFUN=0", "OK", 10);
//	_rst = 0;
//	wait(0.5);
//	_rst = 1;
//	wait(20);
	simSendCmd("AT+CFUN=1", "Call Ready", 10);	
	//Get time
	//simSendCmd("AT+CCLK?", "OK", 5);	
	
	pc.printf("SIM800H Initialised\n\r");
	//Im adding to try and remove weird behaviour after init
	//wait(10);
	clearBuffer();


}

bool Sim800H::FTPInit(const char* fname) {
	//Set the CID to 1
	simSendCmd("AT+FTPCID=1", "OK", 10);
	//Server Address
	simSendCmd("AT+FTPSERV=\"77.72.0.126\"", "OK", 10);
	//Login Username
	simSendCmd("AT+FTPUN=\"dds@dds.kineticjam.co.uk\"", "OK", 10);
	//Login Password
	simSendCmd("AT+FTPPW=\"x7KgpFS01SXg\"", "OK", 10);

	//Create the directory
	string dirstring = "AT+FTPGETPATH=\"/devices/" + id + "/\"";
       	simSendCmd(dirstring.c_str(), "OK", 10);
	simSendCmd("AT+FTPMKD", "+FTPMKD", 75);

	//Set directory
	string putstring = "AT+FTPPUTPATH=\"/devices/" + id + "/\"";
	simSendCmd(putstring.c_str(), "OK", 10);

	//Set filename
	char cmd[40];
	strcpy(cmd, "AT+FTPPUTNAME=\"");
	strcat(cmd, fname);
	strcat(cmd, "\"\0");
	simSendCmd(cmd, "OK", 10);

	//Initiate extended put
	_cmdResponse = simSendCmd("AT+FTPEXTPUT=1", "OK", 75);

	if(this->_cmdResponse == "ERROR") return 0;
	else return 1;		

}

bool Sim800H::wakeup(void){
	//pc.printf("in wake \n\r");

	//Test
//	_rst = 0;
//	wait(5);
//	_rst=1;
//	_key = 0;
//	if(powerStatus()) return 1;	
//	while(!powerStatus()){
//		togglePower();		
	//	wait(1);
////	}
//	Uncommenting these
	//pc,printf("waiting 1 \n\r");
//	getReply("DST: 1", 20);	// - WHAT WAS THIS FOR? REMOVED TO SHORTEN
//	SETUP TIME (SEE ONENOTE)

	//taking out \r\n since adding the || '\r' in getResponse()
	while (_cmdResponse != "OK\r\n") { //Changed from OK\r\n after changes in getresponse
		_cmdResponse = simSendCmd("AAAAAAAT", "OK", 3);
		//pc.printf("%s\n\r", _cmdResponse);
	}
	return 1;	
}

//added out as unsigned
unsigned short Sim800H::b64_encode(const unsigned char* in, unsigned short num, char* out){
	int i = 0;
	memset(out, '\0', 5);
	switch(num){
		case (1):
			out[0] = b64_alphabet[(in[0]>>2)%64];
			out[1] = b64_alphabet[((in[0]&0x03) << 4)%64]; //test to see if byte 2 has 4 LSBs = 0
			i = 2; //was 1
			break;
		case (2):
			out[0] = b64_alphabet[(in[0]>>2)%64];
			out[1] = b64_alphabet[(((in[0]&0x03) << 4) | (in[1]>>4))%64];
			out[2] = b64_alphabet[((in[1]&0x0F) << 2)%64]; //Test if byte 3 has 2 LSBs = 0
			i = 3; //was 2
			break;
		case(3):
			out[0] = b64_alphabet[(in[0]>>2)%64];
			out[1] = b64_alphabet[(((in[0]&0x03) << 4) | (in[1]>>4))%64];
			out[2] = b64_alphabet[(((in[1]&0x0F) << 2) | (in[2]>>6))%64];
			out[3] = b64_alphabet[((in[2]&0x3F))%64];
			i = 4;
			break;
	}
	return i;
}


bool Sim800H::gprsInit(void){	
	//Set up GPRS connection
		//simSendCmd("AT+CBAND?", "OK", 5);
	
	//simSendCmd("AT+CBAND=DCS_MODE", "OK", 5);

	//simSendCmd("at+sapbr=0,1", "OK", 65);
	//simSendCmd("at+cgatt=1", "OK", 10);
	/*
	simSendCmd("at+sapbr=3,1,\"CONTYPE\",\"GPRS\"", "OK", 5);
	simSendCmd("at+sapbr=3,1,\"APN\",\"payandgo.o2.co.uk\"", "OK", 5);;
	simSendCmd("at+sapbr=3,1,\"USER\",\"payandgo\"", "OK", 5);
	simSendCmd("at+sapbr=3,1,\"PWD\",\"password\"", "OK", 5);
	*/
	/*
	simSendCmd("at+sapbr=3,1,\"CONTYPE\",\"GPRS\"", "OK", 5);
	simSendCmd("at+sapbr=3,1,\"APN\",\"data.uk\"", "OK", 5);;
	simSendCmd("at+sapbr=3,1,\"USER\",\"user\"", "OK", 5);
	simSendCmd("at+sapbr=3,1,\"PWD\",\"one2one\"", "OK", 5);
	*/
	simSendCmd("at+sapbr=3,1,\"CONTYPE\",\"GPRS\"", "OK", 5);
	simSendCmd("at+sapbr=3,1,\"APN\",\"everywhere\"", "OK", 5);;
	simSendCmd("at+sapbr=3,1,\"USER\",\"eesecure\"", "OK", 5);
	simSendCmd("at+sapbr=3,1,\"PWD\",\"secure\"", "OK", 5);
	
	//Wait to be on the networknetwork yet
	int nettries = 0;
	size_t first;
	size_t last;
	string stat;
	while(nettries < 10)
	{
		this->_cmdResponse = simSendCmd("AT+CGREG?", "OK", 5);
		first = this->_cmdResponse.find(",");
		stat = this->_cmdResponse.substr(first+1, 1);
		if (stat == "1") 
		{
			pc.printf("Network conneciton successful\n\r");
			break;
		}
		else
		{
			pc.printf("Waiting for network connection. Retrying...\n\r");
			nettries++;
			wait(5);
		}
	}

	//pc.printf("Status: %s\n\r", stat.c_str());



		//Need to add check that we are ready on network
		simSendCmd("at+sapbr=1,1", "OK", 85);
	//Request GPRS IP, check if correctly set
	//this->_cmdResponse = simSendCmd("at+sapbr=2,1", "SAPBR", 10); 
	this->_cmdResponse = simSendCmd("at+sapbr=2,1", "OK", 10); 
	first = this->_cmdResponse.find("\"");
	last = this->_cmdResponse.find("\"", first+1);
		
	if (this->_cmdResponse == "ERROR" || first == string::npos || last == string::npos) 
	{
		pc.printf("GPRS SETUP ERROR\n\r");
		_gprsSet = false;
		return 0;
	}
	else
	{
		this->_ipAddress = this->_cmdResponse.substr(first, (last-first)-1);
		pc.printf("GPRS SETUP WITH IP: %s\r\n", this->_ipAddress.c_str());
		_gprsSet = true;
		//Test to try and get it working
		//wait(10);
		clearBuffer();	
		return 1;
	}

	//test
}

string Sim800H::simSendCmd(const char* command, const char* expected, unsigned short timeout, bool AppendReturn, bool waitReply, bool echoCmd){
	//Echo the command
	if(echoCmd) pc.printf("%s\r\n", command); //was %s
	//Clear any characters in the buffer
	clearBuffer();
	//Send the command, return the size of the command
	AppendReturn ? this->_sim.printf("%s\r\n", command) : this->_sim.printf("%s", command); //both were %s
	if(!waitReply) return command;
	this->_cmdResponse = getReply(expected, timeout);
	return this->_cmdResponse;
}

unsigned short Sim800H::clearBuffer(void){
	//Flush the buffer by reading all characters
	unsigned short i = 0;
	//Read characters and return number flushed
	while(this->_sim.readable()) {
		char c = this->_sim.getc();
		i++;
	}
	return i;
}

std::string Sim800H::getReply(const char* expected, unsigned short timeout){
	Timer t;
	string out = "";
	char rep[150];
	int index = 0;
	bool strfound = false;
	bool crlf = false;
	bool success = false;

	//Size to be reduced when stable
	memset(rep, '\0', 150); 
	t.start();
	//Try and find a reply within timeout period
	while(t.read() < timeout && !success) {
		if(_sim.readable()){
	//Get the character, dont do anything until first \n is found
	rep[index] = _sim.getc();
	if(!crlf) {if(rep[index] == '\n') crlf = true;}
	else {
		//Look for the expected reply. Once found, look for the final \n
		if (!strfound) {
			rep[index+1] = '\0';
			out = rep;
			size_t num = out.find(expected);
			if (num != string::npos) {
				strfound = true;

			}
		}
		else if(rep[index] == '\n') {
			//Expected reply is found successfully
			success = true;
		}
		index++;
	}             
}      
		
	}   
					
	t.stop();
	rep[index] = '\0';
	//if(!success) strcpy(rep, "ERROR");
	if(DEBUG) pc.printf("DEBUG: %s\r\n", rep);
	if(!success) strcpy(rep, "ERROR");
	out = rep;
	return out;	
}

	
void Sim800H::simReset(void) {
	_rst = !_rst;
	wait_ms(100);
	_rst = !_rst;
	
	this->clearBuffer();
	getReply("DST: 1", 40);	
	this->clearBuffer();
}


bool Sim800H::sendEXTFTP(const char* dir, const char* filename){

	//Initialise GPRS
	if(!gprsInit()) return 0;

	//Set up directory to access image on SD card
	mkdir(dir, 0777);
	char filedir[50];
	strcpy(filedir, dir);
	strcat(filedir, filename);
	
//	pc.printf("%s\n\r", filedir);
	
	fp = fopen(filedir, "rb"); //added w for change file name
	if(fp == NULL) {
		pc.printf("Could not open file for reading\n\r");
		return 0;
	}

	fclose(fp);

	//Get GSM time
	this->_cmdResponse = simSendCmd("AT+CIPGSMLOC=2,1", "OK", 10);
	size_t begin = _cmdResponse.find_first_of(",");
	string gsmtime = _cmdResponse.substr(begin+1, 19);
	//Replace all non alphanumerical characters with "_"
	for(int i=4; i<=16; i+=3) gsmtime.replace(i,1,"_");
	pc.printf("GSM TIME: %s\n\r", gsmtime.c_str());

	//Change filename and get new file pointer
	gsmtime += ".jpg";
	char newFileDir[50];
	strcpy(newFileDir, dir);
	strcat(newFileDir, gsmtime.c_str());
	rename(filedir, newFileDir);
	fp = fopen(newFileDir, "rb");

	//Initialise the FTP connection	
	if(!FTPInit(gsmtime.c_str()))
	{
		fclose(fp);	
		return 0;
	}

	//Open the file and determine the filesize
	fseek(fp,0,SEEK_END);
	long int size = ftell(fp);
	long int filesize = ((size*4)/3);
	if(size%3 != 0) filesize++;
	fseek(fp, 0, SEEK_SET);
	
	//Use FTPEXTPUT 2 to begin intialiase data transfer to SIM800 RAM. Wait for OK
	char cmd[40] = "AT+FTPEXTPUT=2,0,";
	char cSize[5];
	snprintf(cSize, 5, "%d", filesize); //Can combine with above 2 lines?
	strcat(cmd, cSize);
	strcat(cmd, ",40000");
	simSendCmd(cmd, "FTPEXTPUT", 2); //This will always timeout until getResponse() is altered

	//Send data encoded in base64 over UART
	unsigned char filestr[4] = {0};
	char outstr[5] = {0};
	unsigned short ret = 0;
	unsigned short conv = 0;

	do {
		memset(filestr, '\0', 4);
		ret = fscanf(fp, "%c%c%c", &filestr[0], &filestr[1], &filestr[2]);
		conv = b64_encode(filestr, ret, outstr);
		filesize -= conv;
		if(filesize) simSendCmd(outstr, "NA", 0, OMIT_RETURN, IGNORE_REPLY, ECHO);
		else simSendCmd(outstr, "OK", 10, OMIT_RETURN, WAIT_REPLY, ECHO);
	} while(filesize!=0);
	
	//Use FTPEXTPUT 1 to send data. Successful transmission will return "+FTPPUT: 1,0"
	simSendCmd("AT+FTPPUT=1", "+FTPPUT: 1,0", 75);
	simSendCmd("AT+FTPEXTPUT=0", "OK", 75);
	simSendCmd("AT+SAPBR=0,1", "OK", 65);
	
	
	return 1;
}

void Sim800H::standby(void) {	
//	while(powerStatus()) 
//	{
		togglePower();
		wait_ms(100);
//	}	
	_gprsSet = false;
}

//This needs to be removed, key button doesn't exists on the coreboards
void Sim800H::togglePower(void) {
	//*_key = 1;
	wait_ms(2000);
	//_key = 0;
}

//bool Sim800H::powerStatus(void){
//	return _ps->read();
//}

int Sim800H::getBattery(void) {
	simSendCmd("AT+CBC","OK",5);
	size_t first = _cmdResponse.find(",");
	size_t last = _cmdResponse.find_last_of(",");
	
	if(first != string::npos && last != string::npos)
	{
		string sub = _cmdResponse.substr(first+1, (last-first)-1);
		pc.printf("Sub: %s\n\r", sub.c_str());
		return atoi(sub.c_str());
	}
	return 0;
}

bool Sim800H::sendBat(const unsigned short level) {
	//Send new one with updated time
	if(!gprsInit()) return 0;
	
	if(!FTPInit("bat.txt")) return 0;
	
	size_t numstart = this->_cmdResponse.find_last_of(",");
	size_t numstop = this->_cmdResponse.find('\r', numstart+1);
	if(numstart == string::npos || numstop == string::npos) return 0;
	string sub = _cmdResponse.substr(numstart+1, ((numstop-numstart)-1)); //Pick out the number
	if(atoi(sub.c_str()) < 3) return 0;
	
	simSendCmd("AT+FTPPUT=2,3", "+FTPPUT: 2,3", 10);	
	char val[4];
	snprintf(val, 4, "%03d", level);
	simSendCmd(val,"+FTPPUT: 1",10); //checks that all was good here
	simSendCmd("AT+FTPPUT=2,0", "+FTPPUT: 1,0", 60);
	return 1; //improve
}

string Sim800H::getIdentifier(void) {
	return simSendCmd("AT+CCID", "OK", 10);
}
