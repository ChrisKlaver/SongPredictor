#ifndef H_MODPLUGFILEHANDLE
#define H_MODPLUGFILEHANDLE

struct _ModPlugFile;

namespace ModExtractor
{
	class ModPlugFileHandle
	{
	public:

		/// C'tor take ownership of pointer!
		ModPlugFileHandle(_ModPlugFile* modPlugFile);
		
		~ModPlugFileHandle(void);

		_ModPlugFile* get(void);
		
	private:

		_ModPlugFile* m_modPlugFile;
	};
}

#endif