#include "tilelayer.h"



TileLayer::TileLayer(int** data, int col, int row): tileIDs(data), columns(col), rows(row){
	;
}
TileLayer::~TileLayer(){
	freeData();
}


int TileLayer::getTileID(int i, int j) const{
	return tileIDs[i][j];
}

int TileLayer::getTileLayerH() const{
	return rows;
}
int TileLayer::getTileLayerW() const{
	return columns;
}


void TileLayer::freeData(){
	for(int i=0; i<rows; ++i){
		delete[] tileIDs[i];
	}
	delete[] tileIDs;
}




