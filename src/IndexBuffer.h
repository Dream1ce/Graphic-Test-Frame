#pragma once
#include<gl/glew.h>


class IndexBuffer {
private:
	unsigned int m_IndexBufferID;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int *data, unsigned int size);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	inline unsigned int GetCount() const { return m_count; }
};