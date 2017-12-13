

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Wed Dec 13 14:35:39 2017
 */
/* Compiler settings for TestOCX.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_TestOCXLib,0x3F91FFE5,0xC6D9,0x4CB6,0xBE,0x23,0x38,0xE3,0x72,0x10,0x6A,0x16);


MIDL_DEFINE_GUID(IID, DIID__DTestOCX,0x01DB9F27,0x7338,0x43E5,0xA9,0xFD,0xC2,0x37,0x3E,0x9F,0xF7,0x44);


MIDL_DEFINE_GUID(IID, DIID__DTestOCXEvents,0xE0DD2328,0x0EA9,0x41CF,0x85,0x8D,0x94,0x73,0x03,0x9C,0x33,0xB3);


MIDL_DEFINE_GUID(CLSID, CLSID_TestOCX,0x64947E15,0x852E,0x496E,0xB3,0xB1,0xAC,0xCF,0x57,0x42,0xBD,0x4C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



