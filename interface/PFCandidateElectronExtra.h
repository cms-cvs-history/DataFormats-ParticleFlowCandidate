#ifndef ParticleFlowCandidate_PFCandidateElectronExtra_h
#define ParticleFlowCandidate_PFCandidateElectronExtra_h

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"


namespace reco {
/** \class reco::PFCandidateElectronExtra
 *
 * extra information on the electron particle candidate from particle flow
 *
 */
  class PFCandidateElectronExtra { 
  public:    
    enum StatusFlag {
      X=0,                            // undefined
      Selected,                       // selected 
      ECALDrivenPreselected,          // ECAL-driven electron pre-selected
      MVASelected,                    // Passed the internal particle-flow selection (mva selection)
      Rejected                        // Rejected 
    };
    
    enum MvaVariable {
      NONE=0,
      MVA_LnPtGsf,
      MVA_EtaGsf,
      MVA_SigmaPtOverPt,
      MVA_Fbrem,
      MVA_Chi2Gsf,
      MVA_NhitsKf,
      MVA_Chi2Kf,
      MVA_EtotOverPin,
      MVA_EseedOverPout,
      MVA_EbremOverDeltaP,
      MVA_DeltaEtaTrackCluster,
      MVA_LogSigmaEtaEta,
      MVA_HOverHE,
      MVA_LateBrem,
      MVA_FirstBrem 
    };


  public:
    /// constructor
    PFCandidateElectronExtra();
    /// constructor
    PFCandidateElectronExtra(const GsfTrackRef&);
    /// destructor
    ~PFCandidateElectronExtra(){;}

    /// set gsftrack reference 
    void setGsfTrackRef(const reco::GsfTrackRef& ref);   

    /// set kf track reference
    void setKfTrackRef(const reco::TrackRef & ref);

    /// return a reference to the corresponding GSF track, if an electron. 
    /// otherwise, return a null reference 
    reco::GsfTrackRef gsfTrackRef() const { return gsfTrackRef_; }     

    /// set LateBrem
    void setLateBrem(float val); 
    /// set EarlyBrem
    void setEarlyBrem(float val);

    /// set the pout (not trivial to get from the GSF track)
    void setGsfTrackPout(const math::XYZTLorentzVector& pout);
    
    /// set the cluster energies. the Pout should be saved first 
    void setClusterEnergies(const std::vector<float>& energies);

    /// set the sigmaetaeta
    void setSigmaEtaEta(float val);

    /// set the had energy. The cluster energies should be entered before
    void setHadEnergy(float val);

    /// set status 
    void setStatus(StatusFlag type,bool status=true);

    /// access to the status
    bool electronStatus(StatusFlag) const ;

 private:
    void  setVariable(MvaVariable type,float var);
    
 private:
    /// Ref to the GSF track
    reco::GsfTrackRef gsfTrackRef_;
    /// Ref to the KF track
    reco::TrackRef kfTrackRef_;

    /// energy of individual clusters (corrected). The first cluster is the seed
    std::vector<float> clusterEnergies_;

    /// mva variables  -  transient !
    std::vector<float> mvaVariables_;
    
    /// status of  mva variables
    int mvaStatus_;

    /// Status of the electron
    int status_;

    /// Variables entering the MVA that should be saved
    math::XYZTLorentzVector pout_;
    float earlyBrem_;
    float lateBrem_;
    float sigmaEtaEta_;
    float hadEnergy_;

  };

}
#endif
