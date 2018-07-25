//#include "StdAfx.h"
#include "MyPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef _WIN32
#pragma comment(lib, "libvlc.lib")
#pragma comment(lib, "libvlccore.lib")
#endif


CMyPlayer::CMyPlayer()
    : m_pInst(NULL)
    , m_pmi(NULL)
{
}

CMyPlayer::~CMyPlayer()
{
    close();
}

void CMyPlayer::close()
{
    if(m_pmi)
    {
        libvlc_media_player_stop(m_pmi);      /* Stop playing */    
        libvlc_media_player_release(m_pmi);   /* Free the media_player */
        m_pmi = NULL;
    }
    
    if(m_pInst)
    {
        libvlc_release (m_pInst);
        m_pInst = NULL;
    }
}

void CMyPlayer::init( int argc/*=0*/, const char* const *argv/*=NULL*/ )
{
    if (!m_pInst)
    {
	//! tetmp for test
	const char* pstrArg = "--vout x11";
        m_pInst = libvlc_new(1, &pstrArg);
    }
}

bool CMyPlayer::loadFromFile( const char* pstrFile )
{
    if(!pstrFile || !pstrFile[0]){ return false;}
    init();
    libvlc_media_t* pmd = libvlc_media_new_path(m_pInst, pstrFile);
    m_pmi = libvlc_media_player_new_from_media(pmd);      /* Create a media player playing environement */     
    libvlc_media_release(pmd);                            /* No need to keep the media now */
}

bool CMyPlayer::loadFromUrl( const char* pstrUrl )
{
    if(!pstrUrl || !pstrUrl[0]){ return false;}
    init();
    libvlc_media_t* pmd = libvlc_media_new_location(m_pInst, pstrUrl);
    m_pmi = libvlc_media_player_new_from_media(pmd);      /* Create a media player playing environement */     
    libvlc_media_release(pmd);                            /* No need to keep the media now */
}

bool CMyPlayer::setMediaFromFile( const char* pstrFile )
{
    if(!pstrFile || !pstrFile[0]){ return false;}
    libvlc_media_t* pmd = libvlc_media_new_path(m_pInst, pstrFile);
    this->setMedia(pmd);
    libvlc_media_release(pmd);
}

bool CMyPlayer::setMediaFromUrl( const char* pstrUrl )
{
    if(!pstrUrl || !pstrUrl[0]){ return false;}
    libvlc_media_t* pmd = libvlc_media_new_location(m_pInst, pstrUrl);
    this->setMedia(pmd);
    libvlc_media_release(pmd);    
}

void CMyPlayer::setWindowHwnd( unsigned int hwnd )
{
#ifdef _WIN32
    libvlc_media_player_set_hwnd(m_pmi, (void*)hwnd);
#else
    libvlc_media_player_set_xwindow(m_pmi, hwnd);
#endif
}

unsigned int CMyPlayer::getWindowHwnd()
{
#ifdef _WIN32
    return (unsigned int)libvlc_media_player_get_hwnd(m_pmi);
#else
    return libvlc_media_player_get_xwindow(m_pmi);
#endif
}





