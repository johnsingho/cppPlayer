#include <string>
#include <iostream>
#include "MyPlayer.h"

void testPlayNoWin();

int main(int argc, char* argv[])
{
    std::string strCMD;
    
    testPlayNoWin(); //

    while(true)
    {
        std::cin >> strCMD;
        
        if (! strCMD.compare("quit"))
        {
            break;
        } 
    }

    return 0;
}

void testPlayNoWin()
{   
    CMyPlayer mPlayer;
    mPlayer.init();
    const char* pstrMedia = NULL;
    
#ifdef _WIN32
    pstrMedia = "d:\\media\\dream.mp3";
#else
    pstrMedia = "/home/john/media/dream.mp3";
#endif    
    mPlayer.loadFromFile(pstrMedia);
    mPlayer.play();
    
#ifdef _WIN32
    pstrMedia = "d:\\media\\bing1110.jpg";
#else
    pstrMedia = "/home/john/media/bing1110.jpg";
#endif
    mPlayer.loadFromFile(pstrMedia);
    mPlayer.play();
    
#ifdef _WIN32
    pstrMedia = "d:\\media\\staticpic.PNG";
#else
    pstrMedia = "/home/john/media/staticpic.PNG";     
#endif    
    mPlayer.loadFromFile(pstrMedia);
    mPlayer.play();
    
#ifdef _WIN32
    pstrMedia = "d:\\media\\beautiful.flv";
#else
    pstrMedia = "/home/john/media/beautiful.flv";     
#endif    
    mPlayer.loadFromFile(pstrMedia);
    mPlayer.play();

    //libvlc_wait(cAVPlayer.m_pVLC_Inst);
    libvlc_set_user_agent( mPlayer.getIns(),"my player", NULL);
    
#ifdef _WIN32
    pstrMedia = "d:\\media\\china.mp4";
#else
    pstrMedia = "/home/john/media/china.mp4";
#endif    
    mPlayer.loadFromFile(pstrMedia);
    mPlayer.play();
}

