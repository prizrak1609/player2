#pragma once

#include <QList>
#include <QUrl>

struct PluginPlaylist
{
    enum class PlaybackMode : uint
    {
        CurrentItemOnce,
        CurrentItemInLoop,
        Sequential,
        Loop
    };

    virtual ~PluginPlaylist() {}

    /**
     * @brief setPlaybackMode - set mode for playlist
     * mode has to be applied immediatelly
     * playlist will return media according to a playmode
     *
     * @param playback - mode for playlist
     */
    virtual void setPlaybackMode(PlaybackMode playback) = 0;
    /**
     * @brief setCurrentIndex - set index for media that needs to be played now
     * @param index - index for media
     */
    virtual void setCurrentIndex(size_t index) = 0;
    /**
     * @brief previousMedia - returns media that was played previously
     * @return media location
     */
    virtual QUrl previousMedia() = 0;
    /**
     * @brief nextMedia - returns media that will be played after current
     * @return media location
     */
    virtual QUrl nextMedia() = 0;
    /**
     * @brief count
     * @return count of added medias into playlist
     */
    virtual size_t count() = 0;
    /**
     * @brief isEmpty
     * @return whether list contains media or not
     */
    virtual bool isEmpty() = 0;
    /**
     * @brief clear - remove all medias
     */
    virtual void clear() = 0;
    /**
     * @brief add - adds new media to current playlist
     * @param mediaPath - media location
     */
    virtual void add(QUrl mediaPath) = 0;
    /**
     * @brief save - save current playlist into a file
     * @param playlistPath - path to a playlist file
     */
    virtual void save(QString playlistPath) = 0;
    /**
     * @brief read - loads playlist from a provided file
     * @param playlistPath - path to a file
     * @return list paths to media
     */
    virtual QList<QUrl> read(QString playlistPath) = 0;
};
