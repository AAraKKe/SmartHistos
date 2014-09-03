#include "SmartHistos.h"
#include <iostream>
#include <algorithm>

using namespace std;


/**
 * @brief SmartHistos constructor.
 */
SmartHistos::SmartHistos(){
}

/**
 * @brief SmartHistos destructor
 */
SmartHistos::~SmartHistos(){

    unordered_map<string,TH1*>::iterator it = m_histos.begin();
    for(; it != m_histos.end(); it++){
        delete (*it).second;
    }

}

/**
  @brief Beta function of the SmartHistos package.

  This functions fills the vector of values with value and weight.
  If the histogram does not exist it creates a new one with the desired properties. This functions fill the histogram without needing nether the limits of the histogram or the number of bins. They will be automatically calculated before writing the histogram into a rootfile. 

  By default the number of bins is 50 if the width of the histogram is treater than 50 and the width or the histogram if it is smaller.
  e.g. xmin = 0, xmax = 20 => nbins = 20.

  @param value This is the value that will be filled into the histogram
  @param weight This is the weight that this value will have when filled into the histogram
  @param name The name of the histogram
  @param title The title of the histogram. In the case that a title is not specified or the function is called with only three arguments the title will be the same as the name.
  */
void SmartHistos::Fill(double value, double weight, string name, string title) {

    // Check if the histogram exists. If it does add the value to it, if it 
    // doesn't create a new one with that name.
    unordered_map<string, vector<double> >::iterator it = m_values.find(name);
    if (it != m_values.end()) {
        m_values[name].push_back(value);
        m_weights[name].push_back(weight);
    } else {
        vector<double> v, w;
        v.push_back(value);
        w.push_back(weight);
        m_values.insert(pair<string,vector<double> >(name, v));
        m_weights.insert(pair<string,vector<double> >(name, w));

        // Create the new histogram.
        string htitle = (title.size() > 0) ? title : name;

        m_histos.insert(pair<string,TH1*>(name, new TH1F(name.c_str(), title.c_str(), 50, -999, 999)));
        m_histos[name]->Sumw2();
    }

}

/**
 *  @brief This fucntions make the fill of the histogram. It will be Filled if it exists and it will be created and fill otherwhise. 
 *
  @param value This is the value that will be filled into the histogram
  @param weight This is the weight that this value will have when filled into the histogram
  @parm bins Number of bins of the histogram
  @param xlow Low limit of the histogram
  @param xup Upper limit of the histogram
  @param name The name of the histogram
  @param title The title of the histogram. In the case that a title is not specified or the function is called with only three arguments the title will be the same as the name.
  */
void SmartHistos::Fill(double value, double weight, int bins, double xlow, double xup, string name, string title){

    // Find the histogram and create it if doesn't exist
    unordered_map<string,TH1*>::iterator it = m_histos.find(name);
    if (it != m_histos.end()){
        m_histos[name]->Fill(value, weight);
    } else {
        string htitle = (title.size() > 0) ? title : name;
        m_histos.insert(pair<string,TH1*>(name, new TH1F(name.c_str(), htitle.c_str(), bins, xlow, xup)));
        m_histos[name]->Sumw2();
        m_histos[name]->Fill(value, weight);
    }

}

/**
 * @brief This function calls the function SetBinContent of the correspondent ROOT histogram. If it doesn't exist it decalres a new one.
 *
 * @param bin The bin whose value will be set
 * @param value The value at that will be set in the bin
 * @param bins The number of bins of the histogram for the declaration in the first time
 * @param xlow Low limit of the histogram
 * @param xup Upper limit of the histogram
 * @param name The name of the histogram for its first declaration
 * @param title Title of the histogram. If the name is not supplied 
 */
void SmartHistos::SetBinContent(int bin, double value, int bins, double xlow, double xup, string name, string title){

    // Find the histogram and create it if doesn't exist
    unordered_map<string,TH1*>::iterator it = m_histos.find(name);
    if (it != m_histos.end()){
        m_histos[name]->SetBinContent(bin, value);
    } else {
        string htitle = (title.size() > 0) ? title : name;
        m_histos.insert(pair<string,TH1*>(name, new TH1F(name.c_str(), htitle.c_str(), bins, xlow, xup)));
        m_histos[name]->Sumw2();
        m_histos[name]->SetBinContent(bin, value);
    }


}

