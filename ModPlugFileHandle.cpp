#include "ModPlugFileHandle.h"
#include "modplug.h"

namespace ModExtractor
{
	
	ModPlugFileHandle::ModPlugFileHandle(ModPlugFile* modPlugFile) :m_modPlugFile( modPlugFile )
	{
	}

	ModPlugFileHandle::~ModPlugFileHandle(void)
	{
		ModPlug_Unload(m_modPlugFile);
	}

	ModPlugFile* ModPlugFileHandle::get(void)
	{
		return m_modPlugFile;
	}

}