/*
This script is trying to split the given set of data into two parts by given row number
For given input results will be stored as input1 and input2
This is basically for the purpose of using multigraph
 */
void DividingData()
  {
     TString basicinputfile="check";
    TString inputfile=basicinputfile+".dat";
    Int_t rownumber=25;
    
    //Checking the opening of the given input file
    ifstream input(inputfile);
    if(input)cout<<"successfully opened the file: "<<inputfile<<endl;
    
    //Defining two files based on the given input files
    TString file1=basicinputfile+"1.dat";
    TString  file2 =basicinputfile+"2.dat";

    //Checking the opening of output files
    ofstream output1(file1),output2(file2);
    if(output1)cout<<"Successfully opened the file :"<<file1<<endl;
    if(output2)cout<<"Successfully opened the file :"<<file2<<endl;
  
    //reading the text file and storing the spilted data into two files
    string line;
    int rowCount=0;
    while(getline(input,line))
    {
	cout<<line<<endl;
	if(rowCount<25)output1<<line<<endl;
	else output2<<line<<endl;
	rowCount++;
    }
   
}
