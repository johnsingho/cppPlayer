#include "HeThread.h"


#ifdef _WIN32

CHeThread::CHeThread( THREAD_FUNC pfn, void* pArg/*=NULL*/)
    : m_pfn(pfn)
    , m_th(0)
    , m_dwThreadID(0)
    , m_pArg(pArg)
{
}


CHeThread::~CHeThread()
{
    if( m_th)
    {
        waitForExit();
        CloseHandle(m_th);
    }    
}

HANDLE CHeThread::CreateThread()
{
    if( !m_pfn){ return NULL;}    
    m_th = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)m_pfn, m_pArg, 0, &m_dwThreadID);
    return m_th;
}

bool CHeThread::isValid()const
{
    return (NULL!=m_th);
}

THR_RET_TYPE CHeThread::waitForExit()
{
    DWORD dwRet = WaitForSingleObject(m_th, INFINITE);
    return dwRet;
}

bool CHeThread::detach()
{
    bool bRet = (TRUE==CloseHandle(m_th));    
    m_th=NULL;
    return bRet;
}

#else

CHeThread::CHeThread( THREAD_FUNC pfn, void* pArg/*=NULL*/)
    : m_pfn(pfn)
    , m_th(0)
    , m_pArg(pArg)
{
}

CHeThread::~CHeThread()
{
    if( m_th)
    {
        waitForExit();
        pthread_detach(m_th);
    }    
}


pthread_t CHeThread::CreateThread()
{
    if( !m_pfn){ return -1;}
    pthread_create(&m_th, NULL, m_pfn, m_pArg);
    return m_th;
}

bool CHeThread::isValid()const
{
    return (-1!=m_th);
}

THR_RET_TYPE CHeThread::waitForExit()
{
    void* ret=NULL;
    if(m_th)
    {
        pthread_join(m_th, &ret);
    }
    return ret;
}

bool CHeThread::detach()
{
    bool bDetach = (0==pthread_detach( m_th));
    m_th=0;
    return bDetach;
}

#endif//_WIN32

