#ifndef H_SOUNDFILE
#define H_SOUNDFILE

#include <string>
#include <vector>
#include "Channel.h"
#include <memory>
#include "Instrument.h"
#include "Sample.h"

namespace ModExtractor
{
	class SoundFile
	{
		public:

		/// C'tor specify full path
		explicit SoundFile(const std::string& fullPathOfFile);

		/// Generate a CSoundFile from this file
		std::unique_ptr<CSoundFile> makeCSoundFile(void) const;

	private:

		/// Stores specific channel info together with the notes
		std::vector<Channel> m_channels;

		/// Instruments
		std::vector<Instrument> m_instruments;

		/// Samples
		std::vector<Sample> m_samples;

	};
}
#endif