#ifndef ParticleFlowCandidate_PFCandidate_h
#define ParticleFlowCandidate_PFCandidate_h
/** \class reco::PFCandidate
 *
 * particle candidate from particle flow
 *
 */

#include <iostream>

#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockFwd.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

namespace reco {
  /**\class PFCandidate
     \brief Particle reconstructed by the particle flow algorithm.
          
     \author Colin Bernet
     \date   February 2007
  */
  class PFCandidate : public LeafCandidate {

  public:
    
    /// particle types
    enum ParticleType {
      X=0,     // undefined
      h,       // charged hadron
      e,       // electron 
      mu,      // muon 
      gamma,   // photon
      h0       // neutral hadron
    };

    /// default constructor
    PFCandidate();
    
    PFCandidate( Charge q, 
		 const LorentzVector & p4, 
		 ParticleType particleId, 
		 reco::PFBlockRef blockRef );

    /// destructor
    virtual ~PFCandidate() {}

    /// return a clone
    virtual PFCandidate * clone() const;
    
    /// set track reference
    void    setTrackRef(const reco::TrackRef& ref);

    /// set muon reference
    void    setMuonRef(const reco::MuonRef& ref);

    /// set corrected Ecal energy 
    void    setEcalEnergy( float ee ) {ecalEnergy_ = ee;}

    /// return corrected Ecal energy
    double ecalEnergy() const { return ecalEnergy_;}

    /// set corrected Hcal energy 
    void    setHcalEnergy( float eh ) {hcalEnergy_ = eh;}

    /// return corrected Hcal energy
    double hcalEnergy() const { return hcalEnergy_;}

    /// set corrected PS1 energy
    void    setPs1Energy( float e1 ) {ps1Energy_ = e1;}

    /// return corrected PS1 energy
    double pS1Energy() const { return ps1Energy_;}

    /// set corrected PS2 energy 
    void    setPs2Energy( float e2 ) {ps2Energy_ = e2;}

    /// return corrected PS2 energy
    double pS2Energy() const { return ps2Energy_;}

    /// particle momentum *= rescaleFactor
    void    rescaleMomentum( double rescaleFactor );

    enum Flags {
      NORMAL=0,
      E_PHI_SMODULES,
      E_ETA_0,
      E_ETA_MODULES,
      E_BARREL_ENDCAP,
      E_PRESHOWER_EDGE,
      E_PRESHOWER,
      E_ENDCAP_EDGE,
      H_ETA_0,
      H_BARREL_ENDCAP,
      H_ENDCAP_VFCAL,
      H_VFCAL_EDGE,  
      T_TO_NUCLINT,
      T_FROM_NUCLINT,
      T_FROM_V0,
      T_FROM_GAMMACONV
    };
    
    /// set a given flag
    void setFlag(Flags theFlag, bool value);
    
    /// return a given flag
    bool flag(Flags theFlag) const;

    /// set uncertainty on momentum
    void setDeltaP(double dp ) {deltaP_ = dp;}

    /// uncertainty on 3-momentum
    double deltaP() const { return deltaP_;}
    

    /// set mva for electron-pion discrimination
    void set_mva_e_pi( float mva ) { mva_e_pi_ = mva; } 
    
    /// mva for electron-pion discrimination
    float mva_e_pi() const { return mva_e_pi_;}

    
    /// set mva for electron-muon discrimination
    void set_mva_e_mu( float mva ) { mva_e_mu_ = mva; } 
    
    /// mva for electron-muon discrimination
    float mva_e_mu() const { return mva_e_mu_;}


    /// set mva for pi-muon discrimination
    void set_mva_pi_mu( float mva ) { mva_pi_mu_ = mva; } 

    /// mva for pi-muon discrimination
    float mva_pi_mu() const { return mva_pi_mu_;}
    

    /// set mva for gamma detection
    void set_mva_nothing_gamma( float mva ) { mva_nothing_gamma_ = mva; } 

    /// mva for gamma detection
    float mva_nothing_gamma() const { return mva_nothing_gamma_;}


    /// set mva for neutral hadron detection
    void set_mva_nothing_nh( float mva ) { mva_nothing_nh_ = mva; } 

    /// mva for neutral hadron detection
    float mva_nothing_nh() const { return mva_nothing_nh_;}


    /// set mva for neutral hadron - gamma discrimination
    void set_mva_gamma_nh( float mva ) { mva_gamma_nh_ = mva; } 

    /// mva for neutral hadron - gamma discrimination
    float mva_gamma_nh() const { return mva_gamma_nh_;}


    /// particle identification code
    virtual int particleId() const { return particleId_;}
    
    /// return reference to the block
    const reco::PFBlockRef& blockRef() const { return blockRef_; } 

    /// return a reference to the corresponding track, if charged. 
    /// otherwise, return a null reference
    reco::TrackRef trackRef() const { return trackRef_; }

    /// return a reference to the corresponding muon, if a muon. 
    /// otherwise, return a null reference
    reco::MuonRef muonRef() const { return muonRef_; }    

    
    /// return indices of elements used in the block
    /*     const std::vector<unsigned>& elementIndices() const {  */
    /*       return elementIndices_; */
    /*     } */
    
    /// return reference to the block
    PFBlockRef block() const { return blockRef_; } 
  

    static const float bigMva_;

    friend std::ostream& operator<<( std::ostream& out, 
				     const PFCandidate& c );
  
  private:
    void setFlag(unsigned shift, unsigned flag, bool value);

    bool flag(unsigned shift, unsigned flag) const;
   
    /// particle identification
    ParticleType            particleId_; 
    
    /// reference to the corresponding PFBlock
    reco::PFBlockRef        blockRef_;

    /// indices of the elements used in the PFBlock
    /*     std::vector<unsigned>   elementIndices_; */

    reco::TrackRef trackRef_;
    
    reco::MuonRef  muonRef_;
    
    /// corrected ECAL energy
    float        ecalEnergy_;

    /// corrected HCAL energy
    float        hcalEnergy_;

    /// corrected PS1 energy
    float        ps1Energy_;

    /// corrected PS2 energy
    float        ps2Energy_;

    /// all flags, packed (ecal regional, hcal regional, tracking)
    unsigned     flags_;

    /// uncertainty on 3-momentum
    double       deltaP_;

    /// mva for electron-pion discrimination
    float       mva_e_pi_;

    /// mva for electron-muon discrimination
    float       mva_e_mu_;

    /// mva for pi-muon discrimination
    float       mva_pi_mu_;
    
    /// mva for gamma detection
    float       mva_nothing_gamma_;

    /// mva for neutral hadron detection
    float       mva_nothing_nh_;

    /// mva for neutral hadron - gamma discrimination
    float       mva_gamma_nh_;
  };

  /// particle ID component tag
  struct PFParticleIdTag { };

  /// get default PFBlockRef component
  /// as: pfcand->get<PFBlockRef>();
  GET_DEFAULT_CANDIDATE_COMPONENT( PFCandidate, PFBlockRef, block );

  /// get int component
  /// as: pfcand->get<int, PFParticleIdTag>();
  GET_CANDIDATE_COMPONENT( PFCandidate, int, particleId, PFParticleIdTag );

}

#endif
