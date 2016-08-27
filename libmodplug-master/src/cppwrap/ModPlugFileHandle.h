#ifndef H_MODPLUGFILEHANDLE
#define H_MODPLUGFILEHANDLE

struct _ModPlugFile;

#include <memory>

namespace ModExtractor
{
	using ModPlugFileHandle = std::shared_ptr < ModPlugFile*, [](ModPlugFile* file) { ModPlug_Unload*(file); } );
}

#endif