const char * timestamp="FINAL/datetimeruntime.dat"; //file for storing final results:date time runtime
ofstream timedateinfo(timestamp);


//Function initialization
string getMonth(string s);//get month
string modified(int a); 
void readingfile(string basicFormat,int iLimit,int jLimit);

//main file
void timeinformationreading()
{
  string file1="bkg_0";
  string file2="bkg_01_0";
  string file3="bkg_02_0";
  string file4="bkg_03_0";
  readingfile(file1,0,2);
  readingfile(file2,1,9);
  readingfile(file3,0,9);
  readingfile(file4,0,6);
}
/*
Given files:
                                     
bkg_000.dat                          bkg_03_000.dat
bkg_001.dat          bkg_01_014.dat  bkg_03_001.dat
bkg_002.dat          bkg_01_015.dat  bkg_03_002.dat
bkg_01_000.dat       bkg_01_016.dat  bkg_03_003.dat
bkg_01_001.dat       bkg_01_017.dat  bkg_03_004.dat
bkg_01_002.dat       bkg_01_018.dat  bkg_03_005.dat
bkg_01_003.dat       bkg_01_019.dat  bkg_03_006.dat
bkg_01_004.dat       bkg_02_000.dat  
bkg_01_005.dat       bkg_02_001.dat  
bkg_01_006.dat       bkg_02_002.dat  
bkg_01_007.dat       bkg_02_003.dat  
bkg_01_008.dat       bkg_02_004.dat  
bkg_01_009.dat       bkg_02_005.dat  
bkg_01_010.dat       bkg_02_006.dat  
bkg_01_011.dat       bkg_02_007.dat
bkg_01_012.dat       bkg_02_008.dat
bkg_01_013.dat       bkg_02_009.dat
*/
//Function to convert given string format of Month into integer form
string getMonth(string s)
{
  if(s=="Sep")return "09";
  if(s=="Oct")return "10";
}

//Adds 0 at the begining of integer if it is less than 10
string modified(int a)
{
  return ((a<10)?("0"+to_string(a)):to_string(a));
}

//Reads the data file based on basicformat, ilimit, jlimit
void readingfile(string basicFormat,int iLimit,int jLimit)
{
  
  for(int i=0;i<=iLimit;i++)
    {
	for(int j=0;j<=jLimit;j++)
	  {
	    string input="ORIGINAL_DATA/"+basicFormat+""+to_string(i)+""+to_string(j)+".dat";
	    //  cout<<"input = "<<input<<endl;
	    ifstream inputfile(input);
	    string line,line1;

	    //Checking if the given file is opened 
	    if(inputfile.is_open())
		{
		  cout<<"Successfully opened the file "<< input<<endl;
		  while(getline(inputfile,line))
		    {
			if(line[0]=='R')
			  {
			    cout<<line<<endl;
			    line1+=" "+line;
			  }
		    }
		  cout<<"line 1 :"<<line1<<endl;
		}
	    else
		{
		  cout<<"failed to open the file "<<input<<endl;
		  return 0;
		}
	    
	    cout<<"line1 = "<<line1<<endl;

	    //Defining the stringstream
	    // Run started....................:  Mon Sep 17 10:56:44 2018 Run  time......................:       86408.22 s
	    stringstream ss;
	    ss<<line1; //line1 as stringstream object
	    string run,start,weekday,month,run1,time;
	    int day,hour, minute,second,year;
	    double runtime;
	    char dummy;
	    
	    // Run started....................:  Mon Sep 17 10:56:44 2018 Run  time......................:       86408.22 s
	    ss>>run>>start>>weekday>>month>>day>>hour>>dummy>>minute>>dummy>>second>>year>>run1>>time>>runtime>>dummy;

	    //editing time and date for less than 10
	    string time1=modified(hour)+modified(minute)+modified(second);
	    cout<<"time = "<<time1<<endl;
	    string date=modified(year)+getMonth(month)+modified(day);//getMonth helps to get in integer form
	    cout<<"date = "<<date<<endl;
	    cout<<"runtime = "<<runtime<<endl;
	    
	    //Checking if the given file is open for storing the manipulated data
	     if(timedateinfo.is_open())cout<<timestamp<<" opened successfully "<<endl;
	     else
		 {
		   cout<<"Could not open "<<timestamp<<endl;
		   return 0;
		 }
	    //Storing the data in this file seperated by tab
	    timedateinfo<<date<<'\t'<<time1<<'\t'<<runtime<<endl;
	    
	  }
    }
}


