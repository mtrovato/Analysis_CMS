#! /usr/bin/env python
import subprocess, shlex, datetime
from multiprocessing import Process

import ROOT as r
from PlotProducer import *
from TableMaker import *

### Wrapper function for multi-threading ###

def plotter_wrapper(plotter, category, inputPath, outputPath, do1D, do2D):

    plotter.set_input_file(inputPath)
    plotter.set_save_path(outputPath)
    plotter._category = category

    if do1D:
        plotter.make_overlays_1D(logScale = True, doRatio = False, doEff = False)
    if do2D:
        plotter.make_overlays_2D(logScale = True, doProjection = False)

now         = datetime.datetime.now()
currentDate = '{0:02d}/{1:02d}/{2:02d}'.format(now.year, now.month, now.day)

### Get command line arguements

if len(sys.argv) > 1:
    batch = '_' + sys.argv[1]
else:
    batch = ''

### This is the config file for manipulating 
### histograms using the PlotProducer class.  

selection   = 'fcnh'
suffix      = sys.argv[1]
#suffix      = 'TEST'

cutList     = ['1_preselection']
#cutList.extend(['2_Z_veto', '3_MET', '4_bjet_cut', '5_BDT'])

period      = '2012'
LUMIDATA    = 5.3

doPlots     = True
doYields    = False

doOS        = False
doSS        = False
do3l        = False
do1D        = True
do2D        = False

### Categories to be plotted ###
catSS       = ['ss_inclusive', 'ss_mumu', 'ss_ee', 'ss_emu'] 
catOS       = ['os_inclusive', 'os_mumu', 'os_ee', 'os_emu'] 
cat3l       = ['3l_inclusive', '3l_OSSF', '3l_SSSF', 'inclusive']
cat3l.extend(['3l_eee', '3l_eemu', '3l_emumu', '3l_mumumu'])

### Samples to be included in stacks ###
samples     = []
samples.append('top')
samples.append('VJets')
#samples.append('ggHToZZ4L_M-125')
#samples.append('WWW')
#samples.append('WWZ')
#samples.append('WZZ')
#samples.append('ZZZ')
#samples.append('WWG')
#samples.append('ttW')
#samples.append('ttZ')
#samples.append('ttG')
#samples.append('WWJets2L2Nu')
#samples.append('WZJets3LNu')
#samples.append('ZZ4mu')
#samples.extend(['ttbar', 'QCD_20_MU', 'ZJets'])

p_plot = []

