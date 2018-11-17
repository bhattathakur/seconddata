const int NUMBER_OF_FILES=40;
string fileDirectory="ORIGINAL_DATA/"; //basic format for the input files 
string inputfilelist="ORIGINAL_DATA/originalfilelist.dat"; //This file has the list of all files
string  File[]={};
//string fileArray(string files[],int size);
string * arrayForFiles(const char *,int );
void checkfileOpening(string fileIn);

void readFile()
{
  string * filelist=arrayForFiles(inputfilelist.c_str(),NUMBER_OF_FILES);
  for(int i=0;i<NUMBER_OF_FILES;i++)
    {
	printf("filelist %2d :%s \n",i+1,filelist[i].c_str());
    }
  for(int i=0;i<NUMBER_OF_FILES;i++){
  string inputFile=fileDirectory+filelist[i];
  cout<<"inputFile: "<<inputFile<<endl;
  checkfileOpening(inputFile);
  }
  exit (0);
}
 //Reads the files and stores the files in the form of string array
string * arrayForFiles(const char * fileName,int fileNum)
{
  ifstream inputfile(fileName);
  string nameOfFile;
  string * intermed =new string[fileNum];
  int count=0;
    if(inputfile.is_open())
    {
	cout<<"Successfully opened the file "<<fileName<<endl;

	while(inputfile>>nameOfFile)
	  {
	    // getline(inputfile,intermed[count]);
	    intermed[count]=nameOfFile;
	    count++;
	  }
    }
  else
    {
	cout<<"Unable to open the file "<<fileName<<endl;
    }
    return intermed;
  }
void checkfileOpening(string fileIn)
{
  // fileIn=fileDirectory+fileIn;
  cout<<"Trying to open the file :"<<fileIn<<endl;
  ifstream input;
  input.open(fileIn.c_str());
  if(input.is_open())
    {
	cout<<"Successfully opened the file :"<<fileIn<<endl;
    }
  else
    {
	cout<<"Unable to open the file :"<<fileIn<<endl;
    }
}
