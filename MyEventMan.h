#ifndef MY_EVENT_MAN_2015_11_H_
#define MY_EVENT_MAN_2015_11_H_

#include <vlc/libvlc_events.h>

// 用来绑定消息处理过程
//
class CMyEventMan
{
public:
    CMyEventMan(libvlc_event_manager_t *p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void *p_user_data )
        :m_pem(p_event_manager)
        ,m_event_type(i_event_type)
        ,m_callback(f_callback)
        ,m_user_data(p_user_data)
        {
            libvlc_event_attach(m_pem, m_event_type, m_callback, m_user_data);
        }
        ~CMyEventMan()
        {
            libvlc_event_detach(m_pem, m_event_type, m_callback, m_user_data);
        }
private:
    libvlc_event_manager_t* m_pem;
    libvlc_event_type_t m_event_type;
    libvlc_callback_t m_callback;
    void* m_user_data;
};



/*

//////////////////////////////////////////
if (libvlc_event_attach( *m_eventManager, m_eventType, m_wrapper, &m_userCallback ) != 0)
{
    printf("***libvlc_event_attach() error!\n");
}
        

~EventHandler()
{
    libvlc_event_detach( *m_eventManager, m_eventType, m_wrapper, &m_userCallback );
}


////////////////////////////////////////////////////////////////


struct EventHandlerBase
{
    virtual ~EventHandlerBase() {}
    virtual void unregister() = 0;
};


class MediaPlayerEventManager : public EventManager
{
    public:
        MediaPlayerEventManager(InternalPtr ptr) : EventManager( ptr ) {}

        template <typename Func>
        RegisteredEvent onMediaChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(MediaPtr));
            return handle(libvlc_MediaPlayerMediaChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                auto media = e->u.media_player_media_changed.new_media;
                (*callback)( media != nullptr ? std::make_shared<Media>( media, true ) : nullptr );
            });
        }

        template <typename Func>
        RegisteredEvent onNothingSpecial( Func&& f )
        {
            return handle(libvlc_MediaPlayerNothingSpecial, std::forward<Func>( f ));
        }

        template <typename Func>
        RegisteredEvent onOpening( Func&& f )
        {
            return handle(libvlc_MediaPlayerOpening, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onBuffering( Func&& f )
        {
            EXPECT_SIGNATURE(void(float));
            return handle(libvlc_MediaPlayerBuffering, std::forward<Func>(f), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_buffering.new_cache );
            });
        }

        template <typename Func>
        RegisteredEvent onPlaying( Func&& f )
        {
            return handle( libvlc_MediaPlayerPlaying, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onPaused(Func&& f)
        {
            return handle( libvlc_MediaPlayerPaused, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onStopped(Func&& f)
        {
            return handle( libvlc_MediaPlayerStopped, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onForward(Func&& f)
        {
            return handle( libvlc_MediaPlayerForward, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onBackward(Func&& f)
        {
            return handle( libvlc_MediaPlayerBackward, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onEndReached(Func&& f)
        {
            return handle( libvlc_MediaPlayerEndReached, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onEncounteredError(Func&& f)
        {
            return handle( libvlc_MediaPlayerEncounteredError, std::forward<Func>( f ) );
        }

        template <typename Func>
        RegisteredEvent onTimeChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(libvlc_time_t));
            return handle( libvlc_MediaPlayerTimeChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_time_changed.new_time );
            });
        }

        template <typename Func>
        RegisteredEvent onPositionChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(float));
            return handle( libvlc_MediaPlayerPositionChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_position_changed.new_position );
            });
        }

        template <typename Func>
        RegisteredEvent onSeekableChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(bool));
            return handle( libvlc_MediaPlayerSeekableChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_seekable_changed.new_seekable != 0 );
            });
        }

        template <typename Func>
        RegisteredEvent onPausableChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(bool));
            return handle( libvlc_MediaPlayerSeekableChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_seekable_changed.new_seekable != 0 );
            });
        }

        template <typename Func>
        RegisteredEvent onTitleChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(int));
            return handle( libvlc_MediaPlayerTitleChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_title_changed.new_title );
            });
        }

        template <typename Func>
        RegisteredEvent onSnapshotTaken( Func&& f )
        {
            EXPECT_SIGNATURE(void(std::string));
            return handle( libvlc_MediaPlayerSnapshotTaken, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_snapshot_taken.psz_filename );
            });
        }

        template <typename Func>
        RegisteredEvent onLengthChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(libvlc_time_t));
            return handle( libvlc_MediaPlayerLengthChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_length_changed.new_length );
            });
        }

        template <typename Func>
        RegisteredEvent onVout( Func&& f )
        {
            EXPECT_SIGNATURE(void(int));
            return handle( libvlc_MediaPlayerVout, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_vout.new_count );
            });
        }

        template <typename Func>
        RegisteredEvent onScrambledChanged( Func&& f )
        {
            EXPECT_SIGNATURE(void(bool));
            return handle( libvlc_MediaPlayerScrambledChanged, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_scrambled_changed.new_scrambled != 0 );
            });
        }

        template <typename Func>
        RegisteredEvent onESAdded( Func&& f )
        {
            EXPECT_SIGNATURE(void(libvlc_track_type_t, int));
            return handle( libvlc_MediaPlayerESAdded, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_es_changed.i_type, e->u.media_player_es_changed.i_id );
            });
        }

        template <typename Func>
        RegisteredEvent onESDeleted( Func&& f )
        {
            EXPECT_SIGNATURE(void(libvlc_track_type_t, int));
            return handle( libvlc_MediaPlayerESDeleted, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_es_changed.i_type, e->u.media_player_es_changed.i_id );
            });
        }

        template <typename Func>
        RegisteredEvent onESSelected( Func&& f )
        {
            EXPECT_SIGNATURE(void(libvlc_track_type_t, int));
            return handle( libvlc_MediaPlayerESSelected, std::forward<Func>( f ), [](const libvlc_event_t* e, void* data)
            {
                auto callback = static_cast<DecayPtr<Func>>( data );
                (*callback)( e->u.media_player_es_changed.i_type, e->u.media_player_es_changed.i_id );
            });
        }
};

*/

#endif // MY_EVENT_MAN_2015_11_H_
