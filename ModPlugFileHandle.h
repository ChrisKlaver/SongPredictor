#ifndef H_MODPLUGFILEHANDLE
#define H_MODPLUGFILEHANDLE

class ModPlugFile;

namespace ModExtractor
{
	class ModPlugFileHandle
	{
	public:

		/// C'tor take ownership of pointer!
		ModPlugFileHandle(ModPlugFile* modPlugFile);
		
		~ModPlugFileHandle(void);

		ModPlugFile* get(void);
		
	private:

		ModPlugFile* m_modPlugFile;
	};
}

#endif