#include "iec104.h"
#include "stdio.h"

void print(const char* str, unsigned char* data, int size){
	printf("%s",str);
	for (int i=0; i<size; i++){
		printf("x%hhX ",data[i]);
	}
	printf("\n");
}

void testfunc(unsigned char* data)
{
	APDU *apdu1 = new APDU();
	
	print("INcoming data: ",data, data[1]);
	
	apdu1->set(data);

	apdu1->apci->func <<= 1;// | 0b00001000 & 0b11111011;
	
	apdu1->get(data);
	
	print("OUTcoming data: ",data, data[1]);
}


