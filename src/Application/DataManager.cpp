/*
AUTHOR : SUZEAU François

DATE : 23/11/2021

MODULE : DataManager

NAMEFILE : DataManager.hpp

PURPOSE :   - Manage data transfert between all module of the application program
            - Store datas references (for texture, render, settings)
*/

#include "DataManager.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
DataManager::DataManager(int width, int height) : m_width(width), m_height(height)
{

}

DataManager::~DataManager()
{
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* getters/setters *********************************************************************/
/***********************************************************************************************************************************************************************/
void DataManager::setTerminate(bool const terminate)
{
    m_terminate = terminate;
}

bool DataManager::getTerminate() const
{
    return m_terminate;
}

int DataManager::getWidth() const
{
    return m_width;
}

int DataManager::getHeight() const
{
    return m_height;
}

void DataManager::setFps(unsigned int const fps)
{
    m_fps = fps;
}

unsigned int DataManager::getFps() const
{
    return m_fps;
}

void DataManager::setVolume(int const volume)
{
    m_volume = volume;
}

int DataManager::getVolume() const
{
    return m_volume;
}

void DataManager::setPause(bool const pause)
{
    m_pause_music = pause;
} 

bool DataManager::getPause() const
{
    return m_pause_music;
}

void DataManager::setTrack(int const track)
{
    m_track = track;
}

int DataManager::getTrack() const
{
    return m_track;
}