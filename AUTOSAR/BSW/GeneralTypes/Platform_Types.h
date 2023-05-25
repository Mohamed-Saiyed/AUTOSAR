/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Platform_Types.h                      						 **
**	                                                      						 **
**	VERSION		: 	1.0.0                                 						 **
**                                                        						 **
**	DATE		:	2021-3-22                             						 **
**                                                        						 **
**	PLATFORM	:	TIVA C      		                  						 **
**																				 **
**  VARIANT  	: 	NA                                                           **
**                                                        						 **
**	AUTHOR		:  	MohamedSayed                          						 **
**                                                         						 **
**	VENDOR		: 	NA                                   						 **
**                                                        						 **
**	                                                      						 **
**	DESCRIPTION : AUTOSAR Standard Platform Types      							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_PlatformTypes, AUTOSAR Release 4.3.1          **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

/*****************************************************************/
/*				        Macros Definition       		         */
/*****************************************************************/

/* Platform types Vendor ID */
#define PLATFORM_VENDOR_ID					(0x40u)

/* Platform types module ID */
#define PLATFORM_MODULE_ID					(199u)


/*	Moudle Version	1.0.0 */
#define PLATFORM_SW_MAJOR_VERSION			(0x01u)
#define PLATFORM_SW_MINOR_VERSION			(0x00u)
#define PLATFORM_SW_PATCH_VERSION			(0x00u)

/* Autosar version 4.3.1 */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION	(0x04u)
#define PLATFORM_AR_RELEASE_MINOR_VERSION	(0x03u)
#define PLATFORM_AR_RELEASE_PATCH_VERSION	(0x01u)

/* register width of the CPU definitions*/
#define CPU_TYPE_8			(8u)
#define CPU_TYPE_16			(16u)
#define CPU_TYPE_32			(32u)
#define CPU_TYPE_64			(64u)

/* Used CPU register width*/	
#define CPU_TYPE			 CPU_TYPE_32

/* bit order definitions*/
#define MSB_FIRST			(0u)
#define LSB_FIRST			(1u)

/* CPU Bit-Order*/
#define CPU_BIT_ORDER		 MSB_FIRST

/* Byte order definitions*/
#define	HIGH_BYTE_FIRST		(0u)
#define LOW_BYTE_FIRST		(1u)

/* CPU Byte order*/
#define CPU_BYTE_ORDER		 HIGH_BYTE_FIRST

/* TRUE , FALSE definitions for boolean type*/
#ifndef FALSE
#define FALSE	0
#endif
#ifndef TRUE
#define TRUE	1
#endif

/*****************************************************************/
/*				        Types Definition        		         */
/*****************************************************************/

/* A bit-width type definition, TRUE = 1 , FLASE = 0*/
typedef unsigned char 		 	boolean;
	
/* 8 unsigned-bit with Range [0..255] , [0x00..0xFF]*/
typedef unsigned char  	     	uint8;

/* 16 unsigned-bit with Range [0..65535] , [0x0000..0xFFFF]*/
typedef unsigned short			uint16;

/* 32 unsigned-bit with Range [0..4294967295] , [0x00000000..0xFFFFFFFF]*/
typedef unsigned long  		 	uint32;

/* 64 unsigned-bit with Range [0..18446744073709551615],\
							  [0x0000000000000000..0xFFFFFFFFFFFFFFFF]*/
typedef unsigned long long 		uint64;

/* 8 signed-bit with Range [-128..+127] , [0x80..0x7F]*/
typedef char  					sint8;
	
/* 16 signed-bit with Range [-32768..+32767] , [0x8000..0x7FFF]*/	
typedef short 					sint16;
	
/* 32 signed-bit with Range [-2147483648..+2147483647] , [0x80000000..0x7FFFFFFF]*/		
typedef long  					sint32;
		
/* 64 signed-bit with Range [-9223372036854775808..9223372036854775807],\
							[0x8000000000000000..0x7FFFFFFFFFFFFFFF]*/		
typedef long long 				sint64;

/* At least 8 bit*/
typedef unsigned char  			uint8_least;

/* At least 16 bit*/
typedef unsigned short 			uint16_laest;

/* At least 32 bit*/
typedef unsigned long  			uint32_least;

/* At least 7 bit + 1 bit sign*/
typedef char  					sint8_least;

/* At least 15 bit + 1 bit sign*/		
typedef short 					sint16_least;

/* At least 31 bit + 1 bit sign*/		
typedef long  					sint32_least;

/* Single-precision floating-point with Range [-3.4028235e+38..+3.4028235e+38]*/
typedef float  					float32;

/* Double-precision floating-point with Range\
			[-1.7976931348623157e+308..+1.7976931348623157e+308]*/
typedef double 					float64;


/*****************************************************************/
/*				        Functions Prototype        		         */
/*****************************************************************/

#endif /* PLATFORM_TYPES_H */
