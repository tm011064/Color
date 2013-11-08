#include "Table.h"


void Table::addHeader(std::vector<std::string> cellValues)
{
  TableRow row;
  int totalColumns = m_columns.size();
  for (int i = 0; i < totalColumns; ++i)
  {
    TableCell cell;
    cell.label = CCLabelBMFont::create(cellValues[i].c_str(), m_columns[i].headerStyle.fontNamePath.c_str());
    cell.label->setScale(m_pGameContext->getFontScale());
    cell.label->setColor(m_columns[i].headerStyle.foregroundColor);
    this->addChild(cell.label);
    row.cells.push_back(cell);
  }
  m_headers.push_back(row);

  if ( !m_isUpdatingLayout )
    this->endLayoutUpdate();
}

void Table::addRow(std::vector<std::string> cellValues)
{
  TableRow row;
  int totalColumns = m_columns.size();
  for (int i = 0; i < totalColumns; ++i)
  {
    TableCell cell;
    cell.label = CCLabelBMFont::create(cellValues[i].c_str(), m_columns[i].cellStyle.fontNamePath.c_str());
    cell.label->setScale(m_pGameContext->getFontScale());
    cell.label->setColor(m_columns[i].cellStyle.foregroundColor);
    this->addChild(cell.label);
    row.cells.push_back(cell);
  }
  m_rows.push_back(row);

  if ( !m_isUpdatingLayout )
    this->endLayoutUpdate();
}

void Table::addColumn(TableColumn column)
{
  m_columns.push_back(column);
  
  if ( !m_isUpdatingLayout )
    this->endLayoutUpdate();
}

