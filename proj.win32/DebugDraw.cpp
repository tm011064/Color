#include "DebugDraw.h"

DebugDraw* DebugDraw::create()
{
 DebugDraw* draw = new DebugDraw();
 draw->autorelease();
 return draw;
}

DebugDraw::DebugDraw()
{
 m_lines = new std::vector<DebugLine>();
 m_points = new std::vector<DebugPoint>();
 m_circles = new std::vector<DebugCircle>();
 m_rects = new std::vector<DebugRect>(); 
}

DebugDraw::~DebugDraw()
{
  CC_SAFE_DELETE(m_lines);
  CC_SAFE_DELETE(m_points);
  CC_SAFE_DELETE(m_circles);
  CC_SAFE_DELETE(m_rects);
}

void DebugDraw::draw(void)
{
  int c = m_lines->size();
  for (int i = 0; i < c; i++)
  {
    DebugLine line = m_lines->at(i);
    ccDrawColor4B(line.r, line.g,line.b,255);
    ccDrawLine(line.pt1, line.pt2);
  }

  c = m_points->size();
  for (int i = 0; i < c; i++)
  {
    DebugPoint pt = m_points->at(i);
    ccDrawColor4B(pt.r, pt.g,pt.b,255);
    ccDrawPoint(pt.pt);
  }

  c = m_circles->size();
  for (int i = 0; i < c; i++)
  {
    DebugCircle ci = m_circles->at(i);
    ccDrawColor4B(ci.r, ci.g,ci.b,255);
    ccDrawCircle(ci.pt, ci.radius, 0, 100, false, 1, 1);
  }
  c = m_rects->size();
  for (int i = 0; i < c; i++)
  {
    DebugRect ci = m_rects->at(i);
    ccDrawColor4B(ci.r, ci.g,ci.b,255);
    ccDrawRect(ci.pt1, ci.pt2);
  }

  /* 
  // size chart  
  int totalLines = (m_visibleRectRightTop.x - m_visibleRectLeftBottom.x ) / 10;
  int colorIndex = 0;
  for (int i = m_visibleRectLeftBottom.x; i < m_visibleRectRightTop.x; i+= 10)
  {
    switch (colorIndex)
    {
    case 0: ccDrawColor4B(255, 255, 255, 255); break;
    case 1: ccDrawColor4B(255, 0, 0, 255); break;
    case 2: ccDrawColor4B(0, 255, 0, 255); break;
    case 3: ccDrawColor4B(0, 0, 255, 255); break;
    }
    colorIndex += (colorIndex == 3) ? -3 : 1;
   
    ccDrawLine(ccp (i, 0), ccp (i, i/m_visibleRectRightTop.x * m_visibleRectRightTop.y));
  }
  */
}

void DebugDraw::appendLine(CCPoint pt1, CCPoint pt2, float r, float g, float b)
{
 DebugLine line;
 line.pt1 = pt1;
 line.pt2 = pt2;
 line.r = r;
 line.g = g;
 line.b = b;
 m_lines->push_back(line);
}

void DebugDraw::appendPoint(float x, float y, float r, float g, float b)
{
 appendPoint(ccp(x, y), r, g, b);
}

void DebugDraw::appendPoint(CCPoint pt, float r, float g, float b)
{
 DebugPoint dp;
 dp.pt = pt;
 dp.r = r;
 dp.g = g;
 dp.b = b;
 m_points->push_back(dp);
}

void DebugDraw::appendCircle(CCPoint pt, float radius, float r, float g, float b)
{
 DebugCircle dc;
 dc.pt = pt;
 dc.r = r;
 dc.g = g;
 dc.b = b;
 dc.radius = radius;
 m_circles->push_back(dc);
}
void DebugDraw::appendCircle(float x, float y, float radius, float r, float g, float b)
{
 DebugCircle dc;
 dc.pt = ccp(x,y);
 dc.r = r;
 dc.g = g;
 dc.b = b;
 dc.radius = radius;
 m_circles->push_back(dc);
}

void DebugDraw::appendRect(CCPoint pt1, CCPoint pt2, float r, float g, float b)
{
 DebugRect dc;
 dc.pt1 = pt1;
 dc.pt2 = pt2;
 dc.r = r;
 dc.g = g;
 dc.b = b;
 m_rects->push_back(dc);
}