#ifndef ROW_H__
#define ROW_H__

namespace CPPTable
{
	class CPPTABLE_API ERow
	{
	public:
		ERow(std::unordered_map<columnId_t, EListValue*>* _columnData)
			: m_columnData(_columnData)
		{
		}

		bool GetDateTime(columnId_t _col, eDateTime_t& _value)
		{
			if (nullptr != m_columnData)
			{
				std::unordered_map<columnId_t, EListValue*>::const_iterator iter = m_columnData->find(_col);
				if (m_columnData->end() != iter)
				{
					if (ERTTI::ERTTI_DATETIME == iter->second->m_type)
					{
						_value = ((EListValue_DATETIME*)iter->second)->m_data;

						return true;
					}
				}
			}

			return false;
		}

		bool GetInt(columnId_t _col, eInt_t& _value)
		{
			if (nullptr != m_columnData)
			{
				std::unordered_map<columnId_t, EListValue*>::const_iterator iter = m_columnData->find(_col);
				if (m_columnData->end() != iter)
				{
					if (ERTTI::ERTTI_INT == iter->second->m_type)
					{
						_value = ((EListValue_INT*)iter->second)->m_data;

						return true;
					}
				}
			}

			return false;
		}

		bool GetFloat(columnId_t _col, eFloat_t& _value)
		{
			if (nullptr != m_columnData)
			{
				std::unordered_map<columnId_t, EListValue*>::const_iterator iter = m_columnData->find(_col);
				if (m_columnData->end() != iter)
				{
					if (ERTTI::ERTTI_DATETIME == iter->second->m_type)
					{
						_value = ((EListValue_FLOAT*)iter->second)->m_data;

						return true;
					}
				}
			}

			return false;
		}

		bool GetString(columnId_t _col, eStr_t& _value)
		{
			if (nullptr != m_columnData)
			{
				std::unordered_map<columnId_t, EListValue*>::const_iterator iter = m_columnData->find(_col);
				if (m_columnData->end() != iter)
				{
					if (ERTTI::ERTTI_DATETIME == iter->second->m_type)
					{
						_value = ((EListValue_STRING*)iter->second)->m_data;

						return true;
					}
				}
			}

			return false;
		}

	private:
		std::unordered_map<columnId_t, EListValue*>* m_columnData = nullptr;
	};
}

#endif