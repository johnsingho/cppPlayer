#ifndef PlayerHelper_h_2015_11_
#define PlayerHelper_h_2015_11_

//#include "HeThread.h"
#include "SimpleWin.h"
#include "MyPlayer.h"


class CPlayerHelper
{
public:
    CPlayerHelper();
    ~CPlayerHelper();

    bool initPlayer(int left, int right, int width, int height);
    bool play(const char* pszMedia);
    void stop();

    inline CMyPlayer*  getPlayer(){ return &m_player;}
    inline CSimpleWin* getWndPlayer(){return &m_wndPlayer;}
private:
    CMyPlayer  m_player;
    CSimpleWin m_wndPlayer;
    
};







#endif // PlayerHelper_h_2015_11_