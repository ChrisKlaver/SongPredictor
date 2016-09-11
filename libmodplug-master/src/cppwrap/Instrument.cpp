#include "Instrument.h"

using namespace ModExtractor;

Instrument::Instrument(
	const MODINSTRUMENT&  instrument,
	const INSTRUMENTHEADER& header
	) : m_instrument(instrument), m_header(header)
{

}