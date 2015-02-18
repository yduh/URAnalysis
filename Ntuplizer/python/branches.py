import FWCore.ParameterSet.Config as cms
from URAnalysis.PATTools.objects.trigger import trigger_paths
paths_mu = [i for i in trigger_paths if 'Mu' in i]
paths_el = [i for i in trigger_paths if 'Ele' in i]
#FIXME: probably not the best possible name
#FIXME: move to PSet
## def add_derived_info(branches, obj, name_prefix=''):
##    '''modifyes a branch list to include a prefix, e.g. trk,
##    and a ward, a condition to check that link is not broken,
##    e.g. innerTrack().isValid(), default null value set at -999
##    '''
##    ret = []
##    fcn_template = '? ({OBJ}.isNonnull()) ? {OBJ}.{FCN} : -999'
##    for branch in branches:
##       ret.append(
##          cms.InputTag(
##             ''.join([name_prefix, branch.moduleLabel]),
##             fcn_template.format(
##                OBJ=obj,
##                FCN=branch.productInstanceLabel
##                ),
##             branch.processName
##             )
##          )
##    return ret

def make_branch_pset(branch_name, expr='', stored_type=''):
   return cms.PSet( 
      name = cms.string(branch_name), 
      expr = cms.string(expr),
      type = cms.string(stored_type)
      )

kinematics = [
   make_branch_pset('pt'),
   make_branch_pset('eta'),
   make_branch_pset('phi'),
   make_branch_pset('charge','','/I'),
]

vertex_info = [
   make_branch_pset('dB'),
   make_branch_pset('ipDXY', 'userFloat("ipDXY")'),
   make_branch_pset('dz', 'userFloat("dz")'),
]

trigger = [
   make_branch_pset(
      i,#.replace('_',''), 
      'matching_path("HLT_%s_v*").accept' % i,
      '/O'
      )
   for i in trigger_paths
]

isolation = [
   #Isolation
   make_branch_pset('chargedIso', 'chargedHadronIso'),
   make_branch_pset('neutralIso', 'neutralHadronIso'),
   make_branch_pset('photonIso'),
   make_branch_pset('puIso', 'puChargedHadronIso'),
]

genjet_specific = [
   make_branch_pset('invisibleEnergy', 'invisibleEnergy()')
]

muon_specific = [
   make_branch_pset('ECalEnergy', 'calEnergy().em'),
   make_branch_pset('HCalEnergy', 'calEnergy().had'),
   make_branch_pset('numChambers', 'numberOfChambers', '/I'), 
   #make_branch_pset('numChambersWithSegments', 'numberOfMatches(2)', '/I'), #2 = Muon::SegmentAndTrackArbitration
   make_branch_pset('numMatchedStations', 'numberOfMatchedStations()', '/I'),

   #global track attributes
   make_branch_pset('ptErr', '? globalTrack().isNonnull() ? globalTrack().ptError() : -1'),
   make_branch_pset('chi2', '? globalTrack().isNonnull() ? globalTrack().chi2() : -1'),
   make_branch_pset('ndof', '? globalTrack().isNonnull() ? globalTrack().ndof() : -1', '/I'),
   make_branch_pset('validHits', '? globalTrack().isNonnull() ? globalTrack().hitPattern().numberOfValidMuonHits() : -1'),

   #innertrack
   make_branch_pset('pixelHits', '? innerTrack().isNonnull() ? innerTrack().hitPattern().numberOfValidPixelHits() : -1'),
   make_branch_pset('trackerLayers', '? innerTrack().isNonnull() ? innerTrack().hitPattern().trackerLayersWithMeasurement() : -1'),

   #id
   make_branch_pset('isGlobal'    ,'isGlobalMuon'    , '/O'),
   make_branch_pset('isTracker'   ,'isTrackerMuon'   , '/O'),
   make_branch_pset('isCalo'      ,'isCaloMuon'      , '/O'),
   make_branch_pset('isPF'        ,'isPFMuon'        , '/O'),
   make_branch_pset('isStandAlone','isStandAloneMuon', '/O'),

   make_branch_pset('isLoose',  'isLooseMuon',  '/O'),
   #make_branch_pset('isTight',  'isTightMuon',  '/O'),
   #make_branch_pset('isSoft',   'isSoftMuon',   '/O'),
   #make_branch_pset('isHighPt', 'isHighPtMuon', '/O'),
]
muon_specific.extend(
   make_branch_pset(
      i,#.replace('_',''),
      'userInt("%s")' % i, '/O') for i in paths_mu
)
#muon_specific.append(
#   make_branch_pset(
#      'testMatchMuonsIsoMu20eta2p1', 
#      'triggerObjectMatches().size()',
#      '/O'
#      )
#   )


