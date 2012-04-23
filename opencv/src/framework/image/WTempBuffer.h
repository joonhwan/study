#pragma once

template<typename T, int C>
struct IppBuffer
{
public:
	IppBuffer(int width, int height)
		: m_size(width, height)
	{
		allocate();
	}
	IppBuffer(const QSize& size)
		: m_size(size)
	{
		allocate();
	}
	virtual ~IppBuffer()
	{
		deallocate();
	}
	void allocate()
	{
		if (m_buffer) {
			deallocate();
		}
		allocateImpl();
	}
	void deallocate()
	{
		if (m_buffer) {
			ippiFree((void*)m_buffer);
			m_buffer = 0;
			m_size = QSize(0,0);
			m_stepBytes = 0;
		}
	}
protected:
	T* m_buffer;
	QSize m_size;
	int m_stepBytes;

	void allocateImpl();
};

template<typename T, int C>
class WTempBuffer
{
public:

private:
	QSharedDataPointer< IppBuffer<T, C> > d;
};


