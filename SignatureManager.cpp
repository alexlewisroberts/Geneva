//------------------------------------------------------------------------------
/// \file SignatureManager.cpp
//
// Author(s):
//    Frank Tackmann
//
// Copyright:
//    Copyright (C) 2012  Frank Tackmann
//
//    This file is part of the Geneva MC framework. Geneva is distributed under
//    the terms of the GNU General Public License version 3 (GPLv3), see the
//    COPYING file that comes with this distribution for details.
//    Please respect the academic usage guidelines in the GUIDELINES file.
//
// Description:
//    Implementation of class SignatureManager
//------------------------------------------------------------------------------

#include "SignatureManager.h"
#include "Logger.h"
#include "QCD.h"
#include "SignatureSet.h"

namespace Geneva
{

//------------------------------------------------------------------------------
/**
 * \brief Generates SignatureSets for e+e- -> n partons.
 * \param numPartons The number of partons in the final state
 * \param numFlavors The number of quark flavors to include
 * \return SignatureSet containing all required Signatures.
 *
 * Should generate these with a somewhat more intelligent algorithm.
 */
SignatureSet SignatureManager::getSignatureseeJets(size_t numPartons, int numFlavors)
{
   // generate recursively for numPartons > 2
   if (numPartons > 2)
      return QCDEmissions(getSignatureseeJets(numPartons - 1, numFlavors), numFlavors);

   if (numFlavors < 1 || numFlavors > 6) {
      Logger::globalLogger() << ERROR << "SignatureManager: Number of light flavors should be between 1 and 6!" << std::endl;
      exit(1);
   }

   // signatures for ee -> 2 partons
   if (numPartons == 2) {
      SignatureSet sigs;
      // TODO: code somewhere depends on which is A/B!!
      Signature justEE;
      justEE.setInitialA(PdgID::kPositron);
      justEE.setInitialB(PdgID::kElectron);
      for (int i = 1; i <= numFlavors; ++i) {
         Signature sig(justEE);
         sig.insertFinal(PdgID(i));
         sig.insertFinal(PdgID(i).antiPartner());
         sigs.insert(sig);
      }
      return sigs;
   }
   
   /*
   // signatures for ee -> 4 partons
   if (numPartons == 4) {
      SignatureSet sigs;
      // TODO: code somewhere depends on which is A/B!!
      Signature justEE;
      justEE.setInitialA(PdgID::kPositron);
      justEE.setInitialB(PdgID::kElectron);
      for (int i = 1; i <= numFlavors; ++i) {
         for (int j = 1; j <= numFlavors; ++j) {
            Signature sig(justEE);
            sig.insertFinal(PdgID(i));
            sig.insertFinal(PdgID(i).antiPartner());
            sig.insertFinal(PdgID(j));
            sig.insertFinal(PdgID(j).antiPartner());
            sigs.insert(sig);
         }
      }
      return sigs;
   }
*/
   Logger::globalLogger() << ERROR << "SignatureManager: Don't know what to do with " << numPartons << " partons." << std::endl;
   return SignatureSet();
}

//------------------------------------------------------------------------------
/**
 * \brief Generates SignatureSets for pp ->W^+ + n partons.
 * \param lepton The ID of the charged lepton in the W decay (can pass either the particle or antiparticle)
 * \param numPartons The number of partons in the final state
 * \param numFlavors The number of quark flavors to include
 * \param doDecay Whether to decay the W
 * \return SignatureSet containing all required Signatures.
 *
 */
SignatureSet SignatureManager::getSignaturespp2WPlusJets(PdgID lepton, size_t numPartons, int numFlavors, bool doDecay)
{

   if (numPartons > 2) {
      Logger::globalLogger() << ERROR << " SignatureManager::getSignaturespp2WPlusJets for more than 2 extra partons in the final state not yet available" << std::endl;
      std::exit(1);
   }
   // generate recursively for numPartons = 1
   if (numPartons == 1 )
      return QCDEmissions(getSignaturespp2WPlusJets(lepton, numPartons - 1, numFlavors, doDecay), numFlavors);

   // recursive generation doesn't generate all the Signatures for numPartons >= 2 . Do it explicitly!
   if (numPartons == 2 )
      return getSignaturespp2WPlus2Jets(lepton, numFlavors, doDecay);

   if (numFlavors < 1 || numFlavors > 6) {
      Logger::globalLogger() << ERROR << "SignatureManager: Number of light flavors should be between 1 and 6!" << std::endl;
      exit(1);
   }

   // (W+) + 0 jets: just (u-type)+(d-type-bar) -> W+
   if (numPartons == 0) {

      SignatureSet sigs;

      // set up allowed up and down-type quarks
      std::vector<int> upType, downType;
      for (int i = 2; i <= numFlavors; i += 2) upType.push_back(i);
      for (int i = 1; i <= numFlavors; i += 2) downType.push_back(i);

      for (size_t ui = 0; ui < upType.size(); ++ui) {
         for (size_t di = 0; di < downType.size(); ++di) {
            // up is A, down is B
            Signature sig;
            sig.setInitialA(PdgID(upType[ui]));
            sig.setInitialB(PdgID(downType[di]).antiPartner());

            if (doDecay) {
               sig.insertFinal(lepton.isParticle() ? lepton.antiPartner() : lepton);
               PdgID nu(abs(lepton.code()) + 1);
               sig.insertFinal(nu);
            } else {
               sig.insertFinal(PdgID::kWPlus);
            }
            sigs.insert(sig);

            // up is B, down is A
            sigs.insert(swapInitial(sig));
         }
      }
      return sigs;
   } else {
      // can only get here for numPartons < 0
      Logger::globalLogger() << ERROR << "SignatureManager: Can't set numPartons < 0!" << std::endl;
      return SignatureSet();
   }

}

//------------------------------------------------------------------------------
/**
 * \brief Generates SignatureSets for pp ->W^- + n partons.
 * \param lepton The ID of the charged lepton in the W decay (can pass either the particle or antiparticle)
 * \param numPartons The number of partons in the final state
 * \param numFlavors The number of quark flavors to include
 * \param doDecay Whether to decay the W
 * \return SignatureSet containing all required Signatures.
 *
 */
SignatureSet SignatureManager::getSignaturespp2WMinusJets(PdgID lepton, size_t numPartons, int numFlavors, bool doDecay)
{
   return invertedSignatures(getSignaturespp2WPlusJets(lepton, numPartons, numFlavors, doDecay));
}

//------------------------------------------------------------------------------
/**
 * \brief Generates SignatureSets for pp ->W^(+/-) + n partons.
 * \param lepton The ID of the charged lepton in the W decay (can pass either the particle or antiparticle)
 * \param numPartons The number of partons in the final state
 * \param numFlavors The number of quark flavors to include
 * \param doDecay Whether to decay the W
 * \return SignatureSet containing all required Signatures.
 *
 */
SignatureSet SignatureManager::getSignaturespp2WJets(PdgID lepton, size_t numPartons, int numFlavors, bool doDecay)
{
   return getSignaturespp2WMinusJets(lepton, numPartons, numFlavors, doDecay) +
          getSignaturespp2WPlusJets(lepton, numPartons, numFlavors, doDecay);
}

//------------------------------------------------------------------------------
/**
 * \brief Generates SignatureSets for pp ->Z + n partons.
 * \param lepton The ID of the fermion in the Z decay
 * \param numPartons The number of partons in the final state
 * \param numFlavors The number of quark flavors to include
 * \param doDecay Whether to decay the W
 * \return SignatureSet containing all required Signatures.
 *
 */
SignatureSet SignatureManager::getSignaturespp2ZJets(PdgID fermion, size_t numPartons, int numFlavors, bool doDecay)
{
   // generate recursively for numPartons > 0
   if (numPartons > 0)
      return QCDEmissions(getSignaturespp2ZJets(fermion, numPartons - 1, numFlavors, doDecay), numFlavors);

   if (numFlavors < 1 || numFlavors > 6) {
      Logger::globalLogger() << ERROR << "SignatureManager: Number of light flavors should be between 1 and 6!" << std::endl;
      exit(1);
   }

   // Z + 0 jets: just qq~ > Z
   if (numPartons == 0) {
      SignatureSet sigs;
      for (int qi = 1; qi <= numFlavors; ++qi) {
         Signature sig;
         sig.setInitialA(PdgID(qi));
         sig.setInitialB(PdgID(qi).antiPartner());
         if (doDecay) {
            sig.insertFinal(fermion);
            sig.insertFinal(fermion.antiPartner());
         } else {
            sig.insertFinal(PdgID::kZ);
         }
         sigs.insert(sig);
         // up is B, down is A
         sigs.insert(swapInitial(sig));
      }
      return sigs;
   } else {
      // can only get here for numPartons < 0
      Logger::globalLogger() << ERROR << "SignatureManager: Can't set numPartons < 0!" << std::endl;
      return SignatureSet();
   }
}

//------------------------------------------------------------------------------
/// Return the set of Signatures representing all possible single QCD emissions from \p sig
SignatureSet SignatureManager::QCDEmissions(const Signature& sig, int numFlavors)
{
   SignatureSet sigs;

   // if any QCD particles present (inc. initial state), can emit a gluon
   if (std::count_if(sig.begin(), sig.end(), IsQCD()) > 0) {
      Signature tmp(sig);
      tmp.insertFinal(PdgID::kGluon);
      sigs.insert(tmp);
   }

   // final-state gluon splitting (note that previous step handled g->gg)
   if (sig.includesFinal(PdgID::kGluon)) {
      for (int i = 1; i <= numFlavors; ++i) {
         Signature tmp(sig);
         tmp.erase(tmp.findFinal(PdgID::kGluon));
         // BUG?: previous version erased all gluons in the final state
//          tmp.eraseFinal(PdgID::kGluon);
         tmp.insertFinal(PdgID(i));
         tmp.insertFinal(PdgID(i).antiPartner());
         sigs.insert(tmp);
      }
   }

   // initial q -> (g) q
   if (*sig.initialA() == PdgID::kGluon) {
      for (int i = -numFlavors; i <= numFlavors; ++i) {
         if (i == 0) continue;
         Signature tmp(sig);
         tmp.setInitialA(PdgID(i));
         tmp.insertFinal(PdgID(i));
         sigs.insert(tmp);
      }
   }
   if (*sig.initialB() == PdgID::kGluon) {
      for (int i = -numFlavors; i <= numFlavors; ++i) {
         if (i == 0) continue;
         Signature tmp(sig);
         tmp.setInitialB(PdgID(i));
         tmp.insertFinal(PdgID(i));
         sigs.insert(tmp);
      }
   }

   // initial g > qq~
   if (sig.initialA()->isQuark()) {
      Signature tmp(sig);
      tmp.setInitialA(PdgID::kGluon);
      tmp.insertFinal(sig.initialA()->antiPartner());
      sigs.insert(tmp);
   }
   if (sig.initialB()->isQuark()) {
      Signature tmp(sig);
      tmp.setInitialB(PdgID::kGluon);
      tmp.insertFinal(sig.initialB()->antiPartner());
      sigs.insert(tmp);
   }
   return sigs;
}

//------------------------------------------------------------------------------
/// Return the set of Signatures representing all possible single QCD emissions from \p sigs
SignatureSet SignatureManager::QCDEmissions(const SignatureSet& sigs, int numFlavors)
{
   SignatureSet emitted;
   for (SignatureSet::iterator it = sigs.begin(); it != sigs.end(); ++it)
      emitted += QCDEmissions(*it, numFlavors);

   return emitted;
}

//------------------------------------------------------------------------------
/// Return an "inverted" Signature -- with all IDs switched with their antiparticles
Signature SignatureManager::invertedSignature(const Signature& sig)
{
   Signature inverted;
   if (sig.initialA() != sig.end())
      inverted.setInitialA(sig.initialA()->antiPartner());
   if (sig.initialB() != sig.end())
      inverted.setInitialB(sig.initialB()->antiPartner());
   for (Signature::iterator it = sig.beginFinal(); it != sig.endFinal(); ++it)
      inverted.insertFinal(it->antiPartner());
   return inverted;
}

//------------------------------------------------------------------------------
/// Return an "inverted" SignatureSet -- same signatures but all IDs switched with their antiparticles
SignatureSet SignatureManager::invertedSignatures(const SignatureSet& sigs)
{
   SignatureSet inverted;
   for (SignatureSet::iterator it = sigs.begin(); it != sigs.end(); ++it)
      inverted.insert(invertedSignature(*it));
   return inverted;
}

//------------------------------------------------------------------------------
/// Return a Signature with initialA <-> initialB
Signature SignatureManager::swapInitial(const Signature& sig)
{
   Signature swapped;
   if (sig.initialA() != sig.end())
      swapped.setInitialB(*sig.initialA());
   if (sig.initialB() != sig.end())
      swapped.setInitialA(*sig.initialB());
   swapped.insert(sig.beginFinal(), sig.endFinal());
   return swapped;
}

//------------------------------------------------------------------------------
/// Return the Signatures for WPlus2Jets which cannot be obtained by iterating QCD emissions,
/// due to the presence of regular Signatures like  u ubar - > W^+ d cbar.
SignatureSet SignatureManager::getSignaturespp2WPlus2Jets(const PdgID& IDdecay, int numFlavors, bool doDecay)
{
   SignatureSet signaturesWPlus2jets;
   const int threeCharge[13] = { -2, 1, -2, 1, -2, 1, 0, -1, 2, -1, 2, -1, 2};
   enum {offset = 6};
   for (int i = -numFlavors ; i <= numFlavors ; i++) {
      for (int j = -numFlavors ; j <= numFlavors ; j++) {
         bool accept = false;
         int threeChargeW =  3;
         PdgID lep1 = IDdecay.antiPartner();
         PdgID lep2 = PdgID(IDdecay.code() + 1);

         for (int k = -numFlavors; k <= numFlavors; k++) {
            for (int l = -numFlavors; l <= numFlavors; l++) {
               accept = (threeCharge[i + offset] + threeCharge[j + offset] - threeCharge[k + offset] - threeCharge[l + offset] == threeChargeW);
               if (accept) {
                  if (i* j* k* l != 0) {
                     // 4 quarks
                     if ( i + j != 0 &&  k + l == 0) {
                        // q qbar' -> W q'' qbar''
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     } else if ( i + j == 0 &&  k + l != 0) {
                        // q qbar -> W q' qbar''
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     } else if (i + j != 0 && j == l) {
                        // q q' -> W q'' q'
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     } else if (i + j != 0 && i == k) {
                        // q q' -> W q q''
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     }
                  } else {
                     // 2 quarks and 2 gluons
                     if (i* j != 0 && i + j != 0 && k == 0 && l == 0) {
                        // q q' -> W g g
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     } else if (k* l != 0 && k + l != 0 && i == 0 && j == 0) {
                        // g g -> W q q'
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     } else if (k* l == 0 && i* j == 0 ) {
                        // q g -> W q' g
                        Signature sig;
                        sig.setInitialA((i != 0) ? PdgID(i) : PdgID::kGluon);
                        sig.setInitialB((j != 0) ? PdgID(j) : PdgID::kGluon);
                        if ( doDecay ) {
                           sig.insertFinal(lep1);
                           sig.insertFinal(lep2);
                        } else {
                           sig.insertFinal(PdgID::kWPlus);
                        }
                        sig.insertFinal((k != 0) ? PdgID(k) : PdgID::kGluon);
                        sig.insertFinal((l != 0) ? PdgID(l) : PdgID::kGluon);
                        signaturesWPlus2jets.insert(sig);
                        accept = false;
                     }
                  }
               }
            }
         }
      }
   }
   return signaturesWPlus2jets;
}
} // namespace Geneva

