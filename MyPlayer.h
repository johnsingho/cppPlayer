#if !defined(AFX_MYPLAYER_H__9C6847EB_0F9E_4496_89AC_14BB95420B80__INCLUDED_)
#define AFX_MYPLAYER_H__9C6847EB_0F9E_4496_89AC_14BB95420B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// MyPlayer
// ��ƽ̨��������װ
// ����vlc��������
// ��ubuntu����Ҫ��װvlc, vlc-dev
//
// History: 
//      H.Z.XIN 2015-11-09 created
//
//////////////////////////////////////////////////////////////////////

#include <vlc/vlc.h>

typedef void* MY_WIN;

class CMyPlayer
{
public:
	CMyPlayer();
	~CMyPlayer();
    
    //֧�ִ���vlc�����в�������ʼ��
    void init(int argc=0, const char* const *argv=NULL);
    
    void close();

    /**
    *����ý���ļ�
    */    
    bool loadFromFile(const char* pstrFile);
    bool loadFromUrl(const char* pstrUrl);

    /**
     * Set the media that will be used by the media_player. If any, previous
     * md will be released.
     */
    void setMedia(libvlc_media_t* pmd)
    {
        libvlc_media_player_set_media( m_pmi, pmd);
    }

    //ֱ����ת������ý���ļ�
    bool setMediaFromFile(const char* pstrFile);
    bool setMediaFromUrl(const char* pstrUrl);

    /**
     * Get the media used by the media_player.
     */
     libvlc_media_t* getMedia()
    {
        libvlc_media_t* media = libvlc_media_player_get_media(m_pmi);
        return media;
    }

    /**
     * Get the Event Manager from which the media player send event.
     */
    libvlc_event_manager_t* getEventManager()
    {   
        libvlc_event_manager_t* pEventManager = libvlc_media_player_event_manager( m_pmi);
        return pEventManager;
    }

    /**
     * isPlaying
     */
    bool isPlaying()
    {
        return libvlc_media_player_is_playing(m_pmi) != 0;
    }

    /**
     * Play     
     */
    bool play()
    {
        return libvlc_media_player_play(m_pmi)==0;
    }

    /**
     * Toggle pause (no effect if there is no media)
     */
    void pause()
    {
        libvlc_media_player_pause(m_pmi);
    }

    /**
     * Stop (no effect if there is no media)
     */
    void stop()
    {
        libvlc_media_player_stop(m_pmi);
    }


    void setWindowHwnd(MY_WIN hwnd);
    MY_WIN getWindowHwnd();

    /**
     * todo �˺�������ֵ����ȷ
     * Get the current movie length (in ms).     
     */
    libvlc_time_t getTotalMediaTime()
    {
        return libvlc_media_player_get_length(m_pmi);
    }

    /**
     * Get the current movie time (in ms).
     * ��ǰ����ʱ��
     * \return the movie time (in ms), or -1 if there is no media.
     */
    libvlc_time_t getMediaTime()
    {
        return  libvlc_media_player_get_time(m_pmi);
    }

    /**
     * Set the movie time (in ms). This has no effect if no media is being
     * played. Not all formats and protocols support this.
     *
     * \param i_time  the movie time (in ms).
     */
    void setMediaTime(libvlc_time_t i_time)
    {
        libvlc_media_player_set_time(m_pmi, i_time);
    }

    /**
     * Get movie position as percentage between 0.0 and 1.0.
     *
     * \return movie position, or -1. in case of error
     */
    float getMediaPosition()
    {
        return libvlc_media_player_get_position(m_pmi);
    }

    /**
     * Set movie position as percentage between 0.0 and 1.0. 
     * ��Ƶ�����޷���ת��������ܲ�һ����Ч��
     */
    void setMediaPosition(float f_pos)
    {
        libvlc_media_player_set_position(m_pmi, f_pos);
    }

    /**
     * ý����Բ�����     
     */
    bool isPlayable()
    {
        return libvlc_media_player_will_play(m_pmi) != 0;
    }
    
