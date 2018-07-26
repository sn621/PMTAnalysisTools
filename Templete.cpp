////////////////////////////////////////
//
// Templete.cpp
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

//////////////////////////////
// declear functions
//////////////////////////////
const void Usage(char * argv[]);
const void GetOptions(int _rgc, char * argv[], char ** e);

//////////////////////////////
// main
//////////////////////////////
int main(int argc, char * argv[]){
  char * e;
  //////////////////////////////
  // get options
  //////////////////////////////
  GetOptions(argc,argv,&e);
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
  cerr << "-d :option d" << endl;
  cerr << "-e :option e" << endl;
  exit(-1);
}

const void GetOptions(int argc, char * argv[], char ** e){
  if (1 == argc){
    Usage(argv);
  }
  int result; 
  while((result=getopt(argc,argv,"abcde:"))!=-1){
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
    case 'e':
      e = &optarg;
      break;
    default:
      Usage(argv);
      break;
    }
  }
}
