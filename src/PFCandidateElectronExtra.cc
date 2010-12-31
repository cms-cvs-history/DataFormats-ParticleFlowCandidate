#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateElectronExtra.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"

using namespace reco;

PFCandidateElectronExtra::PFCandidateElectronExtra() {
  status_ = 0;  
  mvaStatus_ = 0;
  pout_ = math::XYZTLorentzVector(0.,0.,0.,0.);
  hadEnergy_ = -9999. ;
  sigmaEtaEta_ = -9999.;

  mvaVariables_.resize(15);
  
  gsfTrackRef_ = GsfTrackRef();
  kfTrackRef_ = TrackRef();
}

PFCandidateElectronExtra::PFCandidateElectronExtra(const reco::GsfTrackRef& gsfTrack) {
  status_ = 0;  
  mvaStatus_ = 0;
  pout_ = math::XYZTLorentzVector(0.,0.,0.,0.);
  hadEnergy_ = -9999. ;
  sigmaEtaEta_ = -9999.;

  mvaVariables_.resize(15);
  gsfTrackRef_ = gsfTrack;
  kfTrackRef_ = TrackRef();
  
  setVariable(MVA_LnPtGsf,log(gsfTrackRef_->ptMode()));
  setVariable(MVA_EtaGsf,gsfTrackRef_->etaMode());
  setVariable(MVA_Chi2Gsf,gsfTrackRef_->normalizedChi2());  
  float ptmodeerror=gsfTrackRef_->ptModeError() ;
  if(ptmodeerror>0.)
    setVariable(MVA_SigmaPtOverPt,ptmodeerror/gsfTrackRef_->ptMode());
  else
    setVariable(MVA_SigmaPtOverPt,-999.);
  
  setVariable(MVA_Fbrem,(gsfTrackRef_->ptMode() - pout_.pt())/gsfTrackRef_->ptMode());
}

void PFCandidateElectronExtra::setGsfTrackRef(const reco::GsfTrackRef& ref) {
  gsfTrackRef_= ref;
}   

void PFCandidateElectronExtra::setGsfTrackPout(const math::XYZTLorentzVector& pout) {
  pout_ = pout;
  
}

void PFCandidateElectronExtra::setKfTrackRef(const reco::TrackRef & ref){
  kfTrackRef_ = ref;
  setVariable(MVA_NhitsKf,kfTrackRef_->hitPattern().trackerLayersWithMeasurement());
  setVariable(MVA_Chi2Kf,kfTrackRef_->normalizedChi2());
}

void PFCandidateElectronExtra::setLateBrem(float val) {
  lateBrem_ = val;
  setVariable(MVA_LateBrem,val);
}

void PFCandidateElectronExtra::setEarlyBrem(float val) {
  earlyBrem_ = val;
  setVariable(MVA_FirstBrem,val);
}

void PFCandidateElectronExtra::setHadEnergy(float val) {
  hadEnergy_ = val;
  if(clusterEnergies_.size()>0)
    setVariable(MVA_HOverHE,hadEnergy_/(hadEnergy_+clusterEnergies_[0]));
}

void PFCandidateElectronExtra::setSigmaEtaEta(float val) {
  sigmaEtaEta_ = val;
  setVariable(MVA_LogSigmaEtaEta,val);
}

void PFCandidateElectronExtra::setClusterEnergies(const std::vector<float>& energies){
  clusterEnergies_=energies;

  if(pout_.t()!=0.)
    setVariable(MVA_EseedOverPout,clusterEnergies_[0]/pout_.t());
 
  static float m_el2=0.00051*0.00051;
  float Ein_gsf =sqrt(gsfTrackRef_->pMode()*
		      gsfTrackRef_->pMode()+m_el2);
  
  float etot=0;
  unsigned size=clusterEnergies_.size();
  float ebrem=0.;
  for(unsigned ic=0;ic<size;++ic) {    
    etot+=clusterEnergies_[ic];
    if(ic>0)
      ebrem+=clusterEnergies_[ic];
  }
  setVariable(MVA_EtotOverPin,etot/Ein_gsf);
  setVariable(MVA_EbremOverDeltaP,ebrem/(Ein_gsf-pout_.t()));  
}



void PFCandidateElectronExtra::setVariable(MvaVariable type,float val) {
  if(!type) return;
  
  mvaVariables_[type-1]=val;
  mvaStatus_ |= (1 << (type-1)) ;    
}


void PFCandidateElectronExtra::setStatus(StatusFlag type,bool status){
  if(status)     {
    status_ |= (1 << type);
  }
  else     {
    status_ &= ~(1 <<type);
  }
}

bool PFCandidateElectronExtra::electronStatus(StatusFlag flag) const {
  return status_ & (1<<flag) ;
}
