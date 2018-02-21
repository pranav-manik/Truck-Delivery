#include "ReadyDelivery.h"

using namespace std;

//Name: ReadyDelivery() and ReadyDelivery(string, string)
//Precondition: Requires 3 files: a truck file, a deliveries file and an item file
//Postcondition: Populates three vectors

ReadyDelivery::ReadyDelivery()
{
  LoadTruck();
  LoadDelivery();
  LoadItem();
}

ReadyDelivery::ReadyDelivery(string truckFile, string deliveryFile, string itemFile)
{
  m_truckFile = truckFile;
  m_deliveryFile = deliveryFile;
  m_itemFile = itemFile;
  
  //Populates vectors
  LoadTruck();
  LoadDelivery();
  LoadItem();

}

//Name: LoadTruck
//Precondition: Requires a truck file
//Postcondition: Builds a vector of delivery trucks
//Trucks: Holds items
void ReadyDelivery::LoadTruck()
{
  //Gets number of lines
  int numOfLines = 0;
  ifstream truckLines;
  truckLines.open(m_truckFile.c_str());
  while (!truckLines.eof())
    {
      string lineA;
      int lineB;
      truckLines >> lineA >> lineB;
      numOfLines++;
    }
  numOfLines--;
  truckLines.close();

  //Reads in lines and loads m_truck Vector
  ifstream myTruckFile;
  myTruckFile.open(m_truckFile.c_str());
  for (int i = 0; i < numOfLines; i++)
    {
      string name;
      int capacity;
      myTruckFile >> name >> capacity;
      Truck<Item,MAX_CAPACITY> Tr = Truck<Item,MAX_CAPACITY>(name, capacity);
      m_truck.push_back(Tr);
    }
  myTruckFile.close();
  cout << "Trucks Loaded: " << numOfLines << endl;
}

//Name: LoadDelivery
//Precondition: Requires a delivery file
//Postcondition: Builds a vector of deliveries
void ReadyDelivery::LoadDelivery()
{
  //Converts string to char
  char *fileName[m_deliveryFile.length()];
  for (unsigned int i = 0; i < m_deliveryFile.length()-1; i++)
    {
      fileName[i] = &m_deliveryFile[i];
    }
  int numOfLines = 0;
    
  ifstream deliveryLines;
  deliveryLines.open(*fileName);
    
  //gets number of lines
  while (!deliveryLines.eof())
    {
      string lineA;
      int lineB;
      int lineC;
      deliveryLines >> lineA >> lineB >> lineC;
      numOfLines++;
    }
  numOfLines--;
  deliveryLines.close();
    
  //loads delivery info into vector
  ifstream myDeliveryFile;
  myDeliveryFile.open(*fileName);
  for (int i = 0; i < numOfLines; i++)
    {
      string name;
      int numItem;
      int rtMinute;
      myDeliveryFile >> name >> numItem >> rtMinute;
      Delivery DE = Delivery(name, numItem, rtMinute);
      m_delivery.push_back(DE);
        
    }
  myDeliveryFile.close();
  cout << "Deliveries Loaded: " << numOfLines << endl;
}

//Name: LoadItem
//Precondition: Requires an item file
//Postcondition: Builds a vector of items
void ReadyDelivery::LoadItem()
{
  char *fileName[m_itemFile.length()];
  //Converts string to char
  for (unsigned int i = 0; i < m_itemFile.length()-1; i++)
    {
      fileName[i] = &m_itemFile[i];
    }
  ifstream itemLines;
  itemLines.open(*fileName);
  //gets number of lines
  int numOfLines = 0;
  while (!itemLines.eof())
    {
      string lineA;
      float lineB;
      itemLines >> lineA >> lineB;
      numOfLines++;
    }
  numOfLines--;
  itemLines.close();
    
  //loads items into vector
  ifstream myItemFile;
  myItemFile.open(*fileName);
  for (int i = 0; i < numOfLines; i++)
    {
      string name;
      float weight;
      myItemFile >> name >> weight;
      Item IT = Item(name, weight);
      m_item.push_back(IT);
    }
  myItemFile.close();
  cout << "Items Loaded: " << numOfLines << endl;
}

//Name: GetTruck
//Precondition: Requires that a truck has been built
//Postcondition: Returns a vector of all trucks
vector< Truck<Item, MAX_CAPACITY> >& ReadyDelivery::GetTruck()
{
  return m_truck;
}

//Name: GetDelivery
//Precondition: Requires that a delivery has been built
//Postcondition: Returns a vector of all deliveries
vector<Delivery> ReadyDelivery::GetDelivery()
{
  return m_delivery;
}

//Name: GetItem
//Precondition: Requires that an item vectors has been built
//Postcondition: Returns a vector of all items
vector< Item > ReadyDelivery::GetItem()
{
  return m_item;
}
