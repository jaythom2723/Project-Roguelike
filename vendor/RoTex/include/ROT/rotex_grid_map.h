#ifndef ROTEX_GRID_MAP_H
#define ROTEX_GRID_MAP_H

#include <memory>
#include <array>

#include "rotex_defs.h"
#include "rotex_vec.h"

#define RTGRIDCELL_SIZE_PX 16

#define RTGRIDMAP_ROWS 35
#define RTGRIDMAP_COLS 40
#define RTGRIDMAP_WIDTH_PX RTGRIDMAP_COLS * RTGRIDCELL_SIZE_PX
#define RTGRIDMAP_HEIGHT_PX RTGRIDMAP_ROWS * RTGRIDCELL_SIZE_PX

class RTEntity;

struct RTGridCell
{
public:
	std::shared_ptr<RTEntity> entity;
	bool passThrough = true;
	RTVec2<int> gridPos = RTVec2<int>(0, 0);
	RTVec2<float> worldPos = RTVec2<float>(0.f, 0.f);
};

class RTGridMap
{
private:
	std::array<std::array<RTGridCell, RTGRIDMAP_COLS>, RTGRIDMAP_ROWS> map;

public:
	ROTEXAPI RTGridMap();
	ROTEXAPI ~RTGridMap();

	ROTEXAPI void resetGridMap();
	ROTEXAPI void setGridCell(const RTVec2<int> coord, std::shared_ptr<RTEntity> entity);
	ROTEXAPI void clearGridCell(const RTVec2<int> coord);
	ROTEXAPI void clearGridCell(RTGridCell* cell);
	ROTEXAPI void moveGridCell(const RTVec2<int> c1, const RTVec2<int> c2);

	ROTEXAPI bool isGridCellPassThrough(const RTVec2<int> coord);
	ROTEXAPI bool isGridCellEmpty(const RTVec2<int> coord);

	ROTEXAPI const RTVec2<float> gridCellToWorldPosition(const RTVec2<int> coords);
	ROTEXAPI const RTGridCell* getGridCell(int row, int col);

	ROTEXAPI void draw();
};

#endif // ROTEX_GRID_MAP_H