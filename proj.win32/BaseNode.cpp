#include "BaseNode.h"

void BaseNode::show()
{  
  CCObject* o;
  CCARRAY_FOREACH(this->getChildren(), o)
  {    
    CCNode* node = dynamic_cast<CCNode*>(o);
    if (node != NULL)
    {
      BaseNode* baseNode = dynamic_cast<BaseNode*>(node);
      if (baseNode != NULL)
      {
        baseNode->show();
      }
      else
      {
        node->setVisible(true);
      }
    }
  }
  this->setVisible(true);
} 
void BaseNode::hide()
{
  CCObject* o;
  CCARRAY_FOREACH(this->getChildren(), o)
  {    
    CCNode* node = dynamic_cast<CCNode*>(o);
    if (node != NULL)
    {
      BaseNode* baseNode = dynamic_cast<BaseNode*>(node);
      if (baseNode != NULL)
      {
        baseNode->hide();
      }
      else
      {
        node->setVisible(false);
      }
    }
  }
  this->setVisible(false);
} 