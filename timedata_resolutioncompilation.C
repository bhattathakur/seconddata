void timedata_resolutioncompilation()
{

  //Data file storing input file and output file
  const char * inputfile="FINAL/datetimeruntime.dat";
  const char * inputresolution="FINAL/allrandomdata.dat";
  const char * outfile="FINAL/compiledtimeresolution.dat";

  //Check if inputfile is opened successfully
  //Defining the variables to store date and time
  Int_t date,tim,nanosec=0;
  Double_t runtime,resolution,error_resolution;
  // TTimeStamp timestamp=new TTimeStamp();
  
  //Base time to subtract from
  TTimeStamp basetime(20180901,000000,0,kTRUE,-6*3600);
  //cout<<"basetime= "<<basetime.Print();
  double basetimesec=basetime.AsDouble();
  cout<<"basetimesec= "<<basetimesec<<endl;
  
  ifstream datain(inputfile);
  ifstream datainput(inputresolution);
  if(datain.is_open())
    {
	cout<<"successfully opened the file" <<inputfile<<endl;
	//Checking if the file containing resolution and errror is opened
	if(datainput.is_open())
	  {
	    cout<<"successfully opened the file "<<inputresolution<<endl;
	  }
	else
	  {
	    cout<<"Unable to open the file "<<inputresolution<<endl;
	    return 0;
	  }
	cout<<"-----------------------------------"<<endl;
	//Manipulating the data
	while(1)
	  {
	    
	    datainput>>resolution>>error_resolution;//Reading resolution and errro
	    datain>>date>>tim>>runtime; //
	   
	    if(!datainput.good())break;
	    if(!datain.good())break;
	    cout<<"original output from resolution file = "<<endl;
	    cout<<resolution<<'\t'<<error_resolution<<endl;
	    cout<<"original output from time file ="<<endl;
	    cout<<date<<'\t'<<tim<<'\t'<<runtime<<'\t'<<endl;
	   auto timestamp=new TTimeStamp(date,tim,nanosec,kTRUE,0);
	    // timestamp.Set(date,time,nanosec,kTRUE,-6*3600);//offset between CDT and UTC = 6hrs
	    //cout<<"time = ";
	    //cout<<timestamp.Print();
	    // cout<<"month = "<< timestamp.GetMonth()<<endl;
	    //  cout<<"Date  = "<< timestamp.GetDate()<<endl;
	    // cout<<"Time  = "<<timestamp.GetTime()<<endl;
	    cout<<"Second ="<<timestamp->GetSec()<<endl;
	    cout<<"NanoSecond="<<timestamp->GetNanoSec()<<endl;
	    cout<<"As Double ="<<timestamp->AsDouble()<<endl;
	    cout<<"As String ="<<timestamp->AsString()<<endl;
	    double newtime=timestamp->GetSec()+runtime/2;
	    cout<<"run time ="<<runtime<<endl;
	    cout<<"new time ="<<newtime<<endl;
	    //Storing the output in the file
	    //time resolution runtime/2 resolutionerror

	    ofstream timereso(outfile,ios::app);
	    if(timereso.is_open())
		{
		  cout<<"successfully opened the file "<<outfile<<endl;
		  cout<<setw(10)<<newtime-basetimesec<<setw(15)<<resolution<<setw(10)<<runtime/2<<setw(10)<<error_resolution<<endl; //newtime-basetime
		  timereso<<setw(10)<<newtime-basetimesec<<setw(15)<<2.35*resolution<<setw(10)<<runtime/2<<setw(10)<<2.35*error_resolution<<endl;//Multiply by 2.35
		}
	    else
		{
		  cout<<"Error opening the file "<<outfile<<endl;
		}
	     cout<<"-----------------------------------"<<endl;
	  cout<<endl;
	  }
	 
    }
  else
    {
	cout<<"failed to open the file" <<inputfile<<endl;
	return 0;
    }

}
