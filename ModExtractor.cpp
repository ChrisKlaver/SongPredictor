#include "modplug.h"
#include "SoundFile.h"
#include <iostream>

using namespace ModExtractor;

int main(int argc, char** argv)
{
	try
	{
		const SoundFile("F:\\think_twice_iii.mod");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}