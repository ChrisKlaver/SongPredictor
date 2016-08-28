#include "Channel.h"

using namespace ModExtractor;

Channel::Channel(const MODCHANNEL& channel, const std::vector<ModPlugNote>& notes) :
	m_channelSettings(channel), m_notes(notes)
{

}