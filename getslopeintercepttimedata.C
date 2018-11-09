const char * slopedata="FINAL/allslope.dat";
const char * intercpetdata="FINAL/allintercept.dat";
void getslopeintercpettimedata()
{
  
}
double m,merror,b,berror;

ofstream outputslope(slopedata);
ofstream outputintercep(intercpetdata);

//Initialize the function

void readingfile(string basicFormat,int jLimit);

void allrandomdatareading()
{
  readingfile("randomdata",5);
}

void readingfile(string basicFormat,int jLimit)
{
  cout<<" ------------------------------------------------------------"<<endl;
    	for(int j=0;j<=jLimit;j++)
	  {
	    string input="DATA/"+basicFormat+""+to_string(j)+".dat";
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
			cout<<"resoultion = "<<resolution<< " & resolution error = "<<resolution_error<<endl;
			if(outputrandomdata.is_open())
			  {
			    cout<<"Successfully opened  the file "<<resultofrandomdata<<endl;
			    outputrandomdata<<resolution<<setw(10)<<resolution_error<<endl;
			    
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

