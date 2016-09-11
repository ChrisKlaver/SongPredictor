#ifndef H_CHANNEL
#define H_CHANNEL

#include <vector>
#include "sndfile.h"
#include "modplug.h"

namespace ModExtractor
{
	class Channel
	{
		public:

		Channel(
			const MODCHANNEL& channel,
			const MODCHANNELSETTINGS& settings,
			const std::vector<ModPlugNote>& notes
			);

		private:

		/// Channel notes
		std::vector<ModPlugNote> m_notes;

		/// Channel settings
		MODCHANNELSETTINGS m_channelSettings;

		/// Channel
		MODCHANNEL m_channel;

	};
}
#endif