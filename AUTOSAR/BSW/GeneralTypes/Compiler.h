/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Compiler.h                            						 **
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
**                                                        						 **
**	VENDOR		: 	NA				                     						 **
**                                                        						 **
**	                                                      						 **
**	DESCRIPTION : Compiler Abstraction Types         							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_CompilerAbstraction, AUTOSAR Release 4.3.1    **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef COMPILER_H
#define COMPILER_H

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

#include "Compiler_Cfg.h"

/*****************************************************************/
/*				        Macros Definition       		         */
/*****************************************************************/

/* Compiler Abstraction types Vendor ID */
#define COMPILER_VENDOR_ID					(0x40u)

/* Compiler Abstraction types module ID */
#define COMPILER_MODULE_ID					(198u)


/*	Moudle Version	1.0.0 */
#define COMPILER_SW_MAJOR_VERSION			(0x01u)
#define COMPILER_SW_MINOR_VERSION			(0x00u)
#define COMPILER_SW_PATCH_VERSION			(0x00u)

/* Autosar version 4.3.1 */
#define COMPILER_AR_RELEASE_MAJOR_VERSION	(0x04u)
#define COMPILER_AR_RELEASE_MINOR_VERSION	(0x03u)
#define COMPILER_AR_RELEASE_PATCH_VERSION	(0x01u)

#ifndef AUTOMATIC
#define AUTOMATIC
#endif

#ifndef TYPEDEF
#define TYPEDEF
#endif

#ifndef NULL_PTR
#define NULL_PTR		((void *)0)
#endif

#ifndef INLINE
#define INLINE	    	inline
#endif

#ifndef LOCAL_INLINE
#define LOCAL_INLINE	static inline
#endif


#define FUNC(rettype, memclass)						rettype

#define FUNC_P2CONST(rettype, ptrclass, memclass)	const rettype *

#define FUNC_P2VAR(rettype, ptrclass, memclass)		rettype *

#define P2VAR(ptrtype, memclass, ptrclass)	 		ptrtype *

#define P2CONST(ptrtype, memclass, ptrclass) 		ptrtype * const

#define CONSTP2VAR (ptrtype, memclass, ptrclass)  	ptrtype const *

#define CONSTP2CONST(ptrtype, memclass, ptrclass) 	const ptrtype *const

#define P2FUNC(rettype, ptrclass, fctname)			rettype (* fctname)

#define CONSTP2FUNC(rettype, ptrclass, fctname) 	rettype (* const fctname)

#ifndef CONST
#define CONST(consttype, memclass) 					const consttype
#endif

#define VAR(vartype, memclass) 						vartype

/*****************************************************************/
/*				        Types Definition        		         */
/*****************************************************************/


/*****************************************************************/
/*				        Functions Prototype        		         */
/*****************************************************************/


#endif /* COMPILER_H */
