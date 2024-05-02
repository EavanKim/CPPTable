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

		}

		void Save(std::filesystem::path _path)
		{
			FILE* filePtr = nullptr;
			errno_t error = fopen_s(&filePtr, _path.relative_path().string().c_str(), "w+");
			if (0 == error)
			{
				fclose(filePtr);
				filePtr = nullptr;
			}
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

		primaryId_t m_indexCounter = 0;
		std::vector<ERTTI> m_columns;
	};
}

#endif