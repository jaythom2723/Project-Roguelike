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
	if (b.x < 0 || b.x > (RTGRIDMAP_COLS-1) || b.y < 0 || b.y > (RTGRIDMAP_ROWS-1))
		return;
	
	RTGridCell* cell1, * cell2;
	int cMask1, cMask2;

	if (a == b)
		return;

	cell1 = &(map[a.y][a.x]);
	cell2 = &(map[b.y][b.x]);
	cMask1 = cell1->entity->getCollisionMask();
	cMask2 = cell2->entity ? cell2->entity->getCollisionMask() : -1;

	if (cMask1 == cMask2 && !cell2->passThrough)
		return;

	cell2->entity = cell1->entity;
	if (cell2->entity == nullptr)
		return;
	
	cell2->passThrough = cell2->entity->isSolid();
	cell2->passThrough = cell2->entity ? !cell2->entity->isSolid() : true;
	cell2->entity->setPos(cell2->worldPos);
	cell2->entity->setCell(cell2);

	cell1->passThrough = true;
	cell1->entity = nullptr;
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

const RTGridCell* RTGridMap::getGridCell(int row, int col)
{
	if (row > RTGRIDMAP_ROWS - 1 || col > RTGRIDMAP_COLS - 1)
		return NULL;

	return &(map[row][col]);
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