void Table::endLayoutUpdate()
{
  int totalColumns = m_columns.size();
  int cellIndex;
  float posLeftX = .0f
      , posRightX = .0f
      , posTopY = .0f
      , posBottomY = .0f
      , headerRowHeight = .0f
      , cellRowHeight = .0f;

  // headers
  std::vector< TableRow >::iterator rowIterator;
  std::vector< TableCell >::iterator cellIterator;
  for(rowIterator=m_headers.begin();rowIterator!=m_headers.end();++rowIterator)
  {
    cellIndex = 0;
    posLeftX = .0f;
    headerRowHeight = .0f;
    posTopY = posBottomY;
    for(cellIterator=rowIterator->cells.begin();cellIterator!=rowIterator->cells.end() && cellIndex < totalColumns; ++cellIterator)
    {
      if ( m_columns[cellIndex].headerStyle.size.height > headerRowHeight )
        headerRowHeight = m_columns[cellIndex].headerStyle.size.height;

      posBottomY = posTopY - m_columns[cellIndex].headerStyle.size.height;
      posRightX = posLeftX + m_columns[cellIndex].headerStyle.size.width;

      cellIterator->hasBorder = m_columns[cellIndex].headerStyle.isBorderVisible;
      if ( cellIterator->hasBorder )
      {
        // left     
        cellIterator->borderLeft.leftBottom.setPoint(
          posLeftX
          , posBottomY);
        cellIterator->borderLeft.rightTop.setPoint(
          posLeftX + m_columns[cellIndex].headerStyle.borderThickness.left
          , posTopY + m_columns[cellIndex].headerStyle.borderThickness.top);
        cellIterator->borderLeft.color = m_columns[cellIndex].headerStyle.borderColor;

        // top
        cellIterator->borderTop.leftBottom.setPoint(
          posLeftX
          , posTopY);
        cellIterator->borderTop.rightTop.setPoint(
          posRightX + m_columns[cellIndex].headerStyle.borderThickness.right
          , posTopY + m_columns[cellIndex].headerStyle.borderThickness.top);
        cellIterator->borderTop.color = m_columns[cellIndex].headerStyle.borderColor;

        // right
        cellIterator->borderRight.leftBottom.setPoint(
          posRightX
          , posBottomY + m_columns[cellIndex].headerStyle.borderThickness.bottom);
        cellIterator->borderRight.rightTop.setPoint(
          posRightX + m_columns[cellIndex].headerStyle.borderThickness.right
          , posTopY);
        cellIterator->borderRight.color = m_columns[cellIndex].headerStyle.borderColor;
                
        // bottom         
        cellIterator->borderBottom.leftBottom.setPoint(
          posLeftX - m_columns[cellIndex].headerStyle.borderThickness.left
          , posBottomY + m_columns[cellIndex].headerStyle.borderThickness.bottom);
        cellIterator->borderBottom.rightTop.setPoint(
          posRightX
          , posBottomY);        
        cellIterator->borderBottom.color = m_columns[cellIndex].headerStyle.borderColor;
      }

      cellIterator->fill.leftBottom.setPoint(posLeftX, posBottomY);
      cellIterator->fill.rightTop.setPoint(posRightX, posTopY);
      cellIterator->fill.color = m_columns[cellIndex].headerStyle.backgroundColor;

      switch ( m_columns[cellIndex].headerStyle.horizontalTextAlignment )
      {
      case LEFT: cellIterator->label->setPositionX(posLeftX + m_columns[cellIndex].headerStyle.padding.left + cellIterator->label->getContentSize().width/2*m_pGameContext->getFontScale()); break;
      case CENTER: cellIterator->label->setPositionX(posLeftX + (posRightX - posLeftX)/2); break;
      case RIGHT: cellIterator->label->setPositionX(posRightX + m_columns[cellIndex].headerStyle.padding.right - cellIterator->label->getContentSize().width/2*m_pGameContext->getFontScale()); break;
      }
      switch ( m_columns[cellIndex].headerStyle.verticalTextAlignment )
      {
      case TOP: cellIterator->label->setPositionY(posTopY + m_columns[cellIndex].headerStyle.padding.top - cellIterator->label->getContentSize().height/2*m_pGameContext->getFontScale()); break;
      case CENTER: cellIterator->label->setPositionY(posBottomY + (posTopY - posBottomY)/2); break;
      case BOTTOM: cellIterator->label->setPositionY(posBottomY + m_columns[cellIndex].headerStyle.padding.bottom + cellIterator->label->getContentSize().width/2*m_pGameContext->getFontScale()); break;
      }

      posLeftX = posRightX;
      cellIndex++;
    }

    posBottomY = posTopY - headerRowHeight;
  }

  // rows
  for(rowIterator=m_rows.begin();rowIterator!=m_rows.end();++rowIterator)
  {
    cellIndex = 0;
    posLeftX = .0f;
    cellRowHeight = .0f;
    posTopY = posBottomY;
    for(cellIterator=rowIterator->cells.begin();cellIterator!=rowIterator->cells.end() && cellIndex < totalColumns; ++cellIterator)
    {
      if ( m_columns[cellIndex].cellStyle.size.height > cellRowHeight )
        cellRowHeight = m_columns[cellIndex].cellStyle.size.height;

      posBottomY = posTopY - m_columns[cellIndex].cellStyle.size.height;
      posRightX = posLeftX + m_columns[cellIndex].cellStyle.size.width;
      
      cellIterator->hasBorder = m_columns[cellIndex].cellStyle.isBorderVisible;
      if ( cellIterator->hasBorder )
      {
        // left     
        cellIterator->borderLeft.leftBottom.setPoint(
          posLeftX
          , posBottomY);
        cellIterator->borderLeft.rightTop.setPoint(
          posLeftX + m_columns[cellIndex].cellStyle.borderThickness.left
          , posTopY + m_columns[cellIndex].cellStyle.borderThickness.top);
        cellIterator->borderLeft.color = m_columns[cellIndex].cellStyle.borderColor;

        // top
        cellIterator->borderTop.leftBottom.setPoint(
          posLeftX
          , posTopY);
        cellIterator->borderTop.rightTop.setPoint(
          posRightX + m_columns[cellIndex].cellStyle.borderThickness.right
          , posTopY + m_columns[cellIndex].cellStyle.borderThickness.top);
        cellIterator->borderTop.color = m_columns[cellIndex].cellStyle.borderColor;

        // right
        cellIterator->borderRight.leftBottom.setPoint(
          posRightX
          , posBottomY + m_columns[cellIndex].cellStyle.borderThickness.bottom);
        cellIterator->borderRight.rightTop.setPoint(
          posRightX + m_columns[cellIndex].cellStyle.borderThickness.right
          , posTopY);
        cellIterator->borderRight.color = m_columns[cellIndex].cellStyle.borderColor;
                
        // bottom         
        cellIterator->borderBottom.leftBottom.setPoint(
          posLeftX - m_columns[cellIndex].cellStyle.borderThickness.left
          , posBottomY + m_columns[cellIndex].cellStyle.borderThickness.bottom);
        cellIterator->borderBottom.rightTop.setPoint(
          posRightX
          , posBottomY);        
        cellIterator->borderBottom.color = m_columns[cellIndex].cellStyle.borderColor;
      }

      cellIterator->fill.leftBottom.setPoint(posLeftX, posBottomY);
      cellIterator->fill.rightTop.setPoint(posRightX, posTopY);
      cellIterator->fill.color = m_columns[cellIndex].cellStyle.backgroundColor;

      switch ( m_columns[cellIndex].cellStyle.horizontalTextAlignment )
      {
      case LEFT: cellIterator->label->setPositionX(posLeftX + m_columns[cellIndex].cellStyle.padding.left + cellIterator->label->getContentSize().width/2*m_pGameContext->getFontScale()); break;
      case CENTER: cellIterator->label->setPositionX(posLeftX + (posRightX - posLeftX)/2); break;
      case RIGHT: cellIterator->label->setPositionX(posRightX + m_columns[cellIndex].cellStyle.padding.right - cellIterator->label->getContentSize().width/2*m_pGameContext->getFontScale()); break;
      }
      switch ( m_columns[cellIndex].cellStyle.verticalTextAlignment )
      {
      case TOP: cellIterator->label->setPositionY(posTopY + m_columns[cellIndex].cellStyle.padding.top - cellIterator->label->getContentSize().height/2*m_pGameContext->getFontScale()); break;
      case CENTER: cellIterator->label->setPositionY(posBottomY + (posTopY - posBottomY)/2); break;
      case BOTTOM: cellIterator->label->setPositionY(posBottomY + m_columns[cellIndex].cellStyle.padding.bottom + cellIterator->label->getContentSize().width/2*m_pGameContext->getFontScale()); break;
      }

      posLeftX = posRightX;
      cellIndex++;
    }

    posBottomY = posTopY - cellRowHeight;
  }

  this->m_size.setSize(posRightX, abs(posTopY - cellRowHeight));

  this->m_isUpdatingLayout = false;
}

