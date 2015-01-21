import FWCore.ParameterSet.Config as cms
from pdb import set_trace
import URAnalysis.PATTools.skims.ttbarToElJets as eJets
import URAnalysis.PATTools.skims.ttbarToMuJets as muJets

def add_skims(process, **collections):
   '''returns a list of added sequences'''
   return [
      muJets.skim(process, **collections),
      eJets.skim(process, **collections),
      ]
   
