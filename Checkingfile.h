void checkFileOpening(TString filename)
{
  ifstream inputfile(filename);
  if(inputfile)
    {
    cout<<"Successfully opened the file: "<<filename<<endl;
    }
  else
    {
	cout<<"Unable to open the file: "<<filename<<endl;
	return 0;
    }
}
