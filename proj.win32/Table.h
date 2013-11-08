#ifndef __TABLE_H__
#define __TABLE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

using namespace cocos2d;

enum TableCellTextAlignment
{
  LEFT = 0,
  CENTER = 1,
  RIGHT = 2,
  TOP = 3,
  BOTTOM = 4
};

typedef struct
{
  float top;
  float left;
  float bottom;
  float right;
} Dimension;

typedef struct 
{
  bool isBorderVisible;
  ccColor4F borderColor;
  Dimension borderThickness;
  Dimension padding;

  ccColor4F backgroundColor;
  ccColor3B foregroundColor;
  std::string fontNamePath;

  TableCellTextAlignment horizontalTextAlignment;
  TableCellTextAlignment verticalTextAlignment;

  CCSize size;

} CellStyle;

typedef struct
{
  ccColor4F color;
  CCPoint leftBottom;
  CCPoint rightTop;
} DrawRectangleElementDefinition;

typedef struct 
{
  CellStyle headerStyle;
  CellStyle cellStyle;  
} TableColumn;

typedef struct 
{
  bool hasBorder;
  DrawRectangleElementDefinition borderLeft;
  DrawRectangleElementDefinition borderTop;
  DrawRectangleElementDefinition borderRight;
  DrawRectangleElementDefinition borderBottom;

  DrawRectangleElementDefinition fill;

  CCLabelBMFont* label;

} TableCell;

typedef struct 
{
  std::vector<TableCell> cells;
  CCPoint leftBottom;
  CCPoint rightTop;

  float height;

} TableRow;

class Table : public BaseNode
{ 
private:

  GameContext* m_pGameContext;

  CCSize m_size;

  std::vector<TableColumn> m_columns;
  std::vector<TableRow> m_rows;
  std::vector<TableRow> m_headers;
  
  bool m_isUpdatingLayout;

protected:
  Table(GameContext* gameContext) 
    : m_pGameContext(gameContext)
    , m_isUpdatingLayout(false)
  { }

public:
  static Table* create(GameContext* gameContext)
  {
    Table* table = new Table(gameContext);
    table->autorelease();
    return table;
  }
  ~Table() { }
  
  virtual void draw();

  CCSize getSize() { return m_size; }

  void beginLayoutUpdate() { m_isUpdatingLayout = true; }
  void endLayoutUpdate();

  void addColumn(TableColumn column);
  void addHeader(std::vector<std::string> cellValues);
  void addRow(std::vector<std::string> cellValues);

};
#endif  // __TABLE_H__