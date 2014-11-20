import FWCore.ParameterSet.Config as cms
import placeholder.PATTools.meta  as meta
from pdb import set_trace

def customize(process, isMC=True, **kwargs):
    #store meta
    process.meta = cms.Sequence()    
    process.meta += meta.embed_meta(process, isMC)

    #load skimmed objects
    process.load('placeholder.PATTools.skims.objects')
    #defines objectsSkim sequence
    
    #skimming sequences
    process.load('placeholder.PATTools.skims.ttbarSemiLep') 
    skim_sequences = [('ttbar', process.ttbarSemiLepSkim)]

    #pattuplization embedding
    process.makeTuples = cms.Sequence()
    #here goes all the customization needed for embedding

    #make paths
    process.schedule = cms.Schedule()
    for name, sequence in skim_sequences:
        path_name = name+'Path'
        setattr(
            process, 
            path_name, 
            cms.Path(
                process.meta *
                process.objectsSkim *
                sequence * #topology skim sequence
                process.makeTuples
                )
            )
        process.schedule.append(
            getattr(process, path_name)
            )
        
