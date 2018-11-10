const char * slopedata="FINAL/allinterceptslope.dat";

double m,merror,b,berror; //data in the sequence b, berror, m , merror

ofstream outputslope(slopedata);


//Initialize the function

void readingfile(string basicFormat,int jLimit);

void getcombinedslopeintercept()
{
  readingfile("Ecaltrue",1);
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
		  while(inputfile>>b>>m>>berror>>merror)
		    {
			//			inputfile>>b>>berror>>m>>merror;
			//	inputfile>>b>>m>>berror>>merror;

			//	if(!inputfile.good())break;
			cout<<"b = "<<b<< " b error = "<<berror<<" m = "<<m<< " m error = "<<merror<<endl;
			
			if(outputslope.is_open())
			  {
			    cout<<"Successfully opened  the file "<<slopedata<<endl;
			    
			    outputslope<<setw(20)<<b<<setw(20)<<m<<setw(20)<<berror<<setw(20)<<merror<<endl;
			    cout<<"b m berror merror"<<endl;
			    cout<<setw(20)<<b<<setw(20)<<m<<setw(20)<<berror<<setw(20)<<merror<<endl;
			    
			  }
			else cout<<"Unable to open the file "<<slopedata<<endl;
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

