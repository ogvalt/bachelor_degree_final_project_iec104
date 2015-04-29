#include "ASDU.h"

using namespace std;

ASDU::ASDU()
{
	clear();
}

ASDU::~ASDU()
{
}

bool ASDU::valid(){
	return true;
}

void ASDU::clear()
{
	DUI.clear();
	IO.clear();
}

int ASDU::get(unsigned char* data)
{
	int index = 0;
	
	
	// DATA UNIT IDENTIFIER
	data[index++] = DUI.typeIdent;
	data[index++] = (DUI.qualifier.SQ<<7)|(DUI.qualifier.Number);
	data[index++] = (DUI.cause.test<<7)|(DUI.cause.confim<<6)|(DUI.cause.cause);
	data[index++] = DUI.cause.initiator;
	data[index++] = DUI.commonAdrASDU&0xff;
	data[index++] = (DUI.commonAdrASDU>>8);
	
	// INFORMATION OBJECT
	
	vector<InformationObject>::iterator it;
	it = IO.begin();
	
	while (it!=IO.end())
	{
			if ((it==IO.begin()) || !DUI.qualifier.SQ)
			{
				memcpy(&data[index], &it->objectAdr, 3);
				index+=3;
			}
			switch (DUI.typeIdent)
			{
				case M_SP_NA_1:
					memcpy(&data[index++],&it->siq,1);
					break;
				case M_DP_NA_1:
					memcpy(&data[index++],&it->diq,1);
					break;
				case M_ME_NA_1:
					memcpy(&data[index],&it->nva,2);
					index+=2;
					memcpy(&data[index++],&it->qds,1);
					break;
				case M_ME_NC_1:
					memcpy(&data[index],&it->value,4);
					index+=4;
					memcpy(&data[index++],&it->qds,1);
					break;
//				case M_SP_TB_1:
//					memcpy(&data[index++],&it->siq,1);
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
//				case M_DP_TB_1:
//					memcpy(&data[index++],&it->diq,1);
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
//				case M_ME_TD_1:
//					memcpy(&data[index],&it->nva,2);
//					index+=2;
//					memcpy(&data[index++],&it->qds,1);
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
//				case M_ME_TF_1:
//					memcpy(&data[index],&it->value,4);
//					index+=4;
//					memcpy(&data[index++],&it->qds,1);
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
				case C_SC_NA_1:
					memcpy(&data[index++],&it->sco,1);
					break;
				case C_DC_NA_1:
					memcpy(&data[index++],&it->dco,1);
					break;
//				case C_SC_TA_1:
//					memcpy(&data[index++],&it->sco,1);
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
//				case C_DC_TA_1:
//					memcpy(&data[index++],&it->dco,1);
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
				case M_EI_NA_1:
					memcpy(&data[index++],&it->coi,1);
					break;
				case C_IC_NA_1:
					data[index++]=it->qoi;
					break;
				case C_CI_NA_1:
					data[index++]=it->qcc;
					break;
//				case C_CS_NA_1:
//					memcpy(&data[index],&it->cp56time,7);
//					index+=7;
//					break;
			};
		++it;
	}
	return index;
}

void  ASDU::set (unsigned char * data)
{
	DUI.typeIdent = data[0];
	DUI.qualifier.Number = data[1]&0x7f;
	DUI.qualifier.SQ = data[1]>>7;
	DUI.cause.cause = data[2]&0x3F;
	DUI.cause.confim = (data[2]>>6)&0x01;
	DUI.cause.test = data[2]>>7;
	DUI.cause.initiator = data[3];
	DUI.commonAdrASDU = data[4] + data[5]*256;
	
	int i, index = 6;
	InformationObject inf;
	
	for (i=0; i<DUI.qualifier.Number; i++)
	{
		if ((i==0) || (DUI.qualifier.SQ==0))
		{
			inf.objectAdr =  data[index++];
			inf.objectAdr += data[index++]*0x100;
			inf.objectAdr += data[index++]*0x10000;
		}
		else
		{
			inf.objectAdr = IO[0].objectAdr;
		}
		
		switch (DUI.typeIdent)
		{
			case C_SC_NA_1:
				memset(&inf.sco,data[index++],1);
				break;
			case C_DC_NA_1:
				memset(&inf.dco,data[index++],1);
				break;
//			case C_SC_TA_1:
//				memset(&inf.sco,data[index++],1);
//				memcpy(&inf.cp56time,&data[index],7);
//				index+=7;
//				break;
//			case C_DC_TA_1:
//				memset(&inf.dco,data[index++],1);
//				memcpy(&inf.cp56time,&data[index],7);
//				index+=7;
//				break;
			case C_IC_NA_1:
				inf.qoi=data[index++];
				break;
			case C_CI_NA_1:
				inf.qcc=data[index++];
				break;
//			case C_CS_NA_1:
//				memcpy(&inf.cp56time,&data[index],7);
//				index+=7;
//				break;
			default:
				// Ikke st?ttet ident
				return;
		} 
		IO.push_back(inf);
	}	
}

int ASDU::addIO(InformationObject& i)
{
	int len=0;
	IO.push_back(i);
	DUI.qualifier.Number++;
	switch (DUI.typeIdent)
	{
		case M_SP_NA_1:
		case M_DP_NA_1:
		case C_SC_NA_1:
		case C_DC_NA_1:
		case M_EI_NA_1:
		case C_IC_NA_1:
		case C_CI_NA_1:
			len=4;
			break;
		case M_ME_NA_1:
			len=6;
			break;
		case M_ME_NC_1:
			len=8;
			break;
		case C_CS_NA_1:
			len=10;
			break;
		case M_SP_TB_1:
		case M_DP_TB_1:
		case C_SC_TA_1:
		case C_DC_TA_1:
			len=11;
			break;
		case M_ME_TD_1:
			len=13;
			break;
		case M_ME_TF_1:
			len=15;
			break;
	};
	if ((DUI.qualifier.SQ==1) && (DUI.qualifier.Number>1))
		len-=3;
	return len;
}






