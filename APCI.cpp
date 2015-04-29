#include "APCI.h"
#include <string.h>

using namespace std;

APCI::APCI()
{
	clear();
}

APCI::~APCI()
{
}

void APCI::clear()
{
	start = STARTHEAD;
	length = 4;
	format = U_FORMAT;
	func = 0;
	ssn = 0;
	rsn = 0;
}

unsigned char APCI::get(unsigned char* data) //moving inf. from object to data[]
{
	if (start != 0x68)
		return 0;
	memset(data, 0, 6);
	data[0] = start;
	data[1] = length;

	switch (format)
	{
	case I_FORMAT:
		data[2] = (ssn & 0x7f) << 1;
		data[2] &= 0xfe;
		data[3] = (ssn >> 7);
		data[4] = (rsn & 0x7f) << 1;
		data[4] &= 0xfe;
		data[5] = (rsn >> 7);
		break;
	case S_FORMAT:
		data[2] = 1;
		data[4] = (rsn & 0x7f) << 1;
		data[4] &= 0xfe;
		data[5] = (rsn >> 7);
		break;
	case U_FORMAT:
		data[2] = func | 0x03;
		break;
	default:
		return 0;
	}
	return 6;
}

void APCI::set(unsigned char* data) //fill the object with inf. from data[]
{
	start = data[0];
	length = data[1];
	if (data[2] & 0x01)
		format = data[2] & 0x03;
	else
		format = I_FORMAT;
	switch (format)
	{
	case I_FORMAT:
		func = 0;
		ssn = 0x80 * data[3] + (data[2] >> 1);
		rsn = 0x80 * data[5] + (data[4] >> 1);
		break;
	case S_FORMAT:
		func = 0;
		ssn = 0;
		rsn = 0x80 * data[5] + (data[4] >> 1);
		break;
	case U_FORMAT:
		func = data[2] & 0xfc;
		break;
	}
}

bool APCI::valid()
{
	if (start != 0x68)
		return false;
	switch (format)
	{
	case I_FORMAT:
		if ((length<6) || (length>253))
			return false;
		break;
	case S_FORMAT:
		if (length != 4)
			return false;
		if (ssn != 0)
			return false;
		break;
	case U_FORMAT:
		if (length != 4)
			return false;
		break;
	default:
		return false;
	}
	return true;
}
