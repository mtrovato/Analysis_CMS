/*
   Utilities for retrieving weights for PU,etc.
 */

#ifndef _WeightUtils_H
#define _WeightUtils_H

// c++ libraries
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

// ROOT libraries
#include "TROOT.h"
#include "TObject.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TGraphErrors.h"

// boost libraries
//#include <boost/array.hpp>

// custom libraries
#include "../interface/TCPhysObject.h"
#include "../interface/TCJet.h"
#include "../interface/TCGenJet.h"

using namespace std;

class WeightUtils: public TObject {
    public:
        WeightUtils() {};
        virtual ~WeightUtils() {};
        WeightUtils(string sampleName, string dataPeriod, string selection, bool isRealData);

        void    Initialize();
        void    SetDataBit(bool);
        void    SetDataPeriod(string);
        void    SetSampleName(string);
        void    SetSelection(string);
        void    SetPassTrigger(string); 
        void    SetObjects(vector<TCPhysObject>, vector<TCJet>, float, string);

        float   PUWeight();
        float   RecoWeight();
        float   ZZWeight(vector<TLorentzVector>);
        float   VBFHiggsWeight(float, int);
        float   GetTotalWeight();
        float   FakeWeight(TCPhysObject);

        // lepton reco efficiencies
        float GetElectronEff(TLorentzVector) const;
        float GetMuEff(TLorentzVector) const; 

        // lepton trigger efficiencies
        float GetMuTriggerEff(TLorentzVector) const;
        float GetElTriggerEff(TLorentzVector) const {return 0;}

        ClassDef(WeightUtils, 0);

    private:
        //input parameters
        string _dataPeriod;
        string _sampleName;
        string _selection;
        bool   _isRealData;

        // input objects
        vector<TCPhysObject>    _leptons;
        vector<TCJet>           _jets;
        string                  _passTrig;
        float                   _nPU;

        //sources
        TGraphErrors *_muSF2012[4];
        map<string, TH1D*>  puReweight;

        TH2D    *h2_EleMVASF;
        TH2D    *h2_EleFakes;
        TH2D    *h2_MuFakes;


        //weights
        float _puWeight;
        float _zzWeight;
        float _vbfWeight;
        float _recoWeight;
        float _triggerWeight;
};

#endif

#if !defined(__CINT__)
ClassImp(WeightUtils);
#endif
