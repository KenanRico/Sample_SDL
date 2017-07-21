

#ifndef TILE_LAYER_H
#define TILE_LAYER_H
class TileLayer{
	private:
		int** tileIDs;
		int columns;
		int rows;
	public:
		TileLayer() = delete;
		~TileLayer();
		TileLayer(const TileLayer&) = delete;
		TileLayer& operator=(const TileLayer&) = delete;
	public:
		TileLayer(int**, int, int);
	public:
		int getTileID(int,int) const;
		int getTileLayerH() const;
		int getTileLayerW() const;
	private:
		void freeData();
};
#endif