btaggging = [
   make_branch_pset('jetBProb', 'bDiscriminator("jetBProbabilityBJetTags")'),
   make_branch_pset('jetProb', 'bDiscriminator("jetProbabilityBJetTags")'),
   make_branch_pset('trkHiPur', 'bDiscriminator("trackCountingHighPurBJetTags")'),
   make_branch_pset('trkHiEff', 'bDiscriminator("trackCountingHighEffBJetTags")'),
   make_branch_pset('ssvHiEff', 'bDiscriminator("simpleSecondaryVertexHighEffBJetTags")'),
   make_branch_pset('ssvHiPur', 'bDiscriminator("simpleSecondaryVertexHighPurBJetTags")'),
   #make_branch_pset('csv', 'bDiscriminator("combinedSecondaryVertexBJetTags")'),
   make_branch_pset('csv', 'bDiscriminator("combinedSecondaryVertexV2BJetTags")'),
   #make_branch_pset('csvIncl', 'bDiscriminator("combinedInclusiveSecondaryVertexBJetTags")'),
   make_branch_pset('csvIncl', 'bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags")'),
   make_branch_pset('vtxMass' , 'userFloat("vtxMass")'),
   make_branch_pset('vtxNtracks' , 'userFloat("vtxNtracks")'),
   make_branch_pset('vtx3DVal' , 'userFloat("vtx3DVal")'),
   make_branch_pset('vtx3DSig' , 'userFloat("vtx3DSig")'),
]

jet_specific = [
   make_branch_pset('e', 'energy'),
   make_branch_pset('area', 'jetArea'),
   make_branch_pset('mass', 'p4().mass()'),

   make_branch_pset('chargedHadronEnergy'),  
   make_branch_pset('neutralHadronEnergy'), 
   make_branch_pset('photonEnergy'), 
   make_branch_pset('electronEnergy'), 
   make_branch_pset('muonEnergy'), 
   make_branch_pset('forwardEM', 'HFHadronEnergy'), 
   make_branch_pset('forwardHad', 'HFEMEnergy'),

   make_branch_pset('numChargedHadrons', 'chargedHadronMultiplicity'),
   make_branch_pset('numNeutralHadrons', 'neutralHadronMultiplicity'),
   make_branch_pset('numPhotons', 'photonMultiplicity'),
   make_branch_pset('numElectrons', 'electronMultiplicity'),
   make_branch_pset('numMuons', 'muonMultiplicity'),
   make_branch_pset('numForwardEMs', 'HFHadronMultiplicity'),
   make_branch_pset('numForwardHads', 'HFEMMultiplicity'),

   #FIXME add jet shape information, JEC
   #jet PU id
   make_branch_pset('puId', 'userFloat("pileupJetId:fullDiscriminant")'),

   #make_branch_pset('chargedPtMomPA', 
   #make_branch_pset('chargedPtMomPB', 
   #make_branch_pset('constituentPtMomPA', 
   #make_branch_pset('constituentPtMomPB',
   #make_branch_pset('ptFractionWrongPrimaryVertex', 
   #make_branch_pset('maxChargedPtFraction', 
   #make_branch_pset('maxPtFraction',
   #make_branch_pset('energyCorrection', 
   #make_branch_pset('energyCorrectionUnc',
]

ecal_cluster_specific = [
   make_branch_pset('e1x5'),
   #make_branch_pset('e2x5'),
   make_branch_pset('e5x5'),
   make_branch_pset('sigmaIEtaIEta', 'sigmaIetaIeta()'),
   make_branch_pset('sigmaIPhiIPhi', 'sigmaIphiIphi()'),
   #E3x3, SigmaIEtaIPhi
   
   make_branch_pset('hcalDepth1OverEcalBc', 'hcalDepth1OverEcalBc()'),
   make_branch_pset('hcalDepth2OverEcalBc', 'hcalDepth2OverEcalBc()'),
]

electron_specific = [
   make_branch_pset('r9'),
   make_branch_pset('ESCOverETrack', 'eSuperClusterOverP()'),
   make_branch_pset('DEtaSCTrk', 'deltaEtaSuperClusterTrackAtVtx()'),
   make_branch_pset('DPhiSCTrk', 'deltaPhiSuperClusterTrackAtVtx()'),
   make_branch_pset('ecalEnergy', 'correctedEcalEnergy()'),
   make_branch_pset('passConversionVeto', 'passConversionVeto()', '/O'),

   #topology info
   make_branch_pset('isEB', '', '/O'),
   make_branch_pset('isEE', '', '/O'),
   make_branch_pset('isEBGap', '', '/O'),
   make_branch_pset('isEBEtaGap', '', '/O'),
   make_branch_pset('isEBPhiGap', '', '/O'),
   make_branch_pset('isEEGap', '', '/O'),
   make_branch_pset('isEERingGap', '', '/O'),
   make_branch_pset('isEEDeeGap', '', '/O'),
   make_branch_pset('isEBEEGap', '', '/O'),
   make_branch_pset('isElectron', '', '/O'),
   make_branch_pset('ecalSeed', 'ecalDrivenSeed', '/O'),
   make_branch_pset('trackSeed', 'trackerDrivenSeed', '/O'),
]
electron_specific.extend(
   make_branch_pset(
      i,#.replace('_',''),
      'userInt("%s")' % i, '/O') for i in paths_el
)

super_cluster_specific = [
   make_branch_pset('x', 'superCluster().x'),
   make_branch_pset('y', 'superCluster().y'),
   make_branch_pset('z', 'superCluster().z'),
   make_branch_pset('energy'   , 'superCluster().energy'   ),
   make_branch_pset('rawEnergy', 'superCluster().rawEnergy'),
   make_branch_pset('phiWidth' , 'superCluster().phiWidth' ),
   make_branch_pset('etaWidth' , 'superCluster().etaWidth' ),
]

photon_specific = [
   make_branch_pset('e3x3'),
   make_branch_pset('maxCrystalEnergy', 'maxEnergyXtal'),
   make_branch_pset('isEB', '', '/O'),
   make_branch_pset('isEE', '', '/O'),
   make_branch_pset('isPFlowPhoton', '', '/O'),
   make_branch_pset('hasConversionTracks', '', '/O'),
   make_branch_pset('hasPixelSeed', '', '/O'),
]

track_specific = [
   make_branch_pset('chi2'),
   make_branch_pset('ndof'),
   make_branch_pset('dxy'),
   make_branch_pset('dxyError'),
   make_branch_pset('dz'),
   make_branch_pset('dzError'),
   make_branch_pset('nStripHits', 'hitPattern().numberOfValidStripHits()', '/I'),
   make_branch_pset('nPixelHits', 'hitPattern().numberOfValidPixelHits()', '/I'),
   make_branch_pset('nMissingHits', 'hitPattern().numberOfLostHits()', '/I'),
   make_branch_pset('nMissingInnerHits', 'trackerExpectedHitsInner().numberOfHits()', '/I'),
   make_branch_pset('nPixelLayers', 'hitPattern().pixelLayersWithMeasurement()', '/I'),
   make_branch_pset('nStripLayers', 'hitPattern().stripLayersWithMeasurement()', '/I'),
]

vertex_specific = [
   make_branch_pset('x'),
   make_branch_pset('y'),
   make_branch_pset('z'),
   make_branch_pset('chi2'),
   make_branch_pset('ndof'),
   make_branch_pset('nTracks'),
   #SumPtQ
]

geninfo_scpecific = [
   make_branch_pset('weight'),
   make_branch_pset('pdfid1', 'pdf().id.first'),
   make_branch_pset('pdfid2', 'pdf().id.second'),
   #make_branch_pset('x1', 'pdf()->x.first'),
   #make_branch_pset('x2', 'pdf()->x.second'),
   make_branch_pset('renScale', 'qScale()'),
   #make_branch_pset('FacScale', 'qScale());
]

puinfo_specific = [
   make_branch_pset('bx', 'getBunchCrossing'),
   make_branch_pset('nPU', 'getPU_NumInteractions'),
   make_branch_pset('nInteractions', 'getTrueNumInteractions'),   
]

gen_particle_specific = [
   make_branch_pset('e', 'energy'),
   make_branch_pset('vx'),
   make_branch_pset('vy'),
   make_branch_pset('vz'),
   make_branch_pset('pdgId', '', '/I'),
   make_branch_pset('status', '', '/I'),
]

met_specific = [
   make_branch_pset('px'),
   make_branch_pset('py'),
   make_branch_pset('et'),
   make_branch_pset('phi'),   
]

