/* This file is a definition of all structures os ASDU part 
of IEC-60870-5-104 protocol
*/







/* Definition of "Identification Data Block". "Identification Data Block" is consist of:
		TYPE IDENTIFICATION (1 byte)
		QUALIFIER OF VARIABLE STRUCTURE (1 byte)
		CAUSE OF TRANSMISSION (1 or 2 byte)
		GENERAL ADDRESS OF ASDU (1 or 2 byte)
*/ 

//TYPE IDENTIFICATION 

#define M_SP_NA_1				1		// Single-point information
#define M_DP_NA_1				3		// Double-point information
#define M_ST_NA_1				5		// Step position information
#define M_BO_NA_1				7		// Bitstring of 32 bit
#define M_ME_NA_1				9		// Measured value, normalized value
#define M_ME_NC_1				13	// Measured value, short floating point value		
#define M_SP_TB_1				30	// Single-point information with time tag CP56Time2a
#define M_DP_TB_1				31	// Double-point information with time tag CP56Time2a
#define M_ST_TB_1				32	// Step position information with time tag CP56Time2a
#define M_ME_TD_1				34	// Measured value, normalized value with time tag CP56Time2a
#define M_ME_TF_1				36	// Measured value, short floating point value with time tag CP56Time2a
#define M_IT_TB_1				37	// Integrated totals value with time tag CP56Time2a
#define C_SC_NA_1				45	// Single command
#define C_DC_NA_1				46	// Double command
#define C_RC_NA_1				47	// Regulating step command
#define C_SE_NA_1				48	// Set point command, normalised value
#define C_BO_NA_1				51	// Bitstring of 32 bit
#define C_SC_TA_1				58	// Single command with time tag CP56Time2a
#define C_DC_TA_1				59	// Double command with time tag CP56Time2a
#define M_EI_NA_1				70	// End of initialization
#define C_IC_NA_1				100	// Interrrogation command
#define C_CI_NA_1				101	// Counter interrrogation command
#define C_CS_NA_1				103	// Clock syncronization command
#define C_TS_NB_1				104	// Test command
#define C_RP_NC_1				105	// Reset process command

// QUALIFIER OF VARIABLE STRUCTURE

struct QualifierVariableStructute {  //VariableStructureQualifier
	
	unsigned char Number; // number of Informational Objects
	unsigned char SQ; // Single <0> or Series <1> of Objects

};

// CAUSE OF TRANSMISSION: define causes

#define COT_PERIODIC								1
#define COT_BACKGROUND							2
#define COT_SPONTANEOUS							3
#define COT_INITIALISED							4
#define COT_REQUEST									5
#define COT_ACTIVATION							6
#define COT_ACTIVATIONCONFIRM				7
#define COT_DEACTIVATION						8
#define COT_DEACTIVATIONCONFIRM			9
#define COT_ACTIVATIONTERMINATION		10
#define COT_REMOTECOMMAND						11
#define COT_LOCALCOMMAND						12
#define COT_FILETRANSFER						13
#define COT_INTERROGATION						20

// CAUSE OF TRANSMISSION: define structure 

struct CauseOfTransmission {
	
	unsigned char cause; // <0..63> cause number
	unsigned char confim; // <0> - positive , <1> - negative 
	unsigned char test; // <0> - not a test, <1> - test
	unsigned char initiator; // number of initiating address

};

// GENERAL ADDRESS OF ASDU

/* Definition of "OBJECT OF INFORMATION". "OBJECT OF INFORMATION" is consist of:
		ADRRESS OF THE OBJECT OF INFORMATION (1,2 OR 3 BYTES) INFORMATION OBJECT ID
		FRAMEWORK OF ELEMENT OF INFORMATION 
		TIMESTAMP

*/ 

// FRAMEWORK OF ELEMENT OF INFORMATION: define of element of information

// Single-Point Information	
struct SIQ {
	
	unsigned char SPI :1; // <0> - OFF, <1> - ON
	unsigned char RES :3; // RESERV
	unsigned char BL  :1;  // <0> - no block, <1> - block
	unsigned char SB  :1;  // <0> - no substitution (replacement), <1> - substitution
	unsigned char NT  :1;  // <0> - relevance value, <1> - irrelevance value
	unsigned char IV  :1;  // <0> - valid value, <1> - invalid value
	
};

// Double-point Information
struct DIQ
{
	unsigned char DPI :2; // <0> - Indefined state/Intermidiate state, <1> - OFF, <2> - ON, <3> - Indefined State
	unsigned char RES :2; // RESERV
	unsigned char BL  :1;  // <0> - no block, <1> - block
	unsigned char SB  :1;  // <0> - no substitution (replacement), <1> - substitution
	unsigned char NT  :1;  // <0> - relevance value, <1> - irrelevance value
	unsigned char IV  :1;  // <0> - valid value, <1> - invalid value
};

// Quality control 
struct QDS
{
	unsigned char OV		: 1; // Overflow
	unsigned char RES		: 3;
	unsigned char BL		: 1; // Blocked
	unsigned char SB		: 1; // Substituted
	unsigned char NT		: 1; // Not topical
	unsigned char IV		: 1; // Invalid
};
	
// Value with transient state indication
struct VTI
{
	unsigned int Value			: 7;
	unsigned int Transient	: 1;
};



	