    /**
     * ��ǰ�����ٶ�
     */
    float getPlayRate()
    {
        return libvlc_media_player_get_rate(m_pmi);
    }

    /**
     * ���õ�ǰ�����ٶ�
     */
    int setPlayRate(float rate)
    {
        return libvlc_media_player_set_rate(m_pmi, rate);
    }

    /**
     * Get current movie state
     * return the current state of the media player (playing, paused, ...)
     */
    libvlc_state_t getPlayState()
    {
        return libvlc_media_player_get_state(m_pmi);
    }

    /**
     * ֡��
     */
    float getMediafps()
    {
        return libvlc_media_player_get_fps(m_pmi);
    }

    /**
     * Get the amount of video outputs this media player has?
     *
     * \return the number of video outputs
     */
    uint32_t getVideoOuts()
    {
        return libvlc_media_player_has_vout(m_pmi);
    }

    /**
     * �����������
     */
    bool isSeekable()
    {
        return libvlc_media_player_is_seekable(m_pmi) != 0;
    }

    /**
     * ����ͣ��
     */
    bool canPause()
    {
        return libvlc_media_player_can_pause(m_pmi) != 0;
    }

    /**
     * ����һ֡
     */
    void gotoNextFrame()
    {
        libvlc_media_player_next_frame(m_pmi);
    }

    /**
     * ��û�а󶨵����ڵ�ʱ�򣬿��Խ���ȫ���л���
     */
    void toggleFullscreen()
    {
        libvlc_toggle_fullscreen(m_pmi);
    }

    /**
     *�����л�
     */
    void toggleMute()
    {
        libvlc_audio_toggle_mute(m_pmi);
    }

    /**
     * ��ǰ������0~100��
     */
    int getPlayVolume()
    {
        return libvlc_audio_get_volume(m_pmi);
    }

    /**
     * ���ĵ�ǰ����(0~100)
     */
    bool setPlayVolume(int i_volume)
    {
        return libvlc_audio_set_volume(m_pmi, i_volume) == 0;
    }

     /**
     * ���ſ��Ƿ�������
     */
    void setKeyInput(bool bOn)
    {
        libvlc_video_set_key_input(m_pmi, (unsigned)bOn);
    }

    /**
     * ���ſ��Ƿ�����갴����
     */
    void setMouseInput(bool bOn)
    {
        libvlc_video_set_mouse_input(m_pmi, (unsigned)bOn);
    }

    /**
     * ��������ش�С
     * \param num  number of the video (starting from, and most commonly 0)
     * \param px  pointer to get the pixel width [OUT]
     * \param py  pointer to get the pixel height [OUT]
     */
    bool getVideoSize(unsigned num, unsigned * px, unsigned * py)
    {
        return libvlc_video_get_size( m_pmi, num, px, py ) == 0;
    }

    /**
     * ��Ƶ��������ű��ʣ�0��ʾ�Զ���Ӧ���ڴ�С
     */
    float getVideoScale()
    {
        return libvlc_video_get_scale(m_pmi);
    }

    /**
     * ��Ƶ��������ű��ʣ�0��ʾ�Զ���Ӧ���ڴ�С
     */
    void setVideoScale(float f_factor)
    {
        libvlc_video_set_scale(m_pmi, f_factor);
    }

    /**
     * ������Ļ�ļ�
     * \param psz_subtitle  new video subtitle file
     * \return the success status (boolean)
     */
    bool setSubtitleFile(const char* pstrSubtitle)
    {
        return libvlc_video_set_subtitle_file(m_pmi, pstrSubtitle)!=0;
    }

    inline libvlc_instance_t* getIns()
    {
        return m_pInst;
    }
    inline libvlc_media_player_t* getMI()
    {
        return m_pmi;
    }    
private:
    libvlc_instance_t*     m_pInst;
    libvlc_media_player_t* m_pmi;
};




////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_MYPLAYER_H__9C6847EB_0F9E_4496_89AC_14BB95420B80__INCLUDED_)
