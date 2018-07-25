#include "PlayerHelper.h"

#include <stdio.h>
#include <string.h>

CPlayerHelper::CPlayerHelper()
{    
}

    
CPlayerHelper::~CPlayerHelper()
{
    //! todo
    stop();
}


//////////////////////////////////////////

bool CPlayerHelper::initPlayer( int left, int right, int width, int height)
{
#ifdef _WIN32//////////////////////////////
    const char* argv[] = {
        "--video-on-top",
#ifdef JOHN_DEBUG
        "--verbose=2",/*full log*/
#endif
        NULL
        };
#else//////////////////////////////////////
    const char* argv[] = {
        "--video-on-top",
        "--vout","x11",
#ifdef JOHN_DEBUG
        "--verbose=2",/*full log*/
#endif
        NULL
    };
#endif/////////////////////////////////////
    
    int argc=sizeof(argv)/sizeof(argv[0])-1;

    m_player.init(argc, argv);
    bool bCreate = m_wndPlayer.Create(left, right, width, height, NULL);
    return bCreate;
}

// 播放本地文件
bool CPlayerHelper::play(const char* pszMedia)
{
    if( !m_player.getIns() || !m_wndPlayer.getHwnd())
    {
        return false;
    }
    if( !m_player.loadFromFile(pszMedia))
    {
        //加载文件失败
        return false;
    }
    
    m_player.setWindowHwnd(m_wndPlayer.getHwnd());
    
    //pPara->m_pPlayer->setVideoScale(0);
    m_wndPlayer.Show();
    m_player.play();

    return true;
}

void CPlayerHelper::stop()
{
    m_player.stop();
    m_wndPlayer.Hide();
}



