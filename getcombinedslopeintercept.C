TString slopedata="FINAL/allinterceptslope.dat"; //this is the file to store all the  intercepts and slopes in one file

double m,merror,b,berror; //data in the sequence b, berror, m , merror

ofstream outputslope(slopedata);


//Initialize the function

void readingfile(TString basicFormat,int jLimit);

void getcombinedslopeintercept()
{
  readingfile("slopeintercept",24);
  return;
}

//Function reads all the files with some basic format, j limit is the maximum number of files to be read
void readingfile(TString basicFormat,int jLimit)
{
  cout<<" ------------------------------------------------------------"<<endl;
    	for(int j=1;j<=jLimit;j++)
	  {
	    TString input="DATA/"+basicFormat+""+Form("%d",j)+".dat";
	    cout<<"************************** File "<<j<<" **************************"<<endl;
	    cout<<"\vinput = "<<input<<endl;
	    ifstream inputfile(input);
	    

	    //Checking if the given file is opened 
	    if(inputfile.is_open())
		{
		  cout<<"Successfully opened the file "<< input<<endl;
		  
		  while(inputfile>>b>>m>>berror>>merror)
		    {
			
			cout<<"\vb = "<<b<< " \tb error = "<<berror<<"\nm = "<<m<< "\tm error = "<<merror<<endl<<"\v";
			
			if(outputslope.is_open())
			  {
			    cout<<"Successfully opened  the file!\nStoring given data in the file: "<<slopedata<<endl;
			    cout<<"\v";
			    
			    outputslope<<b<<setw(20)<<m<<setw(20)<<berror<<setw(20)<<merror<<endl;
			    cout<<"b \t\tm \t\tberror\t\t merror"<<endl;
			    cout<<b<<setw(10)<<m<<setw(20)<<berror<<setw(20)<<merror<<endl;
			    cout<<"\v\v";
			    
			  }
			else cout<<"Unable to open the file "<<slopedata<<endl;
			cout<<" ------------------------------------------------------------"<<endl;
		    }
		}
	    else
		{
		  cout<<"failed to open the file "<<input<<endl;
		  return ;
		}
	    
	  }
}

