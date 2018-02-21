#include "Item.h"

using namespace std;


//Name: Item() and Item(string, float) - Default and Overloaded Constructor
//Precondition: None
//Postcondition: Creates an item
Item::Item()
{
  
}

Item::Item(string iName, float iWeight)
{
  m_name = iName;
  m_weight = iWeight;
}

//Returns Items Name
string Item::GetName() const
{
  return m_name;
}

//Returns Items weight
float Item::GetWeight() const
{
  return m_weight;
}
