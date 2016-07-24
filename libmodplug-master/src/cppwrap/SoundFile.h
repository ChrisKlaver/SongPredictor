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
		explicit SoundFile(const std::string& fileName);

	private:

		std::vector<Channel> m_channels;

	};
}
#endif