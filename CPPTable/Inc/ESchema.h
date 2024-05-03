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

		void SetRow(ERow& _target)
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
			columnId_t maximum = size();
			for (columnId_t seek = 0; maximum > seek; ++seek)
			{
				_target.push_back(Copy(seek)); // emplace_back이 있는건 알지만 푸쉬로 합니다.
			}
		}

		IEntity* Copy(columnId_t _col)
		{
			IEntity* target = (*this)[_col];

			return nullptr;
		}

	private:

	};
}

#endif