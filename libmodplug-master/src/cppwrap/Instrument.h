#ifndef H_INSTRUMENT
#define H_INSTRUMENT

#include "modplug.h"

namespace ModExtractor
{
	class Instrument
	{
	public:

		Instrument(
			const MODINSTRUMENT&  instrument,
			const INSTRUMENTHEADER& header
			);

	private:

		MODINSTRUMENT m_instrument;
		INSTRUMENTHEADER m_header;
	};

}

#endif