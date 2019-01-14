#include "Histogram.h"
void testMyClass()
{
  cout<<"Creating the histogram using the class"<<endl;
  Histogram * test=new Histogram();
  Histogram * file=new Histogram("final.txt");
  file->checkOpeningStatus();
  file->displayLines();
    
}
