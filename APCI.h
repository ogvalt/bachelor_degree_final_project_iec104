#define	STARTHEAD		0x68;

#define I_FORMAT		0x00
#define S_FORMAT		0x01
#define U_FORMAT		0x03
#define STARTDTACT	0x04
#define STARTDTCON	0x08
#define STOPDTACT		0x10
#define STOPDTCON		0x20
#define TESTFRACT		0x40
#define TESTFRCON		0x80

class APCI
{
	public:
		unsigned char start;			
		unsigned char length;
		unsigned char format;
		unsigned char func;
		unsigned char ssn;
		unsigned char rsn;
		APCI();
		virtual ~APCI();
		void clear();
		unsigned char get(unsigned char* data); //returns only err code
<<<<<<< HEAD
		void set(unsigned char* data);
=======
		void set(const unsigned char* data);
>>>>>>> 0b7e00f4a8489eb33fad1bf1649051befee613c1
		bool valid();
};







/* yuriy: code from example
#define I_FORMAT		0x00
#define S_FORMAT		0x01
#define U_FORMAT		0x03
#define STARTDTACT	0x04
#define STARTDTCON	0x08
#define STOPDTACT		0x10
#define STOPDTCON		0x20
#define TESTFRACT		0x40
#define TESTFRCON		0x80
<<<<<<< HEAD
=======

>>>>>>> 0b7e00f4a8489eb33fad1bf1649051befee613c1
class APCI{
public:
BYTE start;
int length;
int format;
int func;
int ssn;
int rsn;
APCI();
virtual ~APCI();
void clear();
int get(BYTE* data);
void set(const BYTE* data);
bool valid();
};
*/
<<<<<<< HEAD

=======
>>>>>>> 0b7e00f4a8489eb33fad1bf1649051befee613c1
