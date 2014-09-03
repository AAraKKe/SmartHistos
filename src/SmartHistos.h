/************************************************************
 *************************************************************
Description: A class to automatize the histogram creation within
the analysis code.
Author: J.P. Araque
Last change: 18/09/2012
 *************************************************************
 *************************************************************/  
#ifndef Smart_Histos
#define Smart_Histos 

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <vector>
#include <string>
#include <iostream>
#include "Config.h"

#ifdef  HAVE_CXX0X
#include <unordered_map>
typedef std::unordered_map<std::string,TH1*> map_1d;
typedef std::unordered_map<std::string,TH2*> map_2d;
typedef std::unordered_map<std::string,std::vector<double> > map_val;
#elif HAVE_TR1
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<std::string, TH1*> map_1d;
typedef std::tr1::unordered_map<std::string, TH2*> map_2d;
typedef std::tr1::unordered_map<std::string,std::vector<double> > map_val;
#else
#include <map>
typedef std::map<std::string,TH1*> map_1d;
typedef std::map<std::string,TH1*> map_2d;
typedef std::map<std::string,std::vector<double> > map_val;
#endif

class SmartHistos {
    public:
        SmartHistos();
        ~SmartHistos();

        // Variables
        map_1d m_histos; //!< Map of histograms of TH1
        map_2d m_histos2D; //!< Map of histograms fot TH2

        // Functions
        void Fill(double value, double weight, std::string name, std::string title);
        void Fill(double value, double weight, int nbins, double xmin, double xmax, std::string name, std::string title="");
        void Fill2D(double valuex, double valuey, double weight, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax, std::string name, std::string title="");
        void SetBinContent(int bin, double value, int nbins, double xmin, double xmax, std::string name, std::string title="");
        void SetBinError(int bin, double error, int nbins, double xmin, double xmax, std::string name, std::string title="");
        TH1F* GetHisto(std::string); // TODO: Write it
        void Write(TFile*);

    private:

        map_val m_values; //!< Stores values befores writing to Hs
        map_val m_weights; //!< Stores weights befores writing to Hs
};
#endif
