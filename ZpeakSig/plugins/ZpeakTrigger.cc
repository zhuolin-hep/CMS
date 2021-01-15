// -*- C++ -*-
//
// Package:    CMSDASExercises/MuonExercise2
// Class:      MuonExercise2
// 
/**\class MuonExercise3 MuonExercise2.cc CMSDASExercises/MuonExercise3/plugins/MuonExercise2.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Norbert Neumeister
//         Created:  Thu, 10 Dec 2016 21:10:01 GMT
//
//

// system include files
#include <memory>
#include <iomanip>
#include <cstring>

#include <TLorentzVector.h>
#include <TVector3.h>
#include <TProfile.h>
#include <TTree.h>
#include "TString.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
//
// class declaration
//

class ZpeakTrigger : public edm::one::EDAnalyzer<edm::one::SharedResources> {

   public:

      explicit ZpeakTrigger(const edm::ParameterSet&);
      ~ZpeakTrigger();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:

      virtual void beginJob() override;
      bool HLTaccept(const edm::Event&, std::string&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      //edm::EDGetTokenT<pat::PackedGenParticleCollection> genCollToken;
      edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
      //edm::EDGetTokenT<reco::Vertex> vertexToken_;
      edm::EDGetTokenT<edm::TriggerResults> triggerToken_;
  
      TH1F* h_RecDiMuon_Tight_M;
      TH1F* h_RecDiMuon_Loose_M;
      TH1F* h_RecDiMuon_Trigger_M;
      TH1F* h_RecDiMuon_MuonMatch_M;

      TH1F* h_RecDiMuon_Tight_pt;
      TH1F* h_RecDiMuon_Loose_pt;
      TH1F* h_RecDiMuon_Trigger_pt;
      TH1F* h_RecDiMuon_MuonMatch_pt;

      TH1F* h_RecDiMuon_Tight_eta;
      TH1F* h_RecDiMuon_Loose_eta;
      TH1F* h_RecDiMuon_Trigger_eta;
      TH1F* h_RecDiMuon_MuonMatch_eta;

      TH1F* h_RecDiMuon_Tight_phi;
      TH1F* h_RecDiMuon_Loose_phi;
      TH1F* h_RecDiMuon_Trigger_phi;
      TH1F* h_RecDiMuon_MuonMatch_phi;

      TH1F* h_RecMuonPlus_Tight_pt;
      TH1F* h_RecMuonPlus_Loose_pt;
      TH1F* h_RecMuonPlus_Trigger_pt;
      TH1F* h_RecMuonPlus_MuonMatch_pt;

      TH1F* h_RecMuonMinus_Tight_pt;
      TH1F* h_RecMuonMinus_Loose_pt;
      TH1F* h_RecMuonMinus_Trigger_pt;
      TH1F* h_RecMuonMinus_MuonMatch_pt;

      TH1F* h_RecMuonPlus_Tight_eta;
      TH1F* h_RecMuonPlus_Loose_eta;
      TH1F* h_RecMuonPlus_Trigger_eta;
      TH1F* h_RecMuonPlus_MuonMatch_eta;

      TH1F* h_RecMuonMinus_Tight_eta;
      TH1F* h_RecMuonMinus_Loose_eta;
      TH1F* h_RecMuonMinus_Trigger_eta;
      TH1F* h_RecMuonMinus_MuonMatch_eta;

      TH1F* h_RecMuonPlus_Tight_phi;
      TH1F* h_RecMuonPlus_Loose_phi;
      TH1F* h_RecMuonPlus_Trigger_phi;
      TH1F* h_RecMuonPlus_MuonMatch_phi;

      TH1F* h_RecMuonMinus_Tight_phi;
      TH1F* h_RecMuonMinus_Loose_phi;
      TH1F* h_RecMuonMinus_Trigger_phi;
      TH1F* h_RecMuonMinus_MuonMatch_phi;

      std::string HLTPath_;
      //TH1F* h_GenDiMuonM;
      
  
  
};

//
// constructors and destructor
//
ZpeakTrigger::ZpeakTrigger(const edm::ParameterSet& iConfig) {

  
  muonToken_ = (consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muon")));
  //genCollToken = consumes<pat::PackedGenParticleCollection>(theGenMuonLabel);
  vertexToken_ = (consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexTag")));
  triggerToken_ = (consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults")));
  HLTPath_ = iConfig.getParameter<std::string>("HLTPath");

  edm::Service<TFileService> fs;
  
  h_RecDiMuon_Tight_M = fs->make<TH1F>("h_RecDiMuon_Tight_M",";m_{#mu^{+}#mu^{-}};",60,75,105);
  h_RecDiMuon_Loose_M = fs->make<TH1F>("h_RecDiMuon_Loose_M",";m_{#mu^{+}#mu^{-}};",60,75,105);
  h_RecDiMuon_Trigger_M = fs->make<TH1F>("h_RecDiMuon_Trigger_M",";m_{#mu^{+}#mu^{-}};",60,75,105);
  h_RecDiMuon_MuonMatch_M = fs->make<TH1F>("h_RecDiMuon_MuonMatch_M",";m_{#mu^{+}#mu^{-}};",60,75,105);

  h_RecDiMuon_Tight_pt = fs->make<TH1F>("h_RecDiMuon_Tight_pt",";p_{T};",50,0,500);
  h_RecDiMuon_Loose_pt = fs->make<TH1F>("h_RecDiMuon_Loose_pt",";p_{T};",50,0,500);
  h_RecDiMuon_Trigger_pt = fs->make<TH1F>("h_RecDiMuon_Trigger_pt",";p_{T};",50,0,500);
  h_RecDiMuon_MuonMatch_pt = fs->make<TH1F>("h_RecDiMuon_MuonMatch_pt",";p_{T};",50,0,500);

  h_RecDiMuon_Tight_eta = fs->make<TH1F>("h_RecDiMuon_Tight_eta",";#eta;",60,-6,6);
  h_RecDiMuon_Loose_eta = fs->make<TH1F>("h_RecDiMuon_Loose_eta",";#eta;",60,-6,6);
  h_RecDiMuon_Trigger_eta = fs->make<TH1F>("h_RecDiMuon_Trigger_eta",";#eta;",60,-6,6);
  h_RecDiMuon_MuonMatch_eta = fs->make<TH1F>("h_RecDiMuon_MuonMatch_eta",";#eta;",60,-6,6);

  h_RecDiMuon_Tight_phi = fs->make<TH1F>("h_RecDiMuon_Tight_phi",";#phi;",40,-4,4);
  h_RecDiMuon_Loose_phi = fs->make<TH1F>("h_RecDiMuon_Loose_phi",";#phi;",40,-4,4);
  h_RecDiMuon_Trigger_phi = fs->make<TH1F>("h_RecDiMuon_Trigger_phi",";#phi;",40,-4,4);
  h_RecDiMuon_MuonMatch_phi = fs->make<TH1F>("h_RecDiMuon_MuonMatch_phi",";#phi;",40,-4,4);

  h_RecMuonPlus_Tight_pt = fs->make<TH1F>("h_RecMuonPlus_Tight_pt",";p_{T};",50,0,500);
  h_RecMuonPlus_Loose_pt = fs->make<TH1F>("h_RecMuonPlus_Loose_pt",";p_{T};",50,0,500);
  h_RecMuonPlus_Trigger_pt = fs->make<TH1F>("h_RecMuonPlus_Trigger_pt",";p_{T};",50,0,500);
  h_RecMuonPlus_MuonMatch_pt = fs->make<TH1F>("h_RecMuonPlus_MuonMatch_pt",";p_{T};",50,0,500);

  h_RecMuonPlus_Tight_eta = fs->make<TH1F>("h_RecMuonPlus_Tight_eta",";#eta;",60,-6,6);
  h_RecMuonPlus_Loose_eta = fs->make<TH1F>("h_RecMuonPlus_Loose_eta",";#eta;",60,-6,6);
  h_RecMuonPlus_Trigger_eta = fs->make<TH1F>("h_RecMuonPlus_Trigger_eta",";#eta;",60,-6,6);
  h_RecMuonPlus_MuonMatch_eta = fs->make<TH1F>("h_RecMuonPlus_MuonMatch_eta",";#eta;",60,-6,6);

  h_RecMuonPlus_Tight_phi = fs->make<TH1F>("h_RecMuonPlus_Tight_phi",";#phi;",40,-4,4);
  h_RecMuonPlus_Loose_phi = fs->make<TH1F>("h_RecMuonPlus_Loose_phi",";#phi;",40,-4,4);
  h_RecMuonPlus_Trigger_phi = fs->make<TH1F>("h_RecMuonPlus_Trigger_phi",";#phi;",40,-4,4);
  h_RecMuonPlus_MuonMatch_phi = fs->make<TH1F>("h_RecMuonPlus_MuonMatch_phi",";#phi;",40,-4,4);

  h_RecMuonMinus_Tight_pt = fs->make<TH1F>("h_RecMuonMinus_Tight_pt",";p_{T};",50,0,500);
  h_RecMuonMinus_Loose_pt = fs->make<TH1F>("h_RecMuonMinus_Loose_pt",";p_{T};",50,0,500);
  h_RecMuonMinus_Trigger_pt = fs->make<TH1F>("h_RecMuonMinus_Trigger_pt",";p_{T};",50,0,500);
  h_RecMuonMinus_MuonMatch_pt = fs->make<TH1F>("h_RecMuonMinus_MuonMatch_pt",";p_{T};",50,0,500);

  h_RecMuonMinus_Tight_eta = fs->make<TH1F>("h_RecMuonMinus_Tight_eta",";#eta;",60,-6,6);
  h_RecMuonMinus_Loose_eta = fs->make<TH1F>("h_RecMuonMinus_Loose_eta",";#eta;",60,-6,6);
  h_RecMuonMinus_Trigger_eta = fs->make<TH1F>("h_RecMuonMinus_Trigger_eta",";#eta;",60,-6,6);
  h_RecMuonMinus_MuonMatch_eta = fs->make<TH1F>("h_RecMuonMinus_MuonMatch_eta",";#eta;",60,-6,6);

  h_RecMuonMinus_Tight_phi = fs->make<TH1F>("h_RecMuonMinus_Tight_phi",";#phi;",40,-4,4);
  h_RecMuonMinus_Loose_phi = fs->make<TH1F>("h_RecMuonMinus_Loose_phi",";#phi;",40,-4,4);
  h_RecMuonMinus_Trigger_phi = fs->make<TH1F>("h_RecMuonMinus_Trigger_phi",";#phi;",40,-4,4);
  h_RecMuonMinus_MuonMatch_phi = fs->make<TH1F>("h_RecMuonMinus_MuonMatch_phi",";#phi;",40,-4,4);

  //h_GenDiMuonM = fs->make<TH1F>("h_GenDiMuonM",";m_{#mu^{+}#mu^{-}};",80,70,110);
 
}


ZpeakTrigger::~ZpeakTrigger() {
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// Check event pass HLT
bool ZpeakTrigger::HLTaccept(const edm::Event& iEvent, std::string& HLTPaths) {
  edm::Handle<edm::TriggerResults> triggerColleciton;
  iEvent.getByToken(triggerToken_, triggerColleciton);
  const edm::TriggerResults triggerObj = * (triggerColleciton.product()); 
  const edm::TriggerNames& triggerNames = iEvent.triggerNames(triggerObj);
  TString HLTPaths_compare = TString(HLTPaths);
  //bool passTrig=triggerresults->accept(triggerNames.triggerIndex(pathName));
  bool passTrig = false;
  for (size_t i = 0; i < triggerObj.size(); i++)
  {
    TString trigName = triggerNames.triggerName(i);
    bool find = false;
    if (trigName.Contains(HLTPaths_compare)) {
      find = true;
      int accept = triggerObj.accept(i);
      if ((accept == 1) && find) {
        passTrig = true;
        //std::cout<<trigName<<"haha"<<passTrig<<std::endl;
      } 
    }
  }
  return passTrig;
}
/*
bool MuonMiniAODAnalyzer::embedTriggerMatching(const edm::Event& iEvent,
                                               edm::Handle<edm::TriggerResults>& trigResults,
                                               const pat::Muon& mu,
                                               TString& Triggers) {
  for (const auto& trg : Triggers) {
    TString trg_tstr = TString(trg);
    bool matched = false;
    for (auto trigobj : mu.triggerObjectMatches()) {
      trigobj.unpackNamesAndLabels(iEvent, *trigResults);

      // check path names
      if (trg_tstr.Contains("HLT_")) {
        for (auto path : trigobj.pathNames(true, true)) {
          TString path_tstr = TString(path);
          if (path_tstr.Contains(trg_tstr)) {
            matched = true;
            break;
          }
        }
      }
      // check filters
      else {
        for (auto filter : trigobj.filterLabels()) {
          TString filter_tstr = TString(filter);
          if (filter_tstr.Contains(trg_tstr)) {
            matched = true;
            break;
          }
        }
      }

      if (matched)
        break;
    }
  }

  return mathced;
}
*/


