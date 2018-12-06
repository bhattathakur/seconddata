void getTimeInterceptSlopeResolution()
{

  //Data file storing input file and output file
  const char * inputfile="FINAL/datetimeruntime.dat"; //information about date, time and runtime
  const char * inputresolution="FINAL/allrandomdata.dat";//all the random data
  const char * inputintercpeslope="FINAL/allinterceptslope.dat";//all the intercpets slope intercept error and slope error
  const char * outfile="FINAL/TimeInterceptSlopeResolution.dat";//information about time intercept slope and resolution

  //Check if inputfile is opened successfully
  //Defining the variables to store date and time
  Int_t date,tim,nanosec=0;
  Double_t runtime,resolution,error_resolution;
  Double_t intercept,errorintercept,slope,errorslope;
  // TTimeStamp timestamp=new TTimeStamp();
  const double SIGMA_TO_FWHM=2.355; //To Change from sigma to fwhm 
  //Base time to subtract from
  TTimeStamp basetime(20180901,000000,0,kTRUE,-6*3600);
  //cout<<"basetime= "<<basetime.Print();
  double basetimesec=basetime.AsDouble();
  cout<<"basetimesec= "<<basetimesec<<endl;
  
  ifstream datain(inputfile);
  ifstream datainput(inputresolution);
  ifstream intslope(inputintercpeslope);
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

	if(intslope.is_open())
	  {
	    cout<<"successfully opened the file "<<inputintercpeslope<<endl;
	  }
	else
	  {
	    cout<<"Unable to open the file "<<inputintercpeslope<<endl;
	    return 0;
	  }
	cout<<"-----------------------------------"<<endl;
	
	//Manipulating the data
	while(1)
	  {
	    
	    datainput>>resolution>>error_resolution;//Reading resolution and errro
	    datain>>date>>tim>>runtime; //Reading the timefile
	    intslope>>intercept>>slope>>errorintercept>>errorslope;
	   
	    if(!datainput.good())break;
	    if(!datain.good())break;
	    if(!intslope.good())break;
	    cout<<"\v";
	    cout<<"original output from resolution file: "<<endl;
	    cout<<"(resolution->resolutionerror)"<<endl;
	    cout<<resolution<<'\t'<<error_resolution<<endl;
	    cout<<"\v";
	    cout<<"original output from time file:"<<endl;
	    cout<<"(date->time->runtime)"<<endl;
	    cout<<date<<'\t'<<tim<<'\t'<<runtime<<'\t'<<endl;
	    cout<<"\v";
	    cout<<"original output from intercept file:"<<endl;
	    cout<<"(intercpet->slope->intercepterror->slopeerror)"<<endl;
	    cout<<intercept<<'\t'<<slope<<'\t'<<errorintercept<<'\t'<<errorslope<<endl;
	    cout<<"\v";
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

	    ofstream timeresointercept(outfile,ios::app);
	    if(timeresointercept.is_open())
		{
		  cout<<fixed<<setprecision(5)<<showpoint;
		  cout<<"successfully opened the file "<<outfile<<endl;
		  cout<<"newtime-basetime->FWHM->intercpet->slope->errortime->errorFWHM->errorintercept->errorslope"<<endl;
		  cout<<setw(10)<<newtime-basetimesec<<setw(15)<<resolution*SIGMA_TO_FWHM<<setw(15)<<intercept<<setw(20)<<slope
			<<setw(20)<<runtime/2<<setw(15)<<error_resolution*SIGMA_TO_FWHM<<setw(25)<<errorintercept<<setw(20)<<errorslope<<endl; //newtime-basetime
		  timeresointercept<<fixed<<setprecision(5)<<showpoint<<setw(10)<<newtime-basetimesec<<setw(15)<<resolution*SIGMA_TO_FWHM<<setw(15)<<intercept<<setw(20)<<slope
					  <<setw(20)<<runtime/2<<setw(15)<<error_resolution*SIGMA_TO_FWHM<<setw(25)<<errorintercept<<setw(20)<<errorslope<<endl; //newtime-basetime
		 
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
