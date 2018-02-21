#include "ManageDelivery.h"

using namespace std;

// Constructor for managing the deliveries.
// Once the data has been imported and split used to manage all additonal functions
// One vector for trucks
// One vector for deliveries
// One vector for items
ManageDelivery::ManageDelivery(vector< Truck <Item, MAX_CAPACITY> > truck,
			       vector< Delivery > delivery,
			       vector< Item > item)
{
  m_truck = truck;
  m_delivery = delivery;
  m_item = item;
  
  StartDelivery();
  DisplayItemLeft();
}

//Name: StartDelivery
//Precondition: Requires truck, delivery, and items
//Postcondition: Loads items into a truck
//Additional information: All deliveries must be complete - you cannot split a
//single delivery into two trucks. A single truck can complete more than
void ManageDelivery::StartDelivery()
{
  vector< Delivery > curDelivery = m_delivery;
  int totalCap = 0;
  int curDeliv = 0;
  unsigned int curTruck = 0;
  int curItem = 0;
  //Sets all truck times to 0
  for (unsigned int i = 0; i <m_truck.size(); i++)
    {
      m_truck[i].SetTime(0);
    }
  cout << "Start Time: " << m_truck[curTruck].GetTime() << endl;
  cout << "\n\n*****Loading Truck (" << m_truck[curTruck].GetName() << ")*****" << endl;
  while (curDelivery.size() > 0)
    {
      totalCap += curDelivery[0].GetNumItem();
      //Checks if Truck has space for deliveries
      if (totalCap < m_truck[curTruck].GetCapacity())
	{
	  
	  //Loads current Delivery items into truck
	  int loadLimit = curItem + curDelivery[0].GetNumItem();
	  for(; curItem < loadLimit; curItem++)
	    {
	      m_truck[curTruck].AddItem(m_item[curItem]);
	      cout<< m_item[curItem].GetName() << " loaded into " << m_truck[curTruck].GetName() << endl;
	    }
	  //Places the delivery into truck
	  m_truck[curTruck].AddDelivery(m_delivery[curDeliv]);
	  curDeliv++;
	  curDelivery.erase(curDelivery.begin());
	}
      //When The Truck has been filled up deliveries
      else
	{
	  //Sets time to 10 for loading the truck
	  m_truck[curTruck].SetTime(10);
	  //Prints out delivery info
	  DeliverItem(curTruck);
	  
	  //Determines which Truck to start loading into next
	  if (curTruck < m_truck.size()-1)
	    {
	      curTruck++;
	    }
	  else
	    {
	      curTruck = 0;
	    }
	  totalCap = 0;
	  cout << "\n\n*****Loading Truck (" << m_truck[curTruck].GetName() << ")*****" << endl;
	}
    }

  //Prints out final Truck delivery if it was not filled completely
  int time = m_truck[curTruck].GetTime();
  m_truck[curTruck].SetTime(10+time);
  //cout << "\n\n**Truck Name: " << m_truck[curTruck].GetName() << "**" << endl;
  DeliverItem(curTruck);

}

//Name: DeliverItem
//Precondition: Requires that the truck has been loaded with deliveries and items
//Postcondition: Outputs the delivery information including truck name and items
void ManageDelivery::DeliverItem(int j)
{  
  //prints Delivery Info
  cout << "\n\n**Truck Name: " << m_truck[j].GetName() << "**" << endl;
  for (unsigned int i = 0; i < m_truck[j].GetDelivery().size(); i++)
    {
      cout << "***********Delivery " << i+1 << "*************" << endl;
      int time = m_truck[j].GetTime();
      m_truck[j].SetTime(time+m_truck[j].GetDeliveryAt(i).GetRTMinute());
      cout << "Delivery Time: " << m_truck[j].GetTime() << endl;
      cout << "Delivery for: " << m_truck[j].GetDeliveryAt(i).GetName() << endl;
      cout << "Delivered: " << m_truck[j].GetDeliveryAt(i).GetNumItem() << endl;
    }
  //Finds out number of delivery items sent out
  int totalDeliv = 0;
  for (unsigned int i = 0; i < m_truck[j].GetDelivery().size(); i++)
    {
      totalDeliv += m_truck[j].GetDeliveryAt(i).GetNumItem();
    }
  //loops through Queue and removes Item based on number of items in truck
  for (int i = 0; i < totalDeliv; i++)
    {
      m_truck[j].DeliverItemFromTruck();
    }

  //Clears out Truck after Deliveries are sent
  m_truck[j].CompleteDelivery();
}

//Name: DisplayItemLeft
//Precondition: Requires that all trucks have been loaded
//Postcondition: Outputs (cout) each item not loaded into a delivery
void ManageDelivery::DisplayItemLeft()
{
  //finds total items sent out to be delivered
  int totalDelItem = 0;
  for (unsigned int i = 0; i < m_delivery.size(); i++)
    {
      totalDelItem += m_delivery[i].GetNumItem();
    }
  
  //finds total Items in m_item
  int totalItem = m_item.size();
  cout << "\n\n*****Items Left After Deliveries*****" << endl;
  //If there are no remaining items
  if (totalDelItem == totalItem)
    {
      cout << "No Items Remaining" << endl;
    }
  //If there are remaining items
  else
    {
      int itemNum = 1;
      //Prints out remaining items
      for (; totalDelItem < totalItem; totalDelItem++)
	{
	  cout << "Item Num " << itemNum << " - Name: " << m_item[totalDelItem].GetName() << "- Weight: " << m_item[totalDelItem].GetWeight() << endl;
	  itemNum++;
	}
    }
  
}
