#include "ModPlugFileHandle.h"
#include "modplug.h"
	
using namespace ModExtractor;

ModPlugFileHandle::ModPlugFileHandle(_ModPlugFile* modPlugFile) :m_modPlugFile( modPlugFile )
{
}

ModPlugFileHandle::~ModPlugFileHandle(void)
{
	ModPlug_Unload(m_modPlugFile);
}

_ModPlugFile* ModPlugFileHandle::get(void)
{
	return m_modPlugFile;
}

