#include "rotex_grid_map.h"

#include "rotex.h"

RTGridMap::RTGridMap()
{
	int i, j;

	// generate the world positions of the grid cells
	for (i = 0; i < RTGRIDMAP_ROWS; i++)
	{
		for (j = 0; j < RTGRIDMAP_COLS; j++)
		{
			map[i][j].gridPos = RTVec2<int>(j, i);
			map[i][j].worldPos = RTVec2<float>((float)(0 + (16 * j)), (float)(0 + (16 * i)));
			map[i][j].entity = nullptr;
			map[i][j].passThrough = true;
		}
	}
}

RTGridMap::~RTGridMap()
{
	resetGridMap();
}
	
void RTGridMap::resetGridMap()
{
	int i, j;

	for (i = 0; i < RTGRIDMAP_ROWS; i++)
	{
		for (j = 0; j < RTGRIDMAP_COLS; j++)
		{
			clearGridCell(RTVec2<int>(j, i));
		}
	}
}

void RTGridMap::setGridCell(const RTVec2<int> coord, std::shared_ptr<RTEntity> entity)
{
	RTGridCell* cell = &(map[coord.y][coord.x]);

	cell->entity = entity;
	cell->passThrough = !entity->isSolid();
	entity->setCell(cell);
}

void RTGridMap::clearGridCell(const RTVec2<int> coord)
{
	RTGridCell* cell = &(map[coord.y][coord.x]);

	cell->entity->setCell(nullptr);
	cell->entity.reset();
	cell->passThrough = true;
}

// a -> b
// moving from a TO b
void RTGridMap::moveGridCell(const RTVec2<int> a, const RTVec2<int> b)
{
	if (b.x < 0 || b.x > RTGRIDMAP_COLS || b.y < 0 || b.y > RTGRIDMAP_ROWS)
		return;
	
	RTGridCell* cell1, * cell2;

	cell1 = &(map[a.y][a.x]);
	cell2 = &(map[b.y][b.x]);

	if (!cell2->passThrough)
		return;

	printf("should move\n");
	printf("(%d,%d)\n", b.x, b.y);

	cell2->entity = cell1->entity;
	cell2->passThrough = !cell2->entity->isSolid();
	cell2->entity->setPos(cell2->worldPos);
	cell2->entity->setCell(cell2);

	cell1->entity = nullptr;
	cell1->passThrough = true;
}

bool RTGridMap::isGridCellPassThrough(const RTVec2<int> coord)
{
	return map[coord.y][coord.x].passThrough;
}

bool RTGridMap::isGridCellEmpty(const RTVec2<int> coord)
{
	return map[coord.y][coord.x].entity == nullptr;
}

const RTVec2<float> RTGridMap::gridCellToWorldPosition(const RTVec2<int> coord)
{
	return map[coord.y][coord.x].worldPos;
}

void RTGridMap::draw()
{
	int row, col;
	RTGridCell* cell;
	RTVec2<float> pos = RTVEC2FZERO;

	for (row = 0; row < RTGRIDMAP_ROWS; row++)
	{
		for (col = 0; col < RTGRIDMAP_COLS; col++)
		{
			cell = &(map[row][col]);

			if (cell->entity != nullptr && cell->entity->isVisible())
				cell->entity->draw();

			SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0xff, 0xff, 0xff, 0xff);
			SDL_RenderPoint(RTRENDERER->getHandle(), cell->worldPos.x, cell->worldPos.y);
			SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0x00, 0x00, 0x00, 0xff);
		}
	}
}
