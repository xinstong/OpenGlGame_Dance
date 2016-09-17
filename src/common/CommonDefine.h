//*********************************//
//File:         OpenGlViewer.h
//Auther:       xst
//History:
//  xst         2016/9/17       create
//*********************************//


#ifndef SA_COMMON_COMMON_DEFINE__H
#define SA_COMMON_COMMON_DEFINE__H


#include <cassert>
#include "Log.h"


//
// namespace
//
#ifdef __cplusplus
#define NS_SA_BEGIN                     namespace SaGame {
#define NS_SA_END                       }
#define USING_SA_DD                     using namespace SaGame
#define NS_SA                           ::SaGame
#else
#define NS_SA_BEGIN 
#define NS_SA_END 
#define USING_SA_DD 
#define NS_SA
#endif 


#define SAFE_NEW_POINTER(p, T, ...)         \
    if (!p)                                 \
    {                                       \
        p = new T(__VA_ARGS__);             \
    }                                       \

#define SAFE_DELETE_POINTER(p)              \
    if (p)                                  \
    {                                       \
        delete p;                           \
        p = NULL;                           \
    }                                       \

#define SAFE_CALL_POINTER(p, call, ...)     \
    assert(p);                              \
    if (p)                                  \
    {                                       \
        p->call(__VA_ARGS__);               \
    }                                       \
    else                                    \
    {                                       \
        /*SaLog(ERROR, "NULL pointer call"); */ \
    }                                       \

#endif //SA_COMMON_COMMON_DEFINE__H