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
	class CPPTABLE_API ETable
	{
	public:
		ETable()
		{

		}

		~ETable()
		{

		}

	private:
		std::unordered_map<columnId_t, std::unordered_map<primaryId_t, EListValue>> m_columnData;
		std::unordered_map<primaryId_t, std::unordered_map<columnId_t, EListValue>> m_rowData;
		EListValue* m_values = nullptr;
	};
}

#endif