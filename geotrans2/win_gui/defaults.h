#ifndef DEFAULTS_H
#define DEFAULTS_H


#include "stdio.h"


class CMasterView;
class CMainFrame;


class Defaults
{

public:

    Defaults( char* _data_dir_path_name );
    ~Defaults();

    void saveAsDefault( CMasterView* upper_view, CMasterView* lower_view, CMainFrame* mainFrame );

    void restoreDefault( CMasterView* upper_view, CMasterView* lower_view, CMainFrame* mainFrame );


private:

  char* data_dir_path_name;
  FILE* default_file;

  void writeParameters( CMasterView* masterView, int projectionType );

  void writeOptions( CMainFrame* mainFrame );

  void readParameters( CMasterView* masterView, int projectionType );

  void readOptions( CMainFrame* mainFrame );

  void getNodeValue( char node_value[25] );
};



#endif 
