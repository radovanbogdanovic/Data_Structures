#pragma once

class BinaryMinHeapInt
{
private:
	int* array;
	long length;
	long numOfElements;

public:
	BinaryMinHeapInt(long len);
	~BinaryMinHeapInt() { delete[] array; };

	bool isEmpty() const { return numOfElements == 0; };
	int getFirst() const;

	void insert(int el);
	int deleteRoot();

	void UpdateElement(int el, int value);
};
