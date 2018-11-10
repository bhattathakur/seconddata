void checkFileOpening(const char *filename)
{
  ifstream inputfile(filename);
  if(inputfile.is_open())
    {
	cout<<"Successfully opened the file: "<<filename<<endl;
    }
  else
    {
	cout<<"Unable to open the file: "<<filename<<endl;
	return 0;
    }
}