if doPlots:

    print '\nMaking the plots...\n'

    r.gROOT.SetBatch()

    plotter = PlotProducer(inputFile = 'fcncAnalysis/combined_histos/' + selection + '_cut1_' + period + batch + '.root', savePath = '', scale = LUMIDATA, isAFS = False)
    plotter.set_period(period)

    ### DATASETS ###
    ### Specify the datasets you wish to stack 
    ### and overlay accordingly. 

    plotter.add_datasets(samples)
    plotter._overlayList.extend(['DATA'])
    #plotter._overlayList.extend(['FCNC_M125_t'])

    #plotter.get_scale_factors(['FCNC_M125_t'])
    plotter.get_scale_factors()

    ### VARIABLES ###
    ### First specify the directories in which your
    ### histograms are stored.  If directories are 
    ### not used enter '' as the only entry.  Then 
    ### list all of the variable names you wish to 
    ### plot while giving a key value which is the 
    ### directory that they are located in as a key.

    plotter._directoryList1D            = ['Misc', 'Lepton', 'Dilepton', 'DileptonOS', 'MET', 'Jet', 'top']
    plotter._directoryList2D            = ['2D']

    plotter._variableDict['Misc']       = ['PvMult', 'YieldByCut', 'EventWeight', 'TriggerStatus']

    plotter._variableDict['Lepton']     = ['LeptonCharge', 'LeptonFlavor', 
                                           'Lepton1Pt', 'Lepton2Pt','Lepton3Pt',
                                           'Lepton1Eta', 'Lepton2Eta', 'Lepton3Eta',
                                           'Lepton1 dxy', 'Lepton1 dz',
                                           'Lepton2 dxy', 'Lepton2 dz',
                                           'Lepton3 dxy', 'Lepton3 dz',
                                           'TrileptonMass', 'LeptonMult', '4lMass']
                                           #'Lepton1Phi', 'Lepton2Phi', 'Lepton3Phi']

    plotter._variableDict['Dilepton']   = ['DileptonMass21', 'DileptonTransMass21', 'DileptonQt21',
                                           'DileptonDeltaPhi21', 'DileptonDeltaEta21', 'DileptonDeltaR21', 'DileptonDeltaPt21',
                                           'DileptonMass31', 'DileptonTransMass31', 'DileptonQt31', 
                                           'DileptonDeltaPhi31', 'DileptonDeltaEta31', 'DileptonDeltaR31', 'DileptonDeltaPt31',
                                           'DileptonMass32', 'DileptonTransMass32', 'DileptonQt32', 
                                           'DileptonDeltaPhi32', 'DileptonDeltaEta32', 'DileptonDeltaR32', 'DileptonDeltaPt32']

    plotter._variableDict['DileptonOS'] = ['DileptonOSMass', 'DileptonOSTransMass', 'DileptonOSBalance',
                                           'DileptonOSQt', 'DileptonOSDeltaPt', 'DileptonOSDeltaR', 
                                           'DileptonOSDeltaEta', 'DileptonOSDeltaPhi',
                                           'DileptonLepDeltaR', 'DileptonLepDeltaPhi', 'DileptonLepDeltaEta'] 

    plotter._variableDict['top']        = ['Top1Mass', 'Top1TransMass', 'Top1Pt', 'DeltaPhiTop1Met',
                                           'Top2TransMass', 'Top2Pt', 'DeltaPhiTop2Met', 'DeltaPhiTop1Top2Met',
                                           'DeltaPhiWZ', 'DileptonMassWZ']

    plotter._variableDict['Lep+Jet']    = ['Lepton1BJetDeltaPhi', 'Lepton1BJetDeltaEta', 'Lepton1BJetDeltaR', 'Lepton1BJetDeltaPt',
                                           'Lepton2BJetDeltaPhi', 'Lepton2BJetDeltaEta', 'Lepton2BJetDeltaR', 'Lepton2BJetDeltaPt',
                                           'Lepton3BJetDeltaPhi', 'Lepton3BJetDeltaEta', 'Lepton3BJetDeltaR', 'Lepton3BJetDeltaPt'
                                           ]


    plotter._variableDict['Jet']        = ['Jet1Pt', 'Jet2Pt',# 'Jet3Pt',
                                           'Jet1Eta', 'Jet2Eta',# 'Jet3Eta',
                                           #'Jet1Phi', 'Jet2Phi', 'Jet3Phi',
                                           'BJet1Discr', 'BJet1Pt', 'BJet1Eta', #'BJet1Phi', 
                                           'BJet2Discr', 'BJet2Pt', 'BJet2Eta', #'BJet2Phi',
                                           'JetAvgBDiscriminator', 'BJetAvgBDiscriminator',
                                           'HT', 'HTs', 'EventBalance', 'Centrality',
                                           'JetMultCharge', 'JetMult', 'BJetMult']

    plotter._variableDict['MET']        = ['Met', 'MetPhi', 'MetSumEt',
                                           'MetLepton1DeltaPhi', 'MetLepton2DeltaPhi'
                                           'MetLepDeltaPhiMin', 'nearLepIndex', 'ProjectedMet', 'MetLepton3DeltaPhi'] 

    plotter._variableDict['GEN']        = ['GenChargeMisId', 'GenMisIdPt', 'GenMisIdEta',
                                           'GenDeltaR', 'GenBalance']

    plotter._variableDict['2D']         = ['metVsHt', 'metVsSqrtHt', 'TrileptonMVsDileptonMOS',
                                            'DileptonMVsDeltaROS', 'DileptonQtVsDeltaROS',
                                            'DileptonM13VsM21', 'DileptonM12VsM31', 'DileptonM21VsM32',
                                            'DalitzM13VsM21', 'DalitzM12VsM31', 'DalitzM21VsM32',
                                            'BJetVsJetSumBDiscriminator', 'LepChargeVsFlavor']


     ###################   
     ### MAKE PLOTS! ###  
     ###################   

    r.gROOT.SetStyle('Plain')
    r.gStyle.SetOptStat(0)
    #r.gROOT.ProcessLine('.L ./tdrStyle.C')
    #r.setTDRStyle()

    categories = ['inclusive']

    if doOS:
        for category in catOS:
            categories.append(category)
    if doSS:
        for category in catSS:
            categories.append(category)
    if do3l:
        for category in cat3l:
            categories.append(category)

    for i, cut in enumerate(cutList):

        inFile  = 'fcncAnalysis/combined_histos/' + selection + '_cut' + str(i+1) + '_' + period + batch + '.root'
        outFile = 'plots/' + currentDate + '/' + selection + '_' + suffix + '/' + cut

        plotter.make_save_path(outFile, clean=True)

        for category in categories:
            if category in catOS and i is not 0:
                continue

            print '{0}: Testing new sample combiner on {1}'.format(i,category)
            plotter_wrapper(plotter, category, inFile, outFile, True, False)
            #p_plot.append(Process(name = cut[2:] + '/' + category, target = plotter_wrapper, args=(plotter, category, inFile, outFile, do1D, do2D)))

exit()

for process in p_plot:
    print 'Plotting {0}'.format(process.name)
    process.start()

for process in p_plot:
    process.join()

print '\n'

     ####################
     ### MAKE TABLES! ###
     ####################

if doYields:
    doPresel        = True
    outFile         = file('yields/yields_tmp.tex', 'w')
    samples         = samples 
    categoryNames   = []
    yieldTable      = TableMaker('fcncAnalysis/combined_histos/' + selection + '_cut1_' + period + batch + '.root', outFile, scale = LUMIDATA, delimiter = '&', doSumBG = True)

    yieldTable.set_period(period)

    yieldTable._columnList  = ['ttbar', 'ttZ', 'WWJets2L2Nu', 'ZJets', 'BG', 'DATA', 'FCNC_M125_t']#, 'Significance'] 

    yieldTable.add_datasets(samples, Clear = True)
    yieldTable.add_datasets('FCNC_M125_t')
    yieldTable.add_datasets('DATA_MUON')

    print '\n\n Printing yields...\n'

    if doOS:
        categoryNames.extend(catOS)
    if doSS:
        categoryNames.extend(catSS)
    if do3l:
        categoryNames.extend(cat3l)

    if not doPlots: 
        yieldTable.get_scale_factors()

    for category in categoryNames:
        if category == 'inclusive':
            continue

        #yieldTable._rowList = ['Initial', '.', '.', '.', '.']
        yieldTable._rowList = ['.', '.', '.', '.', '.']

        if category[:2] == '3l' and do3l:
            yieldTable._rowList.extend(['3 lepton', 'Z removal', 'MET  \& HT ', 'b-jet']) #, '1 jet'])
            #yieldTable._rowList.extend(['.', '.', '.', '.', '.', '.', 'BDT > -0.3']) 

        elif category[:2] == 'ss' and doSS:
            yieldTable._rowList.extend(['ss lepton preselection', 'Z removal', 'MET > 30 \& HT > 75', '1 b-jet']) #, '1 jet'])

        elif category[:2] == 'os' and doOS:
            yieldTable._rowList.extend(['2 os leptons', 'MET cut', '1 b-jet/1 jet', 'Z removal'])

        yieldTable._category = category
        histDict = yieldTable.get_hist_dict('YieldByCut')

        if category[:2] == 'os':
            continue
            #yieldTable.print_table(histDict, doErrors = False, doEff = False, startBin = 1)
        else:
            yieldTable.print_table(histDict, doErrors = False, doEff = False, startBin = 1)

    outFile.close()
    subprocess.call('pdflatex -output-dir=yields yields/yields.tex', shell = True)
    os.system('cp yields/yields.pdf plots/' + currentDate + '/' + selection + '_' + suffix + '/.')