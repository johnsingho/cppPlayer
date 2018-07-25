#include <string>
#include <iostream>
#include "MyPlayer.h"
#include "SimpleWin.h"

#include "PlayerHelper.h"
#include "MyEventMan.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void testPlayNoWin();
void testPlayHaveWin();

int main(int argc, char* argv[])
{
    //testPlayNoWin();
    testPlayHaveWin(); //


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

    /////////////////////////
//     std::string strCMD;
//     while(true)
//     {
//         std::cin >> strCMD;
//         
//         if (! strCMD.compare("quit"))
//         {
//             break;
//         } 
//     }

}

// void testPlayHaveWin()
// {   
//     CMyPlayer mPlayer;
//     mPlayer.init();
//     const char* pstrMedia = NULL;
//     
//     CSimpleWin* psimpleWin = new CSimpleWin;
//     bool bCreate = psimpleWin->Create(100, 100, 800, 600, NULL);    
//     
// #ifdef _WIN32
//     pstrMedia = "d:\\media\\beautiful.flv";
// #else
//     pstrMedia = "/home/john/media/beautiful.flv";     
// #endif    
//     mPlayer.loadFromFile(pstrMedia);
//     mPlayer.setWindowHwnd(psimpleWin->getHwnd());
//     mPlayer.play();
//     //mPlayer.setVideoScale(0);
//     psimpleWin->Show();
//     
//     // Loop until we get the key or the timer fires.
//     MSG msg;
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }
// }

void SleepMs(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms*1000);
#endif
}

#ifdef _WIN32
#define FMT_INT64 "%I64d"
#else
#define FMT_INT64 "%lld"
#endif


void Func_My_Callback( const struct libvlc_event_t* pev, void* pstrData)
{
    CMyPlayer* pPlayer = (CMyPlayer*)pstrData;
    //todo 也许需要加上锁保护
    switch(pev->type) 
    {
    case libvlc_MediaPlayerPositionChanged:
        printf("**position change, new pos=%lf\n", pev->u.media_player_position_changed.new_position);
        break;
    case libvlc_MediaPlayerPlaying:
        printf("**playing, pEventData=%X, pstrData=%s\n", pev, (const char*)pstrData);
        break;
    case libvlc_MediaPlayerEndReached:
        printf("**Reach end!\n");
        break;
    case libvlc_MediaPlayerTimeChanged:
        {
            double fpPos = pPlayer->getMediaPosition();
            fpPos *= 100.0; //to percent
            printf("**position change, new time=" FMT_INT64 ",pos=%g\n", 
                pev->u.media_player_time_changed.new_time,
                fpPos
                );
        }        
        break;

    case libvlc_MediaPlayerMediaChanged:
    case libvlc_MediaPlayerNothingSpecial:
    case libvlc_MediaPlayerOpening:
    case libvlc_MediaPlayerBuffering:
    case libvlc_MediaPlayerPaused:
    case libvlc_MediaPlayerStopped:
    case libvlc_MediaPlayerForward:
    case libvlc_MediaPlayerBackward:
    case libvlc_MediaPlayerSeekableChanged:
    case libvlc_MediaPlayerPausableChanged:
    case libvlc_MediaPlayerLengthChanged:
    default:
        {
            const char* pstrEvName = libvlc_event_type_name(pev->type);
            printf("***Event: %s\n", pstrEvName);
        }
        break;
    }
}



void testPlayHaveWin()
{   
    CPlayerHelper playHelper;
    bool bValid = playHelper.initPlayer(123, 123, 400, 300);

    const char* pstrMedia=NULL;
// #ifdef _WIN32
//     pstrMedia = "d:\\media\\dream.mp3";
// #else
//     pstrMedia = "/home/john/media/dream.mp3";
// #endif
    
// #ifdef _WIN32
//     pstrMedia = "d:\\media\\china.mp4";
// #else
//     pstrMedia = "/home/john/media/china.mp4";
// #endif     

#ifdef _WIN32
    pstrMedia = "d:\\media\\beautiful.flv";
#else
    pstrMedia = "/home/john/media/beautiful.flv";     
#endif    
    bValid = playHelper.play(pstrMedia);
    //playHelper.stop();
    CMyPlayer* pPlayer = playHelper.getPlayer();
    libvlc_event_manager_t* pem = pPlayer->getEventManager();

    bool canSeek = pPlayer->isSeekable();
    printf("*** canSeek = %d\n", canSeek);

    static const char* pstrUserData="testData1";
    CMyEventMan evPlaying(pem, libvlc_MediaPlayerPlaying, Func_My_Callback, (void*)pstrUserData);
    CMyEventMan evEndReached(pem, libvlc_MediaPlayerEndReached, Func_My_Callback, NULL);
    //CMyEventMan evPosChanged(pem, libvlc_MediaPlayerPositionChanged, Func_cb_Poschange, NULL);
    CMyEventMan evPosChanged(pem, libvlc_MediaPlayerTimeChanged, Func_My_Callback, pPlayer);
    
        
#ifdef _WIN32
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (WM_CLOSE == msg.message) {
            //stop play
            break;
        }
    }
#else
    //! todo
    getchar();
#endif
    
    playHelper.stop();
}

