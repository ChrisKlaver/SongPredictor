#include "ModPlugFileHandle.h"
#include "modplug.h"
	
ModExtractor::ModPlugFileHandle::ModPlugFileHandle(_ModPlugFile* modPlugFile) :m_modPlugFile( modPlugFile )
{
}

ModExtractor::ModPlugFileHandle::~ModPlugFileHandle(void)
{
	ModPlug_Unload(m_modPlugFile);
}

_ModPlugFile* ModExtractor::ModPlugFileHandle::get(void)
{
	return m_modPlugFile;
}

