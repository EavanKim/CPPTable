#ifndef SCHEMA_H__
#define SCHEMA_H__

namespace CPPTable
{
	class ESchema : public std::vector<IEntity*>
	{
	public:
		~ESchema()
		{
			vector::~vector();
		}

		void InitRow(ERow& _target)
		{
			_target.clear();
			columnId_t maximum = size();
			for (columnId_t seek = 0; maximum > seek; ++seek)
			{
				_target.push_back(Copy(seek)); // emplace_back이 있는건 알지만 푸쉬로 합니다.
			}
		}

		void ResetRow(ERow& _target)
		{
			if (size() > _target.size())
			{
				columnId_t maximum = size();
				for (columnId_t seek = 0; maximum > seek; ++seek)
				{
					_target.push_back(Copy(seek)); // emplace_back이 있는건 알지만 푸쉬로 합니다.
				}
			}
			else
			{
				columnId_t maximum = size();
				for (columnId_t seek = 0; maximum > seek; ++seek)
				{
					_target.push_back(Copy(seek)); // emplace_back이 있는건 알지만 푸쉬로 합니다.
				}
			}
		}

		IEntity* Copy(columnId_t _col)
		{
			return new IEntity((*this)[_col]);
		}

	private:

	};
}

#endif