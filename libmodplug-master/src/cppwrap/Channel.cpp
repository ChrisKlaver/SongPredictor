#include "Channel.h"

using namespace ModExtractor;

Channel::Channel(
	const MODCHANNEL& channel, 
	const MODCHANNELSETTINGS& settings,
	const std::vector<ModPlugNote>& notes
	) :
	m_channel(channel), m_channelSettings(settings), m_notes(notes)
{

}