#include "APDU.h"

APDU::APDU()
{
	apci = new APCI();
	asdu = new ASDU();
	clear();
}

APDU::~APDU()
{
	delete apci;
	delete asdu;	
}

void APDU::clear()
{
	apci->clear();
	asdu->clear();
}

int APDU::get(unsigned char* data)
{
	if (!apci->valid())
		return 0;
	apci->get(data);
	if (apci->format==I_FORMAT)
		asdu->get(&data[6]);
	return apci->length+2;
}

bool APDU::set(unsigned char* data)
{
	apci->set(data);
	if (!apci->valid())
		return false;
	if (apci->format==I_FORMAT)
		asdu->set(&data[6]);
	return true;
}

bool APDU::valid()
{
	if (!apci->valid())
		return false;
	return asdu->valid();
}

void APDU::addIO(int address)
{
	InformationObject io;
	io.objectAdr = address;
	int len=asdu->addIO(io);
	apci->length+=len;
}

void APDU::addIO(InformationObject& inf)
{
	int len=asdu->addIO(inf);
	apci->length+=len;
}

void APDU::setAPCI(int format)
{
	apci->format=format;
}

void APDU::setDUI(int common, int ident, int cause)
{
	asdu->DUI.typeIdent=ident;
	asdu->DUI.cause.cause=cause;
	asdu->DUI.commonAdrASDU=common;
	apci->length+=6;
}