void Table::draw()
{  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  std::vector< TableRow >::iterator rowIterator;
  std::vector< TableCell >::iterator cellIterator;
  for(rowIterator=m_headers.begin();rowIterator!=m_headers.end();++rowIterator)
  {
    for(cellIterator=rowIterator->cells.begin();cellIterator!=rowIterator->cells.end(); ++cellIterator)
    {
      ccDrawSolidRect(cellIterator->fill.leftBottom, cellIterator->fill.rightTop, cellIterator->fill.color);
      
      if ( cellIterator->hasBorder )
      {
        ccDrawSolidRect(cellIterator->borderLeft.leftBottom, cellIterator->borderLeft.rightTop, cellIterator->borderLeft.color);
        ccDrawSolidRect(cellIterator->borderTop.leftBottom, cellIterator->borderTop.rightTop, cellIterator->borderTop.color);
        ccDrawSolidRect(cellIterator->borderRight.leftBottom, cellIterator->borderRight.rightTop, cellIterator->borderRight.color);
        ccDrawSolidRect(cellIterator->borderBottom.leftBottom, cellIterator->borderBottom.rightTop, cellIterator->borderBottom.color);
      }
    }
  }
  for(rowIterator=m_rows.begin();rowIterator!=m_rows.end();++rowIterator)
  {
    for(cellIterator=rowIterator->cells.begin();cellIterator!=rowIterator->cells.end(); ++cellIterator)
    {
      ccDrawSolidRect(cellIterator->fill.leftBottom, cellIterator->fill.rightTop, cellIterator->fill.color);

      if ( cellIterator->hasBorder )
      {
        ccDrawSolidRect(cellIterator->borderLeft.leftBottom, cellIterator->borderLeft.rightTop, cellIterator->borderLeft.color);
        ccDrawSolidRect(cellIterator->borderTop.leftBottom, cellIterator->borderTop.rightTop, cellIterator->borderTop.color);
        ccDrawSolidRect(cellIterator->borderRight.leftBottom, cellIterator->borderRight.rightTop, cellIterator->borderRight.color);
        ccDrawSolidRect(cellIterator->borderBottom.leftBottom, cellIterator->borderBottom.rightTop, cellIterator->borderBottom.color);
      }
    }
  }

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}
