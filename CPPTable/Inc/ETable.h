#ifndef	TABLE_H__
#define TABLE_H__

/// <summary>
/// 
/// Class ETable
/// 
/// 테이블 내 사용하는 모든 메모리를 저장하는 메모리 맵.
/// 키 값을 통한 랜덤 액세스 가능, 컬럼 추가제거 지원
/// 
/// </summary>

namespace CPPTable
{
	enum QUERY_STATE
	{
		UNKNOWN,
		INITIALIZE,
		PARSE_COMMAND,
		PARSE_DATA
	};

	class ETable
	{
	public:
		ETable()
		{

		}

		~ETable()
		{

		}

		void Query(std::string& _query)
		{
			std::vector<std::string> querySplit = StrSplit(_query, ' ');
			if (0 < querySplit.size())
			{
				if ("select" == querySplit[0])
				{

				}
				else if ("insert" == querySplit[0])
				{

				}
				else if ("create" == querySplit[0])
				{

				}
				else if ("drop" == querySplit[0])
				{

				}
			}
		}

		// Load Save하려면, Data Flush를 시키기 위한 큰 chunk와 이 chunk를 다시 읽어들일 메타데이터 정립이 필요 해 보이는데
		// 시간이 너무 들어가니 잠시 젖혀둡니다.
		void Load(std::filesystem::path _path)
		{
			//FILE* filePtr = nullptr;
			//errno_t error = fopen_s(&filePtr, _path.relative_path().string().c_str(), "w+");
			//if (0 == error)
			//{

			//	fclose(filePtr);
			//	filePtr = nullptr;
			//}
		}

		void Save(std::filesystem::path _path)
		{
			//FILE* filePtr = nullptr;
			//errno_t error = fopen_s(&filePtr, _path.relative_path().string().c_str(), "w+");
			//if (0 == error)
			//{

			//	fclose(filePtr);
			//	filePtr = nullptr;
			//}
		}

	private:
		void Select(columnId_t _targetColumns)
		{

		}

		void Insert(columnId_t _targetColumns, std::string& _insertTarget)
		{
			
		}

		ERTTI TypeCheck(std::string& _value)
		{
			ERTTI result = ERTTI::ERTTI_STRING;

			for (char ch : _value)
			{
				if (0 == std::isdigit(ch))
				{
					if ('.' == ch && ERTTI::ERTTI_FLOAT != result)
					{
						result = ERTTI::ERTTI_FLOAT;
						continue;
					}
					else
					{
						return result;
					}
				}
			}

			return ERTTI::ERTTI_INT; // UNIXTIME Stamp는 INT와 동격으로 취급합니다. 다만 출력할 때 문자열 처리하면 날자로 뺄 수 있도록만 케어하는 내용입니다.
		}

		QUERY_STATE ParseQuery(std::string& _str, QUERY_STATE& _currentState)
		{
			std::string lowParse = ToLower(_str);
			if ("select" == _str)
			{
				return QUERY_STATE::PARSE_COMMAND;
			}
			else if ("insert" == _str)
			{
				return QUERY_STATE::PARSE_COMMAND;
			}
			else
			{
				return QUERY_STATE::PARSE_DATA;
			}
		}

		std::string ToLower(std::string& _str)
		{
			std::string result;

			for (char ch : _str)
			{
				result += std::tolower(ch);
			}

			return result;
		}

		primaryId_t m_indexCounter = 0;
		std::vector<ERTTI> m_columns;
	};
}

#endif