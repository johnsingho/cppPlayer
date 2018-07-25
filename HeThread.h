#pragma once


/*****************************************************************************
* Name     : CHeThread
* Creator  : H.Z.XIN
* Date     : 2014-01-15
* Function : 简单的线程类实现
* Parameter: 
* Return(s): 
* Notices  : 
* Samples  :

void* HEAPI DoSome2(void* pPara)
{
    for(int i=0; i<5; ++i)
    {
        printf("Hello, %d = %s\n", i, (const char*)pPara);
        Sleep(1000);
    }
    return 0;
}

CHeThread threadDo2((THREAD_FUNC)DoSome2, "醉酒佬");
threadDo2.CreateThread();
threadDo2.waitForExit(); //等待线程结束

------------------------------------------------------------------------------
Change Log:
  2014-01-15        H.Z.XIN        Create
  2014-03-05        H.Z.XIN        修改windows版
*****************************************************************************/
#ifdef _WIN32
#include <windows.h>
#define THR_RET_TYPE DWORD
#define HEAPI WINAPI
typedef THR_RET_TYPE (HEAPI* THREAD_FUNC)(void*);

class CHeThread
{
public:
    CHeThread(THREAD_FUNC pfn, void* pArg=NULL);
    ~CHeThread();
    HANDLE CreateThread();
    bool isValid()const;
    THR_RET_TYPE waitForExit();
    bool detach();

    inline HANDLE getHandle() const
    {
        return m_th;
    }
    inline DWORD getThreadID()const
    {
        return m_dwThreadID;
    }
private:
    THREAD_FUNC m_pfn;
    HANDLE   m_th;
    DWORD    m_dwThreadID;
    void*    m_pArg;
};
#else
#include <pthread.h>
#define THR_RET_TYPE void*
#define HEAPI 
typedef THR_RET_TYPE (HEAPI* THREAD_FUNC )(void *);

class CHeThread
{
public:
    CHeThread(THREAD_FUNC pfn, void* pArg=NULL);
    ~CHeThread();
    pthread_t CreateThread();
    bool isValid()const;
    THR_RET_TYPE waitForExit();
    bool detach();
    
    inline pthread_t getHandle() const
    {
        return m_th;
    }
private:
    THREAD_FUNC m_pfn;
    pthread_t   m_th;
    void*       m_pArg;
};

#endif//_WIN32