/**
 * @brief This function calls the function SetBinError of the correspondent ROOT histogram. If it doesn't exist it decalres a new one.
 *
 * @param bin The bin whose value will be set
 * @param value The error at that will be set in the bin
 * @param bins The number of bins of the histogram for the declaration in the first time
 * @param xlow Low limit of the histogram
 * @param xup Upper limit of the histogram
 * @param name The name of the histogram for its first declaration
 * @param title Title of the histogram. If the name is not supplied 
 */
void SmartHistos::SetBinError(int bin, double error, int bins, double xlow, double xup, string name, string title){

    // Find the histogram and create it if doesn't exist
    unordered_map<string,TH1*>::iterator it = m_histos.find(name);
    if (it != m_histos.end()){
        m_histos[name]->SetBinError(bin, error);
    } else {
        string htitle = (title.size() > 0) ? title : name;
        m_histos.insert(pair<string,TH1*>(name, new TH1F(name.c_str(), htitle.c_str(), bins, xlow, xup)));
        m_histos[name]->Sumw2();
        m_histos[name]->SetBinError(bin, error);
    }


}

/**
 *  @brief This function makes the fill of a 2D hisgotram. It will be Filled if it exists and it will be created and filled otherwhise. 
 *
  @param valuex This is the value that will be filled into the x-axis of the histogram
  @param valuey This is the value that will be filled into the y-axis of the histogram
  @param weight This is the weight that this value will have when filled into the histogram
  @parm binsx Number of bins in the x-axis
  @param xlow Low limit of the x-axis
  @param xup Upper limit of the x-axis
  @parm binsy Number of bins of the y-axis
  @param ylow Low limit of the y-axis
  @param yup Upper limit of the y-axis
  @param name The name of the histogram
  @param title The title of the histogram. In the case that a title is not specified or the function is called with only three arguments the title will be the same as the name.
  */
void SmartHistos::Fill2D(double valuex, double valuey, double weight, int binsx, double xlow, double xup, int binsy, double ylow, double yup, string name, string title){

    // Find the histogram and create it if doesn't exist
    unordered_map<string,TH2*>::iterator it = m_histos2D.find(name);
    if (it != m_histos2D.end()){
        m_histos2D[name]->Fill(valuex, valuey, weight);
    } else {
        string htitle = (title.size() > 0) ? title : name;
        m_histos2D.insert(pair<string,TH2*>(name, new TH2F(name.c_str(), htitle.c_str(), binsx, xlow, xup, binsy, ylow, yup)));
        m_histos2D[name]->Sumw2();
        m_histos2D[name]->Fill(valuex, valuey, weight);
    }

}

/**
 * @brief The write function calls the write function of the ROOT histograms and write them into the output TFile.
 *
 * @param tf Is a pointer to the TFile where the histograms will be written.
 */
void SmartHistos::Write(TFile *tf){

    tf->cd();

    // Create a string with names to sort in alphabetical order.
    // This will make the printout easier.
    vector<string> names2d, names1d;
    for (unordered_map<string,TH2*>::iterator it = m_histos2D.begin(); it != m_histos2D.end(); it++){
        names2d.push_back((*it).first);
    }
    for (unordered_map<string,TH1*>::iterator it = m_histos.begin(); it != m_histos.end(); it++) {
        names1d.push_back((*it).first);
    }

    sort(names1d.begin(), names1d.end());
    sort(names2d.begin(), names2d.end());

    // Not yet supported
    /*for (map<string,TH1*>::iterator it = m_histos.begin(); it != m_histos.end(); it++) {

        // Chck if the limits need to be calculated
        if ((*it).second->GetBinLowEdge(1) == -999){
            string name = (*it).first;
            // TODO: This does not work well with weights
            sort(m_values[name].begin(), m_values[name].end());

            // Set xmin, xmax and nbin 
            double back =  m_values[name].back();
            double front = m_values[name].front();
            int bins = (back - front > 70) ? 70 : int(back-front+1);
            double sc = (back -front+1)/bins;
            (*it).second->SetBins(bins, int(front), int(back + sc));

            // Fill the histogram
            for (unsigned int i = 0; i < m_values[name].size(); i++) {
                (*it).second->Fill(m_values[name][i],1); // The weight is 1 because it has already been multiplied
            }
        }

        // Write all histograms
        (*it).second->Write();
    }*/

    for (unsigned int i = 0; i < names1d.size(); i++){
        m_histos[names1d[i]]->Write();
    }
    for (unsigned int i = 0; i < names2d.size(); i++){
        m_histos[names2d[i]]->Write();
    }
}
