class Histogram
{
 public:
  Histogram();
  Histogram(TString);
  void checkOpeningStatus();
  void displayLines();
 private:
  TString name;
  
};
Histogram::Histogram()
{
  cout<<"Creating the histogram"<<endl;
  TH1F * h1=new TH1F("h1", "histo from a gaussian", 100, -3, 3);
  h1->FillRandom("gaus", 10000);
  h1->SetFillColor(kBlue);
  h1->Draw();
}
Histogram::Histogram(TString name)
{
  cout<<"Creating the file with given name: "<<endl;
  this->name=name;
}
void Histogram::checkOpeningStatus()
{
  cout<<"Checking the opening status of given file"<<endl;
  ifstream input(this->name);
  if(input)
    {
	cout<<"successfully opened the file: "<<this->name<<endl;
    }
  else
    {
	cout<<"unable to open the file: "<<this->name<<endl;
	return 0;
    }
}
void Histogram::displayLines()
{
  cout<<"Showing the lines stores in the given text file "<<endl;
  ifstream input(this->name);
  string line;
  while(getline(input,line))
    {
	string ctype=line.c_str();
	TString ttype=line+"";
	if (isdigit(ctype[0]))cout<<ctype<<endl;
	if(ttype.IsAscii())cout<<"yes letters"<<endl;
	//if (line[0]=='R')cout<<line<<endl;
    }
}

