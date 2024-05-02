#ifndef SCHEMA_H__
#define SCHEMA_H__

namespace CPPTable
{
	class ESchema : public std::vector<IEntity*>
	{
	public:
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
			if (nullptr != target)
			{
				switch (target->m_type)
				{
				case ERTTI::ERTTI_DATETIME:
					return new Entity_Datetime(target); // 자체 데이터에 기본값을 저장했다가 IEntity 처리로 기본값 처리
				case ERTTI::ERTTI_INT:
					return new Entity_Int(target); // 자체 데이터에 기본값을 저장했다가 IEntity 처리로 기본값 처리
				case ERTTI::ERTTI_FLOAT:
					return new Entity_Float(target); // 자체 데이터에 기본값을 저장했다가 IEntity 처리로 기본값 처리
				case ERTTI::ERTTI_STRING:
					return new Entity_String(target); // 자체 데이터에 기본값을 저장했다가 IEntity 처리로 기본값 처리
				}
			}

			return nullptr;
		}

	private:

	};
}

#endif