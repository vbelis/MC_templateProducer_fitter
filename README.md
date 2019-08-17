# Inclusive b-Purity study - _Local Files_

## Purpose
Calculation of b-production fraction (b-purity) using the inclusive muon pTrel method. The the dataset under study is the B-Parking dataset, collected by the CMS experiment at CERN's LHC. Working with Prof. Sphicas NKUA group.

#### template_producer:
The code creates the _MC template_ files which include, among other  distributions and info, the pTrel distribution of muons in b-,c- and udsg events.

#### fitter: 
The program receives the MC templates and the corresponding data file. It parametrizes accordingly the pTrel distributions and fits a linear combination of them to the inclusive data pTrel distribution. The value of the b-Purity is given as a free parameter of the fit. As a result, the b-Purity is extracted from the desired dataset by the fit.

#### generalPlotters:
A collection of programms used to plot certain comparison graphs between data and MC and between some MC pTrel distributions.

#### bFragmentationSystUnc: 
Preliminary code pool for the estimation of systematic uncertainty of the fit due to the uncertainty of the \epsilon_b parameter of the fragmentation function used in the MC (PYTHIA) generation.
