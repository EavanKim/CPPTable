#pragma once

class CPPTABLE_API EColumnAllocator
{
public:
	EColumnAllocator(memSize_t _count, memSize_t _size, ERTTI _columnType)
		: blockCount(_count)
		, paddingSize((16 - (_size % 16)) % (~16))
		, blockSize(_size + ((16 - (_size % 16)) % (~16)))
		, totalSize((_size + ((16 - (_size % 16)) % (~16)))* _count)
		, type(_columnType)
	{
		m_data = new EBYTE[totalSize];

		INTPTR start = ParsePtr(m_data);
		INTPTR end = start + totalSize;
		for (INTPTR seek = start; end > seek; seek += blockSize)
		{
			switch (type)
			{
			case ERTTI::ERTTI_DATETIME:
				new (ParsePtr(seek)) EListValue_DATETIME(0, 0, nullptr, nullptr);
				break;
			case ERTTI::ERTTI_FLOAT:
				new (ParsePtr(seek)) EListValue_FLOAT(0, 0, nullptr, nullptr);
				break;
			case ERTTI::ERTTI_INT:
				new (ParsePtr(seek)) EListValue_INT(0, 0, nullptr, nullptr);
				break;
			case ERTTI::ERTTI_STRING:
				new (ParsePtr(seek)) EListValue_STRING(0, 0, nullptr, nullptr);
				break;
			}
		}
	}

	~EColumnAllocator()
	{
		if (nullptr != m_data)
		{
			delete m_data;
			m_data = nullptr;
		}
	}

	EListValue* EMalloc(primaryId_t _pri, columnId_t _col)
	{
		INTPTR start = ParsePtr(m_data);
		INTPTR end = start + totalSize;
		for (INTPTR seek = start; end > seek; seek += blockSize)
		{
			EListValue* header = (EListValue*)ParsePtr(seek);
			if (header->free_)
			{
				header->free_ = false;
				return header;
			}
		}

		return nullptr;
	}

private:
	const memSize_t blockCount = 0;
	const memSize_t blockSize = 0;
	const memSize_t paddingSize = 0;
	const memSize_t totalSize = 0;
	ERTTI type = ERTTI::ERTTI_UNKNOWN;
	EBYTE* m_data = nullptr;
};