/*
This script reads all the random data i.e. resolution generated from toy mc and mean of that resolution.
We need to supply the highest filenumber of random data.It reads from 1 to that file number and stores the output in the single file
 */
const char * resultofrandomdata="FINAL/allrandomdata.dat"; //file which stores all the random data

double resolution,resolution_error;

ofstream outputrandomdata(resultofrandomdata);

//Initialize the function

void readingfile(string basicFormat,int jLimit);

void allrandomdatareading()
{
  readingfile("randomdata",81); //number of datafiles
}

//reads all the files starting with basic formit upto jLimit//
void readingfile(string basicFormat,int jLimit) 
{
  cout<<" ------------------------------------------------------------"<<endl;
    	for(int j=1;j<=jLimit;j++)
	  {
	    string input="FINAL/"+basicFormat+""+to_string(j)+".dat";
	    cout<<"input = "<<input<<endl;
	    ifstream inputfile(input);
	    

	    //Checking if the given file is opened 
	    if(inputfile.is_open())
		{
		  cout<<"Successfully opened the file "<< input<<endl;
		  while(1)
		    {
			inputfile>>resolution>>resolution_error;
			if(!inputfile.good())break;
			cout<<"\v";
			cout<<fixed<<setprecision(5)<<showpoint;
			cout<<"resoultion:\t\t"<<resolution<< "\nresolution error:\t"<<resolution_error<<endl;
			cout<<"\v";
			if(outputrandomdata.is_open())
			  {
			    cout<<"Successfully opened  the file "<<resultofrandomdata<<endl;
			    outputrandomdata<<fixed<<setprecision(5)<<showpoint;
			    outputrandomdata<<setw(8)<<resolution<<setw(10)<<resolution_error<<endl;
			    
			  }
			else cout<<"Unable to open the file "<<resultofrandomdata<<endl;
			cout<<" ------------------------------------------------------------"<<endl;
		    }
		}
	    else
		{
		  cout<<"failed to open the file "<<input<<endl;
		  return 0;
		}
	    
	  }
}

