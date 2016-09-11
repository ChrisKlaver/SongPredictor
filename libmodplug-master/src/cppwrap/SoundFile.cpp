#include "SoundFile.h"
#include "modplug.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace ModExtractor;

namespace
{
	using ModPlugFileHandle = std::unique_ptr<ModPlugFile, void(*)(ModPlugFile*)>;
	ModPlugFileHandle getHandle(const std::string& filename)
	{
		std::ifstream file(filename.c_str(), std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> buffer(static_cast<std::size_t>(size));
		if (file.read(buffer.data(), size) && size != 0)
		{
			ModPlugFileHandle modPlugFile(
				ModPlug_Load(&(*buffer.begin()), static_cast<int>(buffer.size())),
				[](ModPlugFile* f) { ModPlug_Unload(f); }
			);

			if (!modPlugFile)
			{
				throw std::runtime_error("Error: cannot read " + filename);
			}
			
			return modPlugFile;
		}
		else
		{
			throw std::runtime_error("Error: cannot read " + filename);
		}
	}

	std::vector<std::vector<ModPlugNote> > getAllNotes(ModPlugFile& file, const std::size_t numChannels)
	{
		std::vector<std::vector<ModPlugNote> > notes(numChannels);
		const std::size_t numPatterns = ModPlug_NumPatterns(&file);
		for (auto i = 0; i < numPatterns; ++i)
		{
			unsigned int numRows;
			ModPlugNote* rawNotes = ModPlug_GetPatternAtOrder(&file, i, &numRows);
			std::for_each(notes.begin(), notes.end(), [&numRows](std::vector<ModPlugNote>& n) { n.reserve(numRows + n.size() ); });
			for (unsigned int row = 0; row < numRows; ++row)
			{
				for (auto channel = 0; channel < numChannels; ++channel)
				{
					const std::size_t rowsAlreadyVisited = row * channel;
					notes[channel].push_back(rawNotes[rowsAlreadyVisited + channel]);
				}
			}
		}
		return notes;
	}

	std::vector<Channel> initialiseChannels(ModPlugFile& file)
	{
		const std::size_t numChannels = ModPlug_NumChannels(&file);
		MODCHANNEL* channelsFromModPlug = ModPlug_GetChannels(&file);
		MODCHANNELSETTINGS* channelSettingsFromModPlug = ModPlug_GetChannelsSettings(&file);
		std::vector<Channel> channels;
		channels.reserve(numChannels);

		std::vector<std::vector<ModPlugNote> > notes = getAllNotes(file, numChannels);
		for (auto i = 0; i < numChannels; ++i)
		{
			MODCHANNEL channelInfo = channelsFromModPlug[i];
			MODCHANNELSETTINGS channelSettings;
			if (i < MAX_BASECHANNELS)
			{
				channelSettings = channelSettingsFromModPlug[i];
			}
			channels.push_back(Channel(channelInfo, channelSettings, notes[i]));
		}		
		return channels;
	}

	std::vector<Instrument> initialiseInstruments(ModPlugFile& file)
	{
		const std::size_t numInstruments = ModPlug_NumInstruments(&file);
		std::vector<Instrument> instruments;
		instruments.reserve(numInstruments);
		MODINSTRUMENT* instrumentsFromModPlug = ModPlug_GetInstruments(&file);

		for (auto i = 0; i < numInstruments; ++i)
		{
			MODINSTRUMENT instrument = instrumentsFromModPlug[i];
			INSTRUMENTHEADER header;
			instruments.push_back(Instrument(instrument, header));
		}

		return instruments;
	}

	std::vector<Sample> initialiseSamples(ModPlugFile& file)
	{
		const std::size_t numSamples = ModPlug_NumSamples(&file);
		std::vector<Sample> samples;
		return samples;
	}
}

SoundFile::SoundFile(const std::string& fullPathOfFile)
{
	ModPlugFileHandle fileHandle(getHandle(fullPathOfFile));
	m_channels = initialiseChannels(*fileHandle);
	m_instruments = initialiseInstruments(*fileHandle);
	m_samples = initialiseSamples(*fileHandle);

	const std::size_t numChannels = ModPlug_NumChannels(fileHandle.get());
	const std::size_t numPatterns = ModPlug_NumPatterns(fileHandle.get());
	const std::size_t numInstruments = ModPlug_NumInstruments(fileHandle.get());
	const std::size_t numSamples = ModPlug_NumSamples(fileHandle.get());
	for (int i = 0; i < numPatterns; ++i)
	{
		if (i == 1)
		{
			std::cout << "Pattern: " << i << std::endl;
			unsigned int numRows;
			ModPlugNote* notes = ModPlug_GetPattern(fileHandle.get(), i, &numRows);
			for (unsigned int row = 0; row < numRows * numChannels; ++row)
			{

				std::cout << "Row num: " << row;
				const ModPlugNote& note = notes[row];
				std::cout << "Note: " << note.Note
					<< " Instrument:" << static_cast<int>(note.Instrument)
					//<< " VolumeEffect:" << static_cast<int>(note.VolumeEffect)
					//<< " Effect:" << static_cast<int>(note.Effect)
					//<< " Volume:" << static_cast<int>(note.Volume)
					<< " Parameter: " << static_cast<int>(note.Parameter)
					<< std::endl;
			}
		}
	}	
	
}


/// Generate a CSoundFile from this file
std::unique_ptr<CSoundFile> SoundFile::makeCSoundFile(void) const
{
	return nullptr;
}