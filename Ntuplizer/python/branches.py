import FWCore.ParameterSet.Config as cms

kinematics = [
   cms.InputTag('px'),
   cms.InputTag('py'),
   cms.InputTag('pz'),
   cms.InputTag('pt'),
   cms.InputTag('eta'),
   cms.InputTag('phi'),
   cms.InputTag('charge','','/I'),
]

isolation = [
   #Isolation
   cms.InputTag('chargedIso', 'chargedHadronIso'),
   cms.InputTag('neutralIso', 'neutralHadronIso'),
   cms.InputTag('photonIso'),
   cms.InputTag('puIso', 'puChargedHadronIso'),
]

muon_specific = [
   cms.InputTag('ECalEnergy', 'calEnergy().em'),
   cms.InputTag('HCalEnergy', 'calEnergy().had'),
   cms.InputTag('numChambers', 'numberOfChambers', '/I'), 
   cms.InputTag('numChambersWithSegments', 'numberOfMatches(2)', '/I'), #2 = Muon::SegmentAndTrackArbitration
   cms.InputTag('numMatchedStations', 'numberOfMatchedStations()', '/I'),

   #global track attributes
   cms.InputTag('ptErr', '? globalTrack().isNonnull() ? globalTrack().ptError() : -1'),
   cms.InputTag('chi2', '? globalTrack().isNonnull() ? globalTrack().chi2()    : -1'),
   cms.InputTag('NDOF', '? globalTrack().isNonnull() ? globalTrack().ndof()    : -1', '/I'),
   cms.InputTag('validHits', '? globalTrack().isNonnull() ? globalTrack().hitPattern().numberOfValidMuonHits() : -1'),

   #id
   cms.InputTag('isGlobal'    ,'isGlobalMuon'    , '/O'),
   cms.InputTag('isTracker'   ,'isTrackerMuon'   , '/O'),
   cms.InputTag('isCalo'      ,'isCaloMuon'      , '/O'),
   cms.InputTag('isPF'        ,'isPFMuon'        , '/O'),
   cms.InputTag('isStandAlone','isStandAloneMuon', '/O'),

   cms.InputTag('isLoose',  'isLooseMuon',  '/O'),
   cms.InputTag('isTight',  'isTightMuon',  '/O'),
   cms.InputTag('isSoft',   'isSoftMuon',   '/O'),
   cms.InputTag('isHighPt', 'isHighPtMuon', '/O'),
]

btaggging = [
   cms.InputTag('jetBProb', 'bDiscriminator("jetBProbabilityBJetTags")'),
   cms.InputTag('jetProb', 'bDiscriminator("jetProbabilityBJetTags")'),
   cms.InputTag('trkHiPur', 'bDiscriminator("trackCountingHighPurBJetTags")'),
   cms.InputTag('trkHiEff', 'bDiscriminator("trackCountingHighEffBJetTags")'),
   cms.InputTag('ssvHiEff', 'bDiscriminator("simpleSecondaryVertexHighEffBJetTags")'),
   cms.InputTag('ssvHiPur', 'bDiscriminator("simpleSecondaryVertexHighPurBJetTags")'),
   cms.InputTag('csv', 'bDiscriminator("combinedSecondaryVertexBJetTags")'),
   cms.InputTag('csvIncl', 'bDiscriminator("combinedInclusiveSecondaryVertexBJetTags")'),
   cms.InputTag('vtxMass' , 'userFloat("vtxMass")'),
   cms.InputTag('vtxNtracks' , 'userFloat("vtxNtracks")'),
   cms.InputTag('vtx3DVal' , 'userFloat("vtx3DVal")'),
   cms.InputTag('vtx3DSig' , 'userFloat("vtx3DSig")'),
]

jet_specific = [
   cms.InputTag('e', 'energy'),
   cms.InputTag('area', 'jetArea'),
   cms.InputTag('mass', 'p4().mass()'),

   cms.InputTag('chargedHadronEnergy'),  
   cms.InputTag('neutralHadronEnergy'), 
   cms.InputTag('photonEnergy'), 
   cms.InputTag('electronEnergy'), 
   cms.InputTag('muonEnergy'), 
   cms.InputTag('forwardEM', 'HFHadronEnergy'), 
   cms.InputTag('forwardHad', 'HFEMEnergy'),

   cms.InputTag('numChargedHadrons', 'chargedHadronMultiplicity'),
   cms.InputTag('numNeutralHadrons', 'neutralHadronMultiplicity'),
   cms.InputTag('numPhotons', 'photonMultiplicity'),
   cms.InputTag('numElectrons', 'electronMultiplicity'),
   cms.InputTag('numMuons', 'muonMultiplicity'),
   cms.InputTag('numForwardEMs', 'HFHadronMultiplicity'),
   cms.InputTag('numForwardHads', 'HFEMMultiplicity'),

   #FIXME add jet shape information, JEC
   #jet PU id
   cms.InputTag('puId', 'userFloat("pileupJetId:fullDiscriminant")'),

   #cms.InputTag('chargedPtMomPA', 
   #cms.InputTag('chargedPtMomPB', 
   #cms.InputTag('constituentPtMomPA', 
   #cms.InputTag('constituentPtMomPB',
   #cms.InputTag('ptFractionWrongPrimaryVertex', 
   #cms.InputTag('maxChargedPtFraction', 
   #cms.InputTag('maxPtFraction',
   #cms.InputTag('energyCorrection', 
   #cms.InputTag('energyCorrectionUnc',
]
