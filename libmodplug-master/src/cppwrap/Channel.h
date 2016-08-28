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

		explicit Channel(const MODCHANNEL& channel, const std::vector<ModPlugNote>& notes);

		private:

		/// Channel notes
		std::vector<ModPlugNote> m_notes;

		/// Channel settings
		MODCHANNEL m_channelSettings;

		/// Instrument


	};
}
#endif