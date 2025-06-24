#include "rotex_grid_map.h"

#include "rotex.h"

RTGridMap::RTGridMap()
{
	int i, j;

	// generate each grid cell in the map
	for (i = 0; i < RTGRIDMAP_ROWS; i++)
	{
		for (j = 0; j < RTGRIDMAP_COLS; j++)
		{
			float worldX, worldY;
			worldX = (float)(0 + (16 * j));
			worldY = (float)(0 + (16 * i));

			map[i][j].gridPos = RTVec2<int>(j, i);
			map[i][j].worldPos = RTVec2<float>(worldX, worldY);
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

	// clear each grid cell individually
	for (i = 0; i < RTGRIDMAP_ROWS; i++)
	{
		for (j = 0; j < RTGRIDMAP_COLS; j++)
		{
			clearGridCell(RTVec2<int>(j, i));
		}
	}
}

// set a cell in the grid to an entity value
void RTGridMap::setGridCell(const RTVec2<int> coord, std::shared_ptr<RTEntity> entity)
{
	// get the cell we want to operate on
	RTGridCell* cell = &(map[coord.y][coord.x]);

	cell->entity = entity;
	cell->passThrough = !entity->isSolid();
	entity->setCell(cell);
}

// clear a single grid cell
void RTGridMap::clearGridCell(const RTVec2<int> coord)
{
	// get the cell we want to operate on
	RTGridCell* cell = &(map[coord.y][coord.x]);

	cell->entity->setCell(nullptr); // clear the cell's entity value
	cell->entity.reset();			// reset the shared pointer just to be safe
	cell->passThrough = true;		// allow other entities to move through the cell
}

// just like clearGridCell(const RTVec2<int> coord), just with a pointer instead
void RTGridMap::clearGridCell(RTGridCell* cell)
{
	cell->entity->setCell(nullptr);
	cell->entity.reset();
	cell->passThrough = true;
}

// moving from a TO b
void RTGridMap::moveGridCell(const RTVec2<int> a, const RTVec2<int> b)
{
	// if the entity tries to move out of bounds, do nothing
	if (b.x < 0 || b.x > (RTGRIDMAP_COLS-1) || b.y < 0 || b.y > (RTGRIDMAP_ROWS-1))
		return;
	
	RTGridCell* cell1, * cell2;		// cells being operated on
	int cMask1, cMask2;				// collision masks

	if (a == b)
		return;

	cell1 = &(map[a.y][a.x]);		// get cell1 (A)
	cell2 = &(map[b.y][b.x]);		// get cell2 (B)
	cMask1 = cell1->entity->getCollisionMask();
	// check if cell2's entity exists, if not, there is no collision mask to worry about
	cMask2 = cell2->entity ? cell2->entity->getCollisionMask() : -1;

	// if we can't pass through the cell, do nothing
	if (cMask1 == cMask2 && !cell2->passThrough)
		return;

	// move the entity shared pointer over to cell2 from cell1
	cell2->entity = cell1->entity;
	if (cell2->entity == nullptr) // if the entity that was moved over was nullptr, do nothing
		return;
	
	cell2->passThrough = cell2->entity ? !cell2->entity->isSolid() : true;	// set pass through based on the entity's solid value
	cell2->entity->setPos(cell2->worldPos);									// set the entity's new world position to cell2's world pos
	cell2->entity->setCell(cell2);											// set the entity's own cell reference to cell2
	
	clearGridCell(cell1); // clear cell1
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

			/*
				TODO: remove at some point
					  - or make a different character
			*/
			SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0xff, 0xff, 0xff, 0xff);
			SDL_RenderPoint(RTRENDERER->getHandle(), cell->worldPos.x, cell->worldPos.y);
			SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0x00, 0x00, 0x00, 0xff);
			
		}
	}
}
