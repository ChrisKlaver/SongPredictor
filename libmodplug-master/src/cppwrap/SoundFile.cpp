#include "SoundFile.h"
#include "modplug.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>

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

	std::vector<Channel> initialiseChannels(ModPlugFile& file)
	{
		const std::size_t numChannels = ModPlug_NumChannels(&file);
		std::vector<Channel> channels(numChannels);
		return channels;
	}
}

SoundFile::SoundFile(const std::string& filename)
{
	ModPlugFileHandle fileHandle(getHandle(filename));
	m_channels = initialiseChannels(*fileHandle);

	const std::size_t numChannels = ModPlug_NumChannels(fileHandle.get());
	const std::size_t numPatterns = ModPlug_NumPatterns(fileHandle.get());
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