TString root="ORIGINAL_DATA/";
TString file=root+"originalfilelist.dat";

//Clearing the file if it exists coz we have to use ios::app option which will go on adding the values in each run

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to convert given string format of Month into integer form
TString getMonth(string s)
{
  if(s=="Sep")return "09";
  if(s=="Oct")return "10";
  if(s=="Nov")return "11";
  if(s=="Dec")return "12";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Adds 0 at the begining of integer if it is less than 10
TString modified(int a)
{
  TString aString=Form("%d",a);
  return ((a<10)?("0"+aString):aString);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FinalTimeFile()
{
  int test=remove("FINAL/datetimeruntime.dat"); //For removing the file if it already exist
  TString timestamp="FINAL/datetimeruntime.dat"; //Redifing the file to  store the output timeinformation information
  ifstream input(file);
  //  ofstream output("testoutput.txt");
  if(input)cout<<"Successfully opened the file: "<<file<<endl;
  else
    {
	cout<<"Error in opening the file: "<<file<<endl;
	return ;
    }

  //Defining the string to store the file name:
  string fileorder;
  int count=1;
  while(getline(input,fileorder))
    {
	cout<<"\v";
	cout<<"_________________________________________________________________________________________________________________________________"<<endl;
	cout<<"\v";
	cout<<"File : "<<count<<endl;
	count++;
	cout<<fileorder<<endl;
	//Displaying the line 1 of the given file:

	//TString infile=Format("%s",fileorder);
     	//cout<<"infile: "<<infile<<endl;
	cout<<"root  : "<<root<<endl;
	TString intermediatefile=root+fileorder.c_str();
     	cout<<"intermediatefile: "<<intermediatefile<<endl;
	//	TString intermediatefile="ORIGINAL_DATA"+"/"+"bkg_000.dat";
	cout<<"Input File: "<<intermediatefile<<endl;
	ifstream temp(intermediatefile);
	if(temp)cout<<"Successful to open : "<<intermediatefile<<endl;
	else
	  {
	    cout<<"Failure to open the file: "<<intermediatefile<<endl;
	    return;
	  }

	//Checking the line 1 inside the  file
	string line,line1;
	while(getline(temp,line))
	  {
	    if(line[0]=='R')
		{
		  cout<<line<<endl;
		  line1+=" "+line;
		}
	  }
	cout<<"line 1 :"<<line1<<endl;

	
	// Run started....................:  Mon Sep 17 10:56:44 2018 Run  time......................:       86408.22 s
	stringstream ss;
	ss<<line1; //line1 as stringstream object
	string run,start,weekday,month,run1,time;
	int day,hour, minute,second,year;
	double runtime;
	char dummy;
		  
	// Run started....................:  Mon Sep 17 10:56:44 2018 Run  time......................:       86408.22 s
	ss>>run>>start>>weekday>>month>>day>>hour>>dummy>>minute>>dummy>>second>>year>>run1>>time>>runtime>>dummy;
	cout<<"After stringstream"<<endl;
	//  cout<<run<<start<<weekday<<month<<day<<hour<<dummy<<minute<<dummy<<second<<year<<run1<<time<<runtime<<dummy<<endl;

	//editing time and date for less than 10
	TString time1=modified(hour)+modified(minute)+modified(second);
	cout<<"day: "<<day<<endl;
	cout<<"time:    \t "<<time1<<endl;
	TString date=modified(year)+getMonth(month)+modified(day);//getMonth helps to get in integer form
	cout<<"date:    \t "<<date<<endl;
	cout<<"runtime: \t "<<runtime<<endl;
		  
	//Checking if the given file is open for storing the manipulated data
	ofstream timedateinfo(timestamp,ios::app);
	if(timedateinfo.is_open())cout<<timestamp<<" opened successfully to store output\v"<<endl;
	else
	  {
	    cout<<"Could not open "<<timestamp<<endl;
	    return 0;
	  }
	
	//Storing the data in this file seperated by tab
	timedateinfo<<fixed<<setprecision(1)<<showpoint;
	timedateinfo<<setw(10)<<date<<setw(15)<<time1<<setw(15)<<runtime<<endl;
    
    }
  cout<<"\v";
  cout<<"_________________________________________________________________________________________________________________________________"<<endl;
  cout<<"\v";
 
}
