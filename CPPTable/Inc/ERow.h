#ifndef ROW_H__
#define ROW_H__

namespace CPPTable
{
	struct EStrBlock
	{
		char m_str[16];
	};

	class EStrPage
	{
	public:
		EStrBlock m_block[256];
	};

	class ERow : public std::vector<IEntity*>
	{
	public:
		~ERow()
		{
			vector::~vector();
		}

	private:
		std::list<EStrPage> m_strPages;
	};
}

#endif