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

		// time to export it again
		/*Export to a Impulse Tracker IT file. Should work OK in Little-Endian & Big-Endian platforms :-) */
		const char* const path = "f:\\thinktwice.it";
		const char retCode = ModPlug_ExportIT(file.get(), path);

		std::cout << retCode;
	}
	else
	{
		std::cout << "error";
	}
}