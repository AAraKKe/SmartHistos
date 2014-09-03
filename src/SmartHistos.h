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
#include <tr1/unordered_map>
#include <vector>
#include <string>
#include <iostream>

class SmartHistos {
public:
	SmartHistos();
	~SmartHistos();

// Variables
	std::tr1::unordered_map<std::string,TH1*> m_histos; //!< Map of histograms of TH1
	std::tr1::unordered_map<std::string,TH2*> m_histos2D; //!< Map of histograms fot TH2

// Functions
	void Fill(double value, double weight, std::string name, std::string title);
	void Fill(double value, double weight, int nbins, double xmin, double xmax, std::string name, std::string title="");
	void Fill2D(double valuex, double valuey, double weight, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax, std::string name, std::string title="");
    void SetBinContent(int bin, double value, int nbins, double xmin, double xmax, std::string name, std::string title="");
    void SetBinError(int bin, double error, int nbins, double xmin, double xmax, std::string name, std::string title="");
	TH1F* GetHisto(std::string); // TODO: Write it
	void Write(TFile*);

private:
	
	std::tr1::unordered_map<std::string, std::vector<double> > m_values; //!< Stores values befores writing to Hs
	std::tr1::unordered_map<std::string, std::vector<double> > m_weights; //!< Stores weights befores writing to Hs
};
#endif
