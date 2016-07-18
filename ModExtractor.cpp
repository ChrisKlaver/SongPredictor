#include "modplug.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "ModPlugFileHandle.h"

using namespace ModExtractor;

int main(int argc, char** argv)
{
	std::ifstream file("F:\\think_twice_iii.mod", std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(static_cast<std::size_t>(size));
	if (file.read(buffer.data(), size) && size != 0 )
	{
		ModPlugFileHandle file{ ModPlug_Load(&(*buffer.begin()), static_cast<int>(buffer.size())) };
		if (file.get())
		{
			std::cout << "worked";
		}

		const std::size_t numChannels = ModPlug_NumChannels(file.get());
		const std::size_t numPatterns = ModPlug_NumPatterns(file.get());
		for (int i = 0; i < numPatterns * numChannels; ++i)
		{
			std::cout << "Pattern: " << i << std::endl;
			unsigned int numRows;
			ModPlugNote* notes = ModPlug_GetPatternAtOrder(file.get(), i, &numRows);
			for (unsigned int row = 0; row < numRows; ++row)
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
			if (i == 0) break;
		}
		
	}
	else
	{
		std::cout << "error";
	}
}