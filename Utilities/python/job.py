import os

class Job(object):
   '''
   generalization of a CMSSW job to be submitted 
   with CRAB/batch
   '''
   def __init__(self, pycfg, jobid, simple_name, dbs_name,
                pycfg_args, njobs, lumimask=''):
      self.pycfg = pycfg
      self.name = simple_name 
      self.dbs_name    = dbs_name   
      self.njobs       = njobs      
      self.id       = jobid      
      self.args  = pycfg_args  
      self.mask = lumimask

   def save_as_crab(self):
      from WMCore.Configuration import Configuration
      
      isData = self.name.startswith('data')
      config = Configuration()
      config.section_("General")
      config.General.requestName = '%s_%s' % (self.id, self.name)
      config.section_("JobType")
      config.JobType.psetName = self.pycfg
      config.JobType.pluginName = 'Analysis'
      config.JobType.pyCfgParams = self.args
      config.section_("Data")
      config.Data.inputDataset = self.dbs_name
      config.Data.splitting = 'LumiBased' if isData else 'FileBased'
      config.Data.totalUnits = self.njobs
      if self.mask:
         config.Data.lumimask = self.mask
      config.Data.outLFN = os.path.join(
         '/store/user/', 
         os.environ['USER'],
         self.id,
         self.name
         )
      config.section_("Site")
      config.Site.storageSite = os.environ['URA_STORAGE_SITE']

      crab_cfg_name = 'crab_%s_%s_cfg.py' % (self.id, self.name)
      with open(crab_cfg_name, 'w') as cfg:
         cfg.write(config.pythonise_())

      return crab_cfg_name

