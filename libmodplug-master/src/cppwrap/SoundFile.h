#ifndef H_SOUNDFILE
#define H_SOUNDFILE

#include <string>
#include <vector>
#include "Channel.h"

namespace ModExtractor
{
	class SoundFile
	{
		public:

		/// C'tor specify full path
		explicit SoundFile(const std::string& fullPathOfFile);

	private:

		/// Stores specific channel info together with the notes
		std::vector<Channel> m_channels;

	};
}
#endif