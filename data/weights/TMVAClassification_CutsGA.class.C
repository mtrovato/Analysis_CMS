// Class: ReadCutsGA
// Automatically generated by MethodBase::MakeClass
//

/* configuration options =====================================================

#GEN -*-*-*-*-*-*-*-*-*-*-*- general info -*-*-*-*-*-*-*-*-*-*-*-

Method         : Cuts::CutsGA
TMVA Release   : 4.1.3         [262403]
ROOT Release   : 5.34/01       [336385]
Creator        : naodell
Date           : Thu Apr 18 16:43:45 2013
Host           : Linux naodell-P55-USB3 3.2.0-29-generic #46-Ubuntu SMP Fri Jul 27 17:03:23 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
Dir            : /home/naodell/work/FCNCAnalysis
Training events: 306043
Analysis type  : [Classification]


#OPT -*-*-*-*-*-*-*-*-*-*-*-*- options -*-*-*-*-*-*-*-*-*-*-*-*-

# Set by User:
V: "False" [Verbose output (short form of "VerbosityLevel" below - overrides the latter one)]
H: "True" [Print method-specific help message]
FitMethod: "GA" [Minimisation Method (GA, SA, and MC are the primary methods to be used; the others have been introduced for testing purposes and are depreciated)]
EffMethod: "EffSel" [Selection Method]
# Default:
VerbosityLevel: "Default" [Verbosity level]
VarTransform: "None" [List of variable transformations performed before training, e.g., "D_Background,P_Signal,G,N_AllClasses" for: "Decorrelation, PCA-transformation, Gaussianisation, Normalisation, each for the given class of events ('AllClasses' denotes all events of all classes, if no class indication is given, 'All' is assumed)"]
CreateMVAPdfs: "False" [Create PDFs for classifier outputs (signal and background)]
IgnoreNegWeightsInTraining: "False" [Events with negative weights are ignored in the training (but are included for testing and performance evaluation)]
CutRangeMin[0]: "-1.000000e+01" [Minimum of allowed cut range (set per variable)]
    CutRangeMin[1]: "-1.000000e+00"
    CutRangeMin[2]: "-1.000000e+00"
    CutRangeMin[3]: "-1.000000e+00"
    CutRangeMin[4]: "-1.000000e+00"
    CutRangeMin[5]: "-1.000000e+00"
    CutRangeMin[6]: "-1.000000e+00"
CutRangeMax[0]: "1.000000e+01" [Maximum of allowed cut range (set per variable)]
    CutRangeMax[1]: "-1.000000e+00"
    CutRangeMax[2]: "-1.000000e+00"
    CutRangeMax[3]: "-1.000000e+00"
    CutRangeMax[4]: "-1.000000e+00"
    CutRangeMax[5]: "-1.000000e+00"
    CutRangeMax[6]: "-1.000000e+00"
VarProp[0]: "NotEnforced" [Categorisation of cuts]
    VarProp[1]: "FMax"
    VarProp[2]: "NotEnforced"
    VarProp[3]: "NotEnforced"
    VarProp[4]: "NotEnforced"
    VarProp[5]: "NotEnforced"
    VarProp[6]: "NotEnforced"
##


#VAR -*-*-*-*-*-*-*-*-*-*-*-* variables *-*-*-*-*-*-*-*-*-*-*-*-

NVar 7
met                           met                           met                           met                           GeV                               'F'    [0.104863040149,680.905883789]
HT                            HT                            HT                            HT                            GeV                               'F'    [0,1384.77929688]
TrileptonMass                 TrileptonMass                 TrileptonMass                 TrileptonMass                 GeV                               'F'    [14.6907138824,2160.96118164]
DileptonMassOS                DileptonMassOS                DileptonMassOS                DileptonMassOS                GeV                               'F'    [0,1915.16992188]
DileptonDROS                  DileptonDROS                  DileptonDROS                  DileptonDROS                  rad                               'F'    [0,5.44339895248]
JetMult                       JetMult                       JetMult                       JetMult                                                         'I'    [0,6]
BJetMult                      BJetMult                      BJetMult                      BJetMult                                                        'I'    [0,10]
NSpec 0


============================================================================ */

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#ifndef IClassifierReader__def
#define IClassifierReader__def

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual double GetMvaValue( const std::vector<double>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#endif

class ReadCutsGA : public IClassifierReader {

 public:

   // constructor
   ReadCutsGA( std::vector<std::string>& theInputVars ) 
      : IClassifierReader(),
        fClassName( "ReadCutsGA" ),
        fNvars( 7 ),
        fIsNormalised( false )
   {      
      // the training input variables
      const char* inputVars[] = { "met", "HT", "TrileptonMass", "DileptonMassOS", "DileptonDROS", "JetMult", "BJetMult" };

      // sanity checks
      if (theInputVars.size() <= 0) {
         std::cout << "Problem in class \"" << fClassName << "\": empty input vector" << std::endl;
         fStatusIsClean = false;
      }

      if (theInputVars.size() != fNvars) {
         std::cout << "Problem in class \"" << fClassName << "\": mismatch in number of input values: "
                   << theInputVars.size() << " != " << fNvars << std::endl;
         fStatusIsClean = false;
      }

      // validate input variables
      for (size_t ivar = 0; ivar < theInputVars.size(); ivar++) {
         if (theInputVars[ivar] != inputVars[ivar]) {
            std::cout << "Problem in class \"" << fClassName << "\": mismatch in input variable names" << std::endl
                      << " for variable [" << ivar << "]: " << theInputVars[ivar].c_str() << " != " << inputVars[ivar] << std::endl;
            fStatusIsClean = false;
         }
      }

      // initialize min and max vectors (for normalisation)
      fVmin[0] = 0.104863040149212;
      fVmax[0] = 680.905883789062;
      fVmin[1] = 0;
      fVmax[1] = 1384.779296875;
      fVmin[2] = 14.6907138824463;
      fVmax[2] = 2160.96118164062;
      fVmin[3] = 0;
      fVmax[3] = 1915.169921875;
      fVmin[4] = 0;
      fVmax[4] = 5.44339895248413;
      fVmin[5] = 0;
      fVmax[5] = 6;
      fVmin[6] = 0;
      fVmax[6] = 10;

      // initialize input variable types
      fType[0] = 'F';
      fType[1] = 'F';
      fType[2] = 'F';
      fType[3] = 'F';
      fType[4] = 'F';
      fType[5] = 'I';
      fType[6] = 'I';

      // initialize constants
      Initialize();

   }

   // destructor
   virtual ~ReadCutsGA() {
      Clear(); // method-specific
   }

   // the classifier response
   // "inputValues" is a vector of input values in the same order as the 
   // variables given to the constructor
   double GetMvaValue( const std::vector<double>& inputValues ) const;

 private:

   // method-specific destructor
   void Clear();

   // common member variables
   const char* fClassName;

   const size_t fNvars;
   size_t GetNvar()           const { return fNvars; }
   char   GetType( int ivar ) const { return fType[ivar]; }

   // normalisation of input variables
   const bool fIsNormalised;
   bool IsNormalised() const { return fIsNormalised; }
   double fVmin[7];
   double fVmax[7];
   double NormVariable( double x, double xmin, double xmax ) const {
      // normalise to output range: [-1, 1]
      return 2*(x - xmin)/(xmax - xmin) - 1.0;
   }

   // type of input variable: 'F' or 'I'
   char   fType[7];

   // initialize internal variables
   void Initialize();
   double GetMvaValue__( const std::vector<double>& inputValues ) const;

   // private members (method specific)
   // not implemented for class: "ReadCutsGA"
};
   inline double ReadCutsGA::GetMvaValue( const std::vector<double>& inputValues ) const
   {
      // classifier response value
      double retval = 0;

      // classifier response, sanity check first
      if (!IsStatusClean()) {
         std::cout << "Problem in class \"" << fClassName << "\": cannot return classifier response"
                   << " because status is dirty" << std::endl;
         retval = 0;
      }
      else {
         if (IsNormalised()) {
            // normalise variables
            std::vector<double> iV;
            int ivar = 0;
            for (std::vector<double>::const_iterator varIt = inputValues.begin();
                 varIt != inputValues.end(); varIt++, ivar++) {
               iV.push_back(NormVariable( *varIt, fVmin[ivar], fVmax[ivar] ));
            }
            retval = GetMvaValue__( iV );
         }
         else {
            retval = GetMvaValue__( inputValues );
         }
      }

      return retval;
   }
