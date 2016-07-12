#include "modplug.h"
#include <fstream>
#include <vector>
#include <iostream>

namespace
{
	class ModPlugFileHandle
	{
	public:

		inline ModPlugFileHandle(ModPlugFile* modPlugFile) :m_modPlugFile( modPlugFile ) 
		{
		}

		inline ~ModPlugFileHandle(void)
		{
			ModPlug_Unload(m_modPlugFile);
		}

		inline ModPlugFile* get(void)
		{
			return m_modPlugFile;
		}

	private:
		ModPlugFile* m_modPlugFile;
	};
}

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

		const std::size_t numPatterns = ModPlug_NumPatterns(file.get());
		for (int i = 0; i < numPatterns; ++i)
		{
			std::cout << "Pattern: " << i << std::endl;
			unsigned int numRows;
			ModPlugNote* notes = ModPlug_GetPattern(file.get(), i, &numRows);
			for (unsigned int row = 0; row < numRows; ++row)
			{
				std::cout << "Row num: " << row;
				const ModPlugNote& note = notes[row];
				std::cout << "Note: " << note.Note << " Instrument:" << static_cast<int>(note.Instrument) << std::endl;
				/*
				unsigned char Note;
				unsigned char Instrument;
				unsigned char VolumeEffect;
				unsigned char Effect;
				unsigned char Volume;
				unsigned char Parameter;
				*/
			}
			break;
		}
		
	}
	else
	{
		std::cout << "error";
	}
}