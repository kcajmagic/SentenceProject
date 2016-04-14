// Matrix.h
// Jack Murdock
//
//

#ifndef __MATRIX_CLASS_H__
#define __MATRIX_CLASS_H__

class Matrix
{
public:
	Matrix(uint32_t sizeX, uint32_t sizeY){
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		data.resize(sizeX);
		for (int i = 0; i < sizeX; ++i)
			data[i].resize(sizeY);
	}

	~Matrix(){
	}


	uint32_t& at(uint32_t x, uint32_t y){
		return data[x][y];
	}

	uint32_t get_value(uint32_t x, uint32_t y){
		return data[x][y];
	}

	void set_value(uint32_t x, uint32_t y, uint32_t value){
		data[x][y]  = value;
	}


private:
	uint32_t sizeX;
	uint32_t sizeY;
	vector<vector<uint32_t>> data;
};


#endif /*__MATRIX_CLASS_H__*/