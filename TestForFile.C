TString file="ORIGINAL_DATA/originalfilelist.dat";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to convert given string format of Month into integer form
string getMonth(string s)
{
  if(s=="Sep")return "09";
  if(s=="Oct")return "10";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Adds 0 at the begining of integer if it is less than 10
string modified(int a)
{
  return ((a<10)?("0"+to_string(a)):to_string(a));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestForFile()
{
  ifstream input(file);
  ofstream output("testoutput.txt");
  if(input)cout<<"Successfully opned the file: "<<file<<endl;
  else cout<<"Error in opening the file: "<<file<<endl;

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
	
	TString intermediatefile="ORIGINAL_DATA/"+fileorder;
	ifstream temp(intermediatefile);
	if(temp)cout<<"Successful to open : "<<fileorder<<endl;
	else cout<<"Failure to open the file: "<<fileorder<<endl;

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

		  //Manipulting the given lines
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
	    cout<<"time:    \t "<<time1<<endl;
	    string date=modified(year)+getMonth(month)+modified(day);//getMonth helps to get in integer form
	    cout<<"date:    \t "<<date<<endl;
	    cout<<"runtime: \t "<<runtime<<endl;
	    
	    //Checking if the given file is open for storing the manipulated data
	    // 	     if(timedateinfo.is_open())cout<<timestamp<<" opened successfully to store output\v"<<endl;
	    //  else
	    // 	 {
	    // 	   cout<<"Could not open "<<timestamp<<endl;
	    // 	   return 0;
	    // 	 }
	    // //Storing the data in this file seperated by tab
	    //  timedateinfo<<fixed<<setprecision(1)<<showpoint;
	     
	    // timedateinfo<<setw(10)<<date<<setw(15)<<time1<<setw(15)<<runtime<<endl;

	
    }
  cout<<"\v";
  cout<<"_________________________________________________________________________________________________________________________________"<<endl;
	cout<<"\v";
 
}
