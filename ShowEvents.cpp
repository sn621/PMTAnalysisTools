////////////////////////////////////////
//
// ShowEvents.cpp
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
#include"TApplication.h"
#include"TFile.h"
#include"TTree.h"
#include"TGraph.h"
#include"TAxis.h"
#include"TCanvas.h"

//////////////////////////////
// declear functions
//////////////////////////////
const void Usage(char * argv[]);
const void GetOptions(int argc, char * argv[], char ** opt1, char ** opt2, char ** opt3,char ** opt4,char ** opt5, char ** opt6);

//////////////////////////////
// main
//////////////////////////////
int main(int argc, char * argv[]){
  using namespace std;
  TApplication app("app",&argc,argv);
  const int kNumCell = 1024;
  char * in_filename;
  char * in_treename;
  char * out_filename;
  char * eve_num;
  //char * begin_cell;
  //char * cell_length;
  //////////////////////////////
  // get options
  //////////////////////////////
  GetOptions(app.Argc(),app.Argv(),&in_filename,&in_treename,&out_filename,&eve_num,&begin_cell,&cell_length);
  //////////////////////////////
  // open TFile
  //////////////////////////////
  TFile * in_file;
  cout << in_filename << endl;
  in_file = new TFile(in_filename,"READ");
  //////////////////////////////
  // read TTree
  //////////////////////////////
  TTree * in_tree;
  cout << in_treename << endl;
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
  TGraph * graph = new TGraph();
  TCanvas * canv = new TCanvas("c1","c1",600,600);
  int dummy;
  graph->Draw("a");

  //////////////////////////////
  // test loop
  //////////////////////////////
  const int kNumEve = atoi(eve_num);
  const int kNumEvent = in_tree->GetEntries();
  for(int  i_event = 0;i_event<kNumEvent;i_event++){
    in_tree->GetEntry(i_event);
    int count=0;
    for(int i_cell =0;i_cell<1024;i_cell++){
      //int num_p = graph->GetN();
      graph->RemovePoint(i_cell);
      graph->SetPoint(i_cell,time[i_cell],wform1[i_cell]-wform0[i_cell]);
      cout << time[i_cell] << endl;
      count++;
    }
    //    graph->GetXaxis()->SetLimits(atoi(begin_cell),atoi(begin_cell)+atoi(cell_length));
    graph->SetMaximum(100);
    graph->SetMinimum(-50);
    //graph->Draw("a*");
    canv->Update();
    canv->Modified();
    graph->Clear();
    getchar();
    //sleep(1);
  }


  //TFile * out_file;
  //out_file = new TFile(out_filename,"RECREATE");
  //graph->Write();
  //out_file->Close();
  app.Run();
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
  cerr << "-c :option c" << endl;
  cerr << "-i :input filename" << endl;
  cerr << "-t :input TTree name" << endl;
  cerr << "-o :output filename" << endl;
  cerr << "-e :event number" << endl;
  cerr << "-b :begin cell" << endl;
  cerr << "-l :cell length" << endl;
  exit(-1);
}

const void GetOptions(int argc, char * argv[], char ** opt1, char ** opt2, char ** opt3, char ** opt4, char ** opt5, char ** opt6){
  if (1 == argc){
    Usage(argv);
  }
  int result; 
  while((result=getopt(argc,argv,"acdi:t:o:e:b:l:"))!=-1){
    switch(result){
    case 'a':
      Usage(argv);
      break;
    case 'c':
      Usage(argv);
      break;
    case 'd':
      Usage(argv);
      break;
    case 'i':
      std::cout << optarg << std::endl;
      *opt1 = optarg;
      break;
    case 't':
      std::cout << optarg << std::endl;
      *opt2 = optarg;
      break;
    case 'o':
      std::cout << optarg << std::endl;
      *opt3 = optarg;
      break;
    case 'e':
      std::cout << optarg << std::endl;
      *opt4 = optarg;
      break;
    case 'b':
      std::cout << optarg << std::endl;
      *opt5 = optarg;
      break;
    case 'l':
      std::cout << optarg << std::endl;
      *opt6 = optarg;
      break;
    default:
      Usage(argv);
      break;
    }
  }
}
