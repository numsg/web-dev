

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TestOCXidl_h__
#define __TestOCXidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DTestOCX_FWD_DEFINED__
#define ___DTestOCX_FWD_DEFINED__
typedef interface _DTestOCX _DTestOCX;

#endif 	/* ___DTestOCX_FWD_DEFINED__ */


#ifndef ___DTestOCXEvents_FWD_DEFINED__
#define ___DTestOCXEvents_FWD_DEFINED__
typedef interface _DTestOCXEvents _DTestOCXEvents;

#endif 	/* ___DTestOCXEvents_FWD_DEFINED__ */


#ifndef __TestOCX_FWD_DEFINED__
#define __TestOCX_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestOCX TestOCX;
#else
typedef struct TestOCX TestOCX;
#endif /* __cplusplus */

#endif 	/* __TestOCX_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_TestOCX_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_TestOCX_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TestOCX_0000_0000_v0_0_s_ifspec;


#ifndef __TestOCXLib_LIBRARY_DEFINED__
#define __TestOCXLib_LIBRARY_DEFINED__

/* library TestOCXLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_TestOCXLib;

#ifndef ___DTestOCX_DISPINTERFACE_DEFINED__
#define ___DTestOCX_DISPINTERFACE_DEFINED__

/* dispinterface _DTestOCX */
/* [uuid] */ 


EXTERN_C const IID DIID__DTestOCX;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("01DB9F27-7338-43E5-A9FD-C2373E9FF744")
    _DTestOCX : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTestOCXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTestOCX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTestOCX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTestOCX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTestOCX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTestOCX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTestOCX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTestOCX * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DTestOCXVtbl;

    interface _DTestOCX
    {
        CONST_VTBL struct _DTestOCXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTestOCX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DTestOCX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DTestOCX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DTestOCX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DTestOCX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DTestOCX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DTestOCX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTestOCX_DISPINTERFACE_DEFINED__ */


#ifndef ___DTestOCXEvents_DISPINTERFACE_DEFINED__
#define ___DTestOCXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DTestOCXEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DTestOCXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E0DD2328-0EA9-41CF-858D-9473039C33B3")
    _DTestOCXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTestOCXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTestOCXEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTestOCXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTestOCXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTestOCXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTestOCXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTestOCXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTestOCXEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DTestOCXEventsVtbl;

    interface _DTestOCXEvents
    {
        CONST_VTBL struct _DTestOCXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTestOCXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DTestOCXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DTestOCXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DTestOCXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DTestOCXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DTestOCXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DTestOCXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTestOCXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TestOCX;

#ifdef __cplusplus

class DECLSPEC_UUID("64947E15-852E-496E-B3B1-ACCF5742BD4C")
TestOCX;
#endif
#endif /* __TestOCXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


