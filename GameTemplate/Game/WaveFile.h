#pragma once

#include <thread>
#include <string>

class WaveFile
{
private:
	std::unique_ptr<char[]> m_readBuffer = nullptr;
	HMMIO m_hmmio = nullptr;
	WAVEFORMATEX* m_pwfx = nullptr;
	MMCKINFO m_ckRiff;
	DWORD m_dwSize = 0;
	MMCKINFO m_ck;
	BYTE* m_pbData = nullptr;
	BYTE* m_pbDataCur = nullptr;
	ULONG m_ulDataSize = 0;
	volatile bool m_isReadEnd = true;
	std::thread m_readAsyncThread;
	bool m_isInvokeReadAsyncThread = false;
	std::wstring m_filePath;
	unsigned int m_filePathHash = 0;
public:
	WaveFile();
	~WaveFile();

	bool Open(const wchar_t* fileName);

	void Read(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize);

	void ReadAsync(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize);

	bool IsReadEnd() const
	{
		return m_isReadEnd;
	}

	void ResetFile();

	void Release();

	DWORD GetSize() const
	{
		return m_dwSize;
	}

	WAVEFORMATEX* GetFormat() const
	{
		return m_pwfx;
	}

	unsigned int GetFilePathHash() const
	{
		return m_filePathHash;
	}

	void AllocReadBuffer(int size)
	{
		m_readBuffer.reset(new char[size]);
	}

	char* GetReadBuffer()
	{
		return m_readBuffer.get();
	}

};

