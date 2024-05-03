#ifndef ROW_H__
#define ROW_H__

namespace CPPTable
{
	class ERow : public std::vector<IEntity*>
	{
	public:
		~ERow()
		{
			vector::~vector();
		}

	private:
		
	};
}

#endif