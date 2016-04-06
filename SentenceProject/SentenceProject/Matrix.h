// Matrix.h
// Jack Murdock
//
//

#ifndef __MATRIX_CLASS_H__
#define __MATRIX_CLASS_H__

class Matrix
{
public:
	Matrix(unsigned long long sizeX, unsigned long long sizeY){
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		data.resize(sizeX);
		for (int i = 0; i < sizeX; ++i)
			data[i].resize(sizeY);
	}

	~Matrix(){
	}


	unsigned long long& at(unsigned long long x, unsigned long long y){
		return data[x][y];
	}

	unsigned long long get_value(unsigned long long x, unsigned long long y){
		return data[x][y];
	}

	void set_value(unsigned long long x, unsigned long long y, unsigned long long value){
		data[x][y]  = value;
	}


private:
	unsigned long long sizeX;
	unsigned long long sizeY;
	vector<vector<unsigned long long>> data;
};


#endif /*__MATRIX_CLASS_H__*/