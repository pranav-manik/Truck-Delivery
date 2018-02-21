#include "Delivery.h"

using namespace std;


//Name: Delivery and Delivery(name, numItem, rtMinute) - Constructors
//Precondition: None
//Postcondition: Creates a delivery
Delivery::Delivery()
{

}

Delivery::Delivery(string name, int numItem, int rtMinute)
{
  m_name = name;
  m_numItem = numItem;
  m_rtMinute = rtMinute;
}

//Name: GetName, GetNumItem
//Precondition: None
//Postcondition: Returns various class values

string Delivery::GetName() const
{
  return m_name;
}


int Delivery::GetNumItem() const
{
  return m_numItem;
}

int Delivery::GetRTMinute() const
{
  return m_rtMinute;
}
