#include "APCI.h"
#include "ASDU.h"

class APDU
{
public:
	APCI *apci;
	ASDU *asdu;
	APDU();
	virtual ~APDU();
	void clear();
	int get(unsigned char* data);
	bool set(unsigned char* data);
	bool valid();
	void addIO(int address);
	void addIO(InformationObject& inf);
	void setDUI(int common, int ident, int cause);
	void setAPCI(int format);
};

