////////////////////////////////////////
//
// ExtractPulse.cpp
//
// Developed by Shunsuke SAKURAI
//
// Last Update: 27 July 2018
//
////////////////////////////////////////
//////////////////////////////
// import libraries
//////////////////////////////
#include<iostream>
#include<unistd.h> //for getopt()
#include"TFile.h"
#include"TTree.h"


//////////////////////////////
// declear functions
//////////////////////////////
const void Usage(char * argv[]);
const void GetOptions(int _rgc, char * argv[], char ** opt1, char ** opt2);

//////////////////////////////
// main
//////////////////////////////
int main(int argc, char * argv[]){
  using namespace std;
  const int kNumCell = 1024;
  char * in_filename;
  char * in_treename;
  //////////////////////////////
  // get options
  //////////////////////////////
  GetOptions(argc,argv,&in_filename,&in_treename);
  //////////////////////////////
  // open TFile
  //////////////////////////////
  TFile * in_file = new TFile(in_filename,"READ");
  //////////////////////////////
  // read TTree
  //////////////////////////////
  TTree * in_tree = new TTree();
  in_tree = dynamic_cast<TTree *>(in_file->Get(in_treename));
  //////////////////////////////
  // prepare arrays
  //////////////////////////////
  float time[kNumCell] = {};
  float wform0[kNumCell] = {};
  float wform1[kNumCell] = {};
  in_tree->SetBranchAddress("time",time);
  in_tree->SetBranchAddress("wform0",wform0);
  in_tree->SetBranchAddress("wform1",wform1);
  //////////////////////////////
  // test loop
  //////////////////////////////
  const int kNumEvent = in_tree->GetEnties();
  for(int  i_event = 0;i_event<kNumEvent;i_event++){
    in_tree->GetEntries();
    for(int i_cell = 0;i_cell<kNumCell;i_cell++){
      cout << time[i_cell] <<", " << wform1[i_cell]-wform0[i_cell] << endl;
    }
  }
  return 0;
}

//////////////////////////////
// define functions
//////////////////////////////
const void Usage(char * argv[]){
  using namespace std;
  cerr << "Usage: " << argv[0] << " <OPTION> " << "<ARGUMENT>" << endl;
  cerr << "-----Options-----" << endl;
  cerr << "-a :option a" << endl;
  cerr << "-b :option b" << endl;
  cerr << "-c :option c" << endl;
  cerr << "-i :input filename" << endl;
  cerr << "-t :input TTree name" << endl;
  exit(-1);
}

const void GetOptions(int argc, char * argv[], char ** opt1, char ** opt2){
  if (1 == argc){
    Usage(argv);
  }
  int result; 
  while((result=getopt(argc,argv,"abcdi:t:"))!=-1){
    switch(result){
    case 'a':
      Usage(argv);
      break;
    case 'b':
      Usage(argv);
      break;
    case 'c':
      Usage(argv);
      break;
    case 'd':
      Usage(argv);
      break;
    case 'i':
      opt1 = &optarg;
      break;
    case 't':
      opt2 = &optarg;
      break;
    default:
      Usage(argv);
      break;
    }
  }
}