// ------------ method called for each event  ------------
void ZpeakTrigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  using namespace std;
  using namespace pat;
  
  edm::Handle<vector<pat::Muon>> muons;
  iEvent.getByToken(muonToken_, muons);

  /* 
  edm::Handle <pat::PackedGenParticleCollection> genColl;
  iEvent.getByToken(genCollToken, genColl);
  */

  edm::Handle<vector<reco::Vertex>> vertices;
  iEvent.getByToken(vertexToken_, vertices);

  if(!vertices.isValid()) {
    throw cms::Exception("Vertex collection not valid!"); 
  } 

   // Let's check that we have at least one good vertex! 
  
  std::vector<reco::Vertex>::const_iterator firstGoodVertex = vertices->end();

   for (std::vector<reco::Vertex>::const_iterator it=vertices->begin(); it!=firstGoodVertex; ++it) {
    if (!it->isFake() && it->ndof()>4 && it->position().Rho()<2. && std::abs(it->position().Z())<24.) {
      if(firstGoodVertex == vertices->end()) firstGoodVertex = it;
      break;
    }
  }
  // Require a good vertex
  if(firstGoodVertex == vertices->end()) return;

  /////////////////////////////////////////////////
  // Dimuon pairs /////////////////////////////////
  /////////////////////////////////////////////////
    
  //put your code here
  // Tight Muon
  // find mu+
  
  for (auto mup = muons->cbegin(); mup != muons->cend(); ++mup) {
      double mupRecPt = ((mup->p4()).pt());
      double mupRecEta = ((mup->p4()).eta());
      double mupRecPhi = ((mup->p4()).phi());

      // Use tight muon ID, pT and eta cut were mentioned in AN2018/073 - Zhuolin 2020-12-22
      if ( not (mup->charge() > 0 ) ) continue;
      if ( not (fabs(mup->eta()) < 2.4) ) continue;
      if (!mup->isTightMuon(*firstGoodVertex)) continue; // tight muon ID
      // PF Isolation very loose
      if ( not ((mup->pfIsolationR04().sumChargedHadronPt + std::max(0., mup->pfIsolationR04().sumNeutralHadronEt + mup->pfIsolationR04().sumPhotonEt - 0.5*mup->pfIsolationR04().sumPUPt))/mup->pt() < 0.4) ) continue; 
      
      // find mu-
           for (auto mum = muons->cbegin(); mum != muons->cend(); ++mum) {
                double mumRecPt = ((mum->p4()).pt());
                double mumRecEta = ((mum->p4()).eta());
                double mumRecPhi = ((mum->p4()).phi());

                if ( not (mum->charge() < 0 ) ) continue;
                if ( not (fabs(mum->eta()) < 2.4) ) continue;
                if (!mum->isTightMuon(*firstGoodVertex)) continue; // tight muon ID
                // PF Isolation very loose
                if ( not ((mum->pfIsolationR04().sumChargedHadronPt + std::max(0., mum->pfIsolationR04().sumNeutralHadronEt + mum->pfIsolationR04().sumPhotonEt - 0.5*mum->pfIsolationR04().sumPUPt))/mum->pt() < 0.4) ) continue; 
                // pt constrains - Zhuolin 2020-10-12
                if ( mup->pt() > mum->pt() ){
                  if ( mup->pt() <= 25.0 ) continue;
                  if ( mum->pt() <= 15.0 ) continue;
                }
                else
                {
                  if ( mup->pt() <= 15.0 ) continue;
                  if ( mum->pt() <= 25.0 ) continue;
                }
                double diMuonRecMass = ((mup->p4() + mum->p4()).M());
                double diMuonRecPt = ((mup->p4() + mum->p4()).pt());
                double diMuonRecEta = ((mup->p4() + mum->p4()).eta());
                double diMuonRecPhi = ((mup->p4() + mum->p4()).phi());
                if ( diMuonRecMass < 75 || diMuonRecMass > 105) continue; // only look around the Z peak
                
                h_RecDiMuon_Tight_M->Fill(diMuonRecMass);
                h_RecDiMuon_Tight_pt->Fill(diMuonRecPt);
                h_RecDiMuon_Tight_eta->Fill(diMuonRecEta);
                h_RecDiMuon_Tight_phi->Fill(diMuonRecPhi);
                h_RecMuonPlus_Tight_pt->Fill(mupRecPt);
                h_RecMuonPlus_Tight_eta->Fill(mupRecEta);
                h_RecMuonPlus_Tight_phi->Fill(mupRecPhi);
                h_RecMuonMinus_Tight_pt->Fill(mumRecPt);
                h_RecMuonMinus_Tight_eta->Fill(mumRecEta);
                h_RecMuonMinus_Tight_phi->Fill(mumRecPhi);
           }
  }

    // Loose Muon
    // find mu+
    for (auto mup = muons->cbegin(); mup != muons->cend(); ++mup) {
        const char *hltName = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*";
        double mupRecPt = ((mup->p4()).pt());
        double mupRecEta = ((mup->p4()).eta());
        double mupRecPhi = ((mup->p4()).phi());
        if ( not (mup->charge() > 0 ) ) continue;
        if (!mup->isLooseMuon()) continue; // Loose Muon ID 
        // find mu-
             for (auto mum = muons->cbegin(); mum != muons->cend(); ++mum) {
                  double mumRecPt = ((mum->p4()).pt());
                  double mumRecEta = ((mum->p4()).eta());
                  double mumRecPhi = ((mum->p4()).phi());
                  if ( not (mum->charge() < 0 ) ) continue;
                  if (!mum->isLooseMuon()) continue; // Loose muon ID
                  
                  double diMuonRecMass = ((mup->p4() + mum->p4()).M());
                  double diMuonRecPt = ((mup->p4() + mum->p4()).pt());
                  double diMuonRecEta = ((mup->p4() + mum->p4()).eta());
                  double diMuonRecPhi = ((mup->p4() + mum->p4()).phi());
                  if ( diMuonRecMass < 75 || diMuonRecMass > 105) continue; // only look around the Z peak
                  const pat::Muon *muon1 = &(*mup);
                  const pat::Muon *muon2 = &(*mum);
                  if (muon1->triggerObjectMatchByPath(hltName) != nullptr && muon2->triggerObjectMatchByPath(hltName) != nullptr) {
                      h_RecDiMuon_MuonMatch_M->Fill(diMuonRecMass);
                      h_RecDiMuon_MuonMatch_pt->Fill(diMuonRecPt);
                      h_RecDiMuon_MuonMatch_eta->Fill(diMuonRecEta);
                      h_RecDiMuon_MuonMatch_phi->Fill(diMuonRecPhi);
                      h_RecMuonPlus_MuonMatch_pt->Fill(mupRecPt);
                      h_RecMuonPlus_MuonMatch_eta->Fill(mupRecEta);
                      h_RecMuonPlus_MuonMatch_phi->Fill(mupRecPhi);
                      h_RecMuonMinus_MuonMatch_pt->Fill(mumRecPt);
                      h_RecMuonMinus_MuonMatch_eta->Fill(mumRecEta);
                      h_RecMuonMinus_MuonMatch_phi->Fill(mumRecPhi);

                  }
                  if (HLTaccept(iEvent, HLTPath_)){
                    
                    h_RecDiMuon_Trigger_M->Fill(diMuonRecMass);
                    h_RecDiMuon_Trigger_pt->Fill(diMuonRecPt);
                    h_RecDiMuon_Trigger_eta->Fill(diMuonRecEta);
                    h_RecDiMuon_Trigger_phi->Fill(diMuonRecPhi);
                    h_RecMuonPlus_Trigger_pt->Fill(mupRecPt);
                    h_RecMuonPlus_Trigger_eta->Fill(mupRecEta);
                    h_RecMuonPlus_Trigger_phi->Fill(mupRecPhi);
                    h_RecMuonMinus_Trigger_pt->Fill(mumRecPt);
                    h_RecMuonMinus_Trigger_eta->Fill(mumRecEta);
                    h_RecMuonMinus_Trigger_phi->Fill(mumRecPhi);
                  }  
                  h_RecDiMuon_Loose_M->Fill(diMuonRecMass);
                  h_RecDiMuon_Loose_pt->Fill(diMuonRecPt);
                  h_RecDiMuon_Loose_eta->Fill(diMuonRecEta);
                  h_RecDiMuon_Loose_phi->Fill(diMuonRecPhi);
                  h_RecMuonPlus_Loose_pt->Fill(mupRecPt);
                  h_RecMuonPlus_Loose_eta->Fill(mupRecEta);
                  h_RecMuonPlus_Loose_phi->Fill(mupRecPhi);
                  h_RecMuonMinus_Loose_pt->Fill(mumRecPt);
                  h_RecMuonMinus_Loose_eta->Fill(mumRecEta);
                  h_RecMuonMinus_Loose_phi->Fill(mumRecPhi);
             }
    
    }
    
                /*
                int idxmup_Gen = -1;
                int idxmum_Gen = -1;

                // Gen matching
                for (auto genParticle = genColl->cbegin(); genParticle != genColl->cend(); ++genParticle) {
                    const pat::PackedGenParticle& mcMuon = (*genParticle);
                    if ( not (abs(mcMuon.pdgId()) == 13 ) ) continue; // make sure it is a muon
                    if ( fabs(mcMuon.eta()) > 2.4 ) continue;
                    if ( fabs(mcMuon.eta()) > 2.4 ) continue;
                    if ( not (mcMuon.pt() > 1.5 ) ) continue;
                    if ( deltaR(mcMuon, *(mup->innerTrack())) < 0.1 && mcMuon.charge() > 0 ) idxmup_Gen = std::distance(genColl->cbegin(), genParticle);
                    if ( deltaR(mcMuon, *(mum->innerTrack())) < 0.1 && mcMuon.charge() < 0 ) idxmum_Gen = std::distance(genColl->cbegin(), genParticle);
                }
                if ( idxmup_Gen > -1 && idxmum_Gen > -1) {
                    double diMuonRecMassGen = (genColl->at(idxmup_Gen).p4() + genColl->at(idxmum_Gen).p4()).M();
                    h_GenDiMuonM->Fill(diMuonRecMassGen);
                }
                */
           
  
}


// ------------ method called once each job just before starting event loop  ------------
void ZpeakTrigger::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------
void ZpeakTrigger::endJob() {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void ZpeakTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(ZpeakTrigger);
