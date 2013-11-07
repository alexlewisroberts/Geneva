//------------------------------------------------------------------------------
/// \file GeneratorEE.cpp
//
// Author(s):
//    Alex Roberts, Christian Bauer
//
// Copyright:
//    Copyright (C) 2012 LBNL
//
//    This file is part of the Geneva MC framework. Geneva is distributed under
//    the terms of the GNU General Public License version 3 (GPLv3), see the
//    COPYING file that comes with this distribution for details.
//    Please respect the academic usage guidelines in the GUIDELINES file.
//
// Description:
//    Implementation of class GeneratorEE
//------------------------------------------------------------------------------

#include "GeneratorEE.h"
#include "Configuration.h"
#include "MathUtils.h"
#include "Random.h"
#include "GeneratorUtils.h"
#include "Logger.h"
#include "FKSMapping.h"
#include "PhiRadFKS.h"
#include "PhiRadFKSGenerator.h"
#include "SignatureManager.h"

#include <list>
#include <cassert>


namespace Geneva
{

//------------------------------------------------------------------------------
// default constructor
GeneratorEE::GeneratorEE(double Ecm)
   : _isCalculated(false), _sigSet(), _Ecm(Ecm), _mapping(new FKSMapping)
   {
     //HACK: number of light flavors hardcoded for now
     _nf = 5;

// Define the grids

      _tIRRatio = 1./10000;

      /*double arrayggg[] = {0.11398900626641718,0.1095677693320703,0.06417457523407934,0.10956776933207829,0.11398900626641723,
         0.49592250079825745,0.4587591633963024,0.28001512302651393,0.4587591633963018,0.49592250079825706,
         1.376031608764623,1.1927367100674993,0.7868421647450613,1.192736710067502,1.376031608764623,2.247057538786013,
         1.8017898344525278,1.355937814692535,1.8017898344525298,2.2470575387860134,1.539511748861076,1.2777643344144622,
         1.1563999843498087,1.2777643344144625,1.5395117488610768};

      for(int i = 0; i < _nums*_numv; i++)
         _fsrgggGrid[i] = arrayggg[i];

      _fsrgggGridSum = 0;
      for(int i = 0; i<_nums*_numv; i++) {
         _fsrgggGridSum += _fsrgggGrid[i];
      }

      double arraygqq[] = {0.0024107707993906184,0.0017052874275781844,0.0014701263036407067,0.0017052874275781842,0.0024107707993906184,
         0.012978276335219257,0.009183429587187392,0.007918480671176769,0.009183429587187392,0.012978276335219257,
         0.04735876796986192,0.03358251519116556,0.028990430931600104,0.03358251519116556,0.047358767969861944,
         0.11304037627140401,0.08126040008829241,0.07066707469392187,0.08126040008829238,0.11304037627140401,
         0.1331144104333751,0.10535121697128429,0.09609681915058733,0.10535121697128429,0.13311441043337519};

      for(int i = 0; i < _nums*_numv; i++)
         _fsrgqqGrid[i] = arraygqq[i];

      _fsrgqqGridSum = 0;
      for(int i = 0; i<_nums*_numv; i++) {
         _fsrgqqGridSum += _fsrgqqGrid[i];
      }
*/
   }

//------------------------------------------------------------------------------
GeneratorEE::~GeneratorEE()
{
   delete _mapping;
//   delete _phiRadGenImp;
}

//------------------------------------------------------------------------------
// Returns the current set of Signatures used by the generator.
const SignatureSet& GeneratorEE::getSignatures() const
{
   return _sigSet;
}

//------------------------------------------------------------------------------
// Sets the Signatures for which to generate Configurations checking if they are allowed. 
bool GeneratorEE::setSignatures(const SignatureSet& sigSet)
{
   for (SignatureSet::iterator it=sigSet.begin(); it!=sigSet.end(); ++it)
      if(!addSignature(*it)) return false;
   setHistories();

   return true;
}

//------------------------------------------------------------------------------
// Adds a Signature to generate Configurations for.
bool GeneratorEE::addSignature(const Signature& sig)
{
   if (checkSignature(sig)) {
      _sigSet.insert(sig);
      return true;
   } else
      return false;
}

//------------------------------------------------------------------------------
// Checks if the generator can handle a Signature.
bool GeneratorEE::checkSignature(const Signature& sig) const
{
   return GeneratorUtils::isEe(sig);
}

//------------------------------------------------------------------------------
// This compiles a list of all signatures
void GeneratorEE::setHistories()
{
   size_t maxFinal = _sigSet.rbegin()->sizeFinal();
   Logger::globalLogger()<<DEBUG << "maxFinal= " << maxFinal << std::endl;
   for (size_t i = 2; i < maxFinal + 1; ++i)
      _allSigs.push_back(SignatureManager().getSignatureseeJets(i, _nf));

   // this generates all possible associations between n and n-1 body signatures
   for (std::list<SignatureSet>::iterator it = _allSigs.begin();it != --_allSigs.end();++it)  {
       RegionInfoList temp;
       std::list<SignatureSet>::iterator tti=it;
       ++tti;
       temp.setRegionInfoList(*it, *tti, _nf);
       _regionInfoLists.push_back(temp);
   }
}

//------------------------------------------------------------------------------
// Generates a new Configuration.
bool GeneratorEE::generate(Configuration& configuration)
{
//   std::cout << _sigSet << std::endl;
   if(_sigSet.size() == 0)
        return false;
   _lastConfig.clear();
   configuration.clear();

   SignatureSet::iterator signature = _sigSet.begin();
   int signatureNumber = int(_sigSet.size()*randomInterval());
   std::advance(signature, signatureNumber);

   generatePhi(*signature, configuration);
    
   _lastConfig = configuration;
   _isCalculated = false;
   return true;
}

//------------------------------------------------------------------------------
// Generates a new Configuration
bool GeneratorEE::generatePhi(const Signature& sig, Configuration& configuration)
{
   Configuration tempcon;
   std::list<RegionInfo> flalist;
   //Generates a flavor history
   getFlavorHistory(sig,flalist);
   //Now build up the configurations
   if (sig.sizeFinal() == 2)
       generatePhi2(sig, tempcon);
   else  {
       generatePhi2(*(flalist.front().fN), tempcon);
       Configuration configN;
       Configuration configNp1;
       configN = tempcon;
       double weight;
       FourVector internal;
       for (std::list<RegionInfo>::iterator hi = flalist.begin(); hi != flalist.end(); hi++) {
            weight = generatePhiNp1(*hi, configN, configNp1,internal);
            internal = _mapping->getPhiNplus1().FKSparton->p()+_mapping->getPhiNplus1().sister->p();

            _importanceJac *= weight;
            //reset the configuration for the next step
            configN = configNp1;
            configNp1.clear();
        }
        tempcon = configN;
    }
    
    configuration = tempcon;
    return true;
}

//------------------------------------------------------------------------------
// Randomly generate a flavor history for a given signature. Ordering is smallest signature first, largest last.
double GeneratorEE::getFlavorHistory(const Signature& sig, std::list<RegionInfo>& flalist)
{
   //Set decay rates, right now all set to one. Format decay"mother.id""sister.id""FKS.id".
   double decayggg = 1.0;
   double decayqqg = 1.0;
   double decaygqq = 1.0;
   flalist.clear();
   double prob = 1.0;
   Signature tempsig = sig;
   //The history is empty if we only have two final state particles
   if (sig.sizeFinal() > 2) {
      for (size_t um = 0; um != sig.sizeFinal()-2; ++um) {
         std::list<RegionInfoList>::iterator iit = _regionInfoLists.begin();
         //Jump to correct RegionInfoList for N body signatures
         std::advance(iit, tempsig.sizeFinal()-3);
         std::list<RegionInfo> tmplist = iit->getSingularRegionsToSignature(tempsig);
         //Pick an element from this list.
         double sumwgt = 0.0;
         double decay = 1.0;
         std::vector<double> probs;
         for (std::list<RegionInfo>::iterator it = tmplist.begin(); it != tmplist.end(); ++it) {
            if (it->k->isQuark())
               decay = decayqqg;
            else if (it->i->isQuark())
               decay = decaygqq;
            else
               decay = decayggg;
            sumwgt += decay * it->multRad;
            probs.push_back(decay * it->multRad);
         }
         assert(probs.size() == tmplist.size());
         //compare the normalized weight comp to a random integer to select branching
         double comp = 0.0;
         double rang = randomInterval();
         std::list<RegionInfo>::iterator id = tmplist.begin();
         for (std::vector<double>::iterator it = probs.begin(); it != probs.end(); ++it) {
            comp += *it / sumwgt;
            if (rang <= comp) {
               std::advance(id, distance(probs.begin(),it));
               prob *= *it / sumwgt;
               break;
            }
         }
         flalist.push_back(*id);
         tempsig = *(id->fN);
      }
   }
   flalist.reverse(); //want the smallest signature to be at the beginning
   return prob; //return the probability of the path chosen
}

//------------------------------------------------------------------------------
// Generates a 2-body Configuration.
/**
 * The generates the phi2 from a flat distribution and costheta according to 1+cos^2
 */
double GeneratorEE::generatePhi2(const Signature& sig2, Configuration& configuration) {

   //First, add the initial particles
   configuration.setInitialA(Particle(*sig2.initialA(), _Ecm/2, 0, 0,  _Ecm/2, 0, 0)); //The last two entries are color information
   configuration.setInitialB(Particle(*sig2.initialB(), _Ecm/2, 0, 0, -_Ecm/2, 0, 0)); //The last two entries are color information

   //Now, determine the quark and anti-quark momenta
   _importanceJac = 1.;
   double ran1 = randomInterval();
   double ran2 = randomInterval();
   double tmp = pow(2.-4.*ran1+sqrt(5.-16.*ran1+16.*ran1*ran1),1./3.);
   double costh = 1./tmp - tmp;
   _importanceJac *= 4.*(1+tmp*tmp)/3./sqrt(5.-16.*ran1+16.*ran1*ran1)/tmp;
   double phi = 2.*math_constants::pi()*ran2;
   _importanceJac *= 2.*math_constants::pi();
   double sinth = sqrt(1.-costh*costh);
   FourVector pnew1(_Ecm/2.,_Ecm/2.*sinth*cos(phi),_Ecm/2.*sinth*sin(phi),_Ecm/2.*costh);
   FourVector pnew2(_Ecm/2.,-_Ecm/2.*sinth*cos(phi),-_Ecm/2.*sinth*sin(phi),-_Ecm/2.*costh);

   Signature::iterator sig = sig2.beginFinal();
   configuration.insertFinal(Particle(*sig, pnew1.p0(), pnew1.p1(), pnew1.p2(), pnew1.p3(), 0, 0));
   configuration.insertFinal(Particle(*(++sig), pnew2.p0(), pnew2.p1(), pnew2.p2(), pnew2.p3(), 0, 0));

   return 1.0;
}

//------------------------------------------------------------------------------
// This is the recursive procedure for generating N+1 body phase space from N body phase space
double GeneratorEE::generatePhiNp1(const RegionInfo& info, const Configuration& configN, Configuration& configNp1, FourVector internal) {

   //check that incoming RegionInfo has same signature as incoming configuration
   assert(configN.operator==(*info.fN));

   PhiNFKS phiN;
   phiN.config = configN;

   //choose a random emitter with the PDG ID of Info.k
   int emNumber = int(configN.countFinal(*(info.k))*randomInterval());
   Configuration::iterator san = phiN.config.findFinal(*(info.k));
   std::advance(san,emNumber);
   phiN.emitter = san;
   //sanity check
   assert(phiN.emitter->id() == *(info.k));

   //Create a PhiRad with the correct flavor structure
   PhiRadFKS phiRad;
   double genWeight = 0.;
   if (phiN.emitter->isFinal()) {
      if(configN.sizeFinal()==2)
         genWeight = generatePhiRadFSRGrid(phiN, *(info.i), *(info.j), phiRad);
      else
         genWeight = generatePhiRadFSRGrid(phiN, *(info.i), *(info.j), phiRad);
   } else if (phiN.emitter->isInitialA() || phiN.emitter->isInitialB())  {
      genWeight = generatePhiRadISR(phiN, *(info.i), *(info.j), phiRad);
   } else {
      Logger::globalLogger() << ERROR << "Invalid emitter" << std::endl;
      exit(0);
   }

   //Rescale the xi integral to the correct range. Include a jacobian factor
   //phiRad.xi()*=_mapping->getXiMaxReal(phiN,1,1,phiRad.y());
   //_importanceJac*=_mapping->getXiMaxReal(phiN,1,1,phiRad.y());

   //Create the phiNp1 from phiN and phirad
   _mapping->generateSplit(phiN, phiRad,_Ecm*_Ecm,1,1);
   configNp1 = _mapping->getPhiNplus1().config;
//   _importanceJac *= _mapping->getJacobian() / _phiRadGenImp->getLastWeight();
   _importanceJac *= _mapping->getJacobian() / genWeight;

   //we need to use S_ij factors, right now only for three jets
   double alphasplit = 1.0;
   if(configNp1.sizeFinal()==3)     {
      alphasplit = 1/(_mapping->getPhiNplus1().FKSparton->p()*_mapping->getPhiNplus1().sister->p());
      PdgID sis_id = _mapping->getPhiNplus1().sister->id();
      double alphatot = 0;
      alphatot += alphasplit;
      Configuration::iterator mtt = configNp1.findFinal(sis_id.antiPartner());
      alphatot += 1/(_mapping->getPhiNplus1().FKSparton->p()*mtt->p());
      alphasplit *=2.0/alphatot;
   }
   /*if(configNp1.sizeFinal()==4 && (info.i)->isQuark())   {
      alphasplit = 1/(_mapping->getPhiNplus1().FKSparton->p()+_mapping->getPhiNplus1().sister->p()).square()/internal.square();
      double alphatot =0;
      std::vector<FourVector> tempq;
      std::vector<FourVector> tempaq;
      FourVector temp2;
      FourVector temp3;
      for(Configuration::iterator mtt = configNp1.begin(); mtt != configNp1.end(); mtt++) {
         for(Configuration::iterator nt = configNp1.begin(); nt != configNp1.end(); nt++) {
            if(*nt != *mtt) {
               if(nt->id().isParticle())
                  tempq.push_back(nt->p());
               else if(!nt->id().isParticle())
                  tempaq.push_back(nt->p());
               temp3 += nt->p();
            }
            std::cout << "temp3 = " << temp3 << std::endl;
         }
         if (tempq.size() ==2) {
            std::vector<FourVector>::iterator tt = tempq.begin();
            advance(tt, int(randomInterval()*2.));
            temp2 = *tt+*(tempaq.begin());
            alphatot += temp2.square()*temp3.square();
         }
         else {
            std::vector<FourVector>::iterator tt = tempaq.begin();
            advance(tt, int(randomInterval()*2.));
            temp2 = *tt + *(tempq.begin());
            alphatot += 1/temp2.square()*1/temp3.square();
         }
      }
      alphasplit *= 4.0*alphatot;
   }
   */
   return alphasplit;
}

//------------------------------------------------------------------------------
// Generates the PhiRadFKS for final state radiation using a grid
// Have to input the N-body phase space used previously along with the emitter stored in phiN.emitter->id() as well as the ID of the left and right parton to be generated from the splitting
// Outputs a new
double GeneratorEE::generatePhiRadFSRGrid(const PhiNFKS& phiN, PdgID idI, PdgID idJ, PhiRadFKS& phiRad) {

   double jac=1.; //This will hold the value of the jacobian that will be returned
   //Make sure that the flavor of the emitter in phiN is the same as idEmitter

   //Assign the value of the particle IDs
   phiRad.idMother() = phiN.emitter->id();
   phiRad.idLeft() = idJ;
   phiRad.idRight() = idI;
   phiRad.radType() = PhiRadFKS::kFSR;

   //const Configuration& config = phiN.config;
   Configuration::iterator emitter = phiN.emitter;
   PdgID idK = emitter->id();
   FourVector q = phiN.config.initialA()->p() + phiN.config.initialB()->p();
   double Q = sqrt(q.square());
   double ENb = emitter->energy();
   double ximax = 1. - (q - emitter->p()).square() / q.square();

   double t = 0;
   double z, zmin, zmax = 0;
   double prob = 0;
   double gridsum = 0;
   double grid[_nums*_numv] = {0};
   get2Dgrid(ENb, phiRad.idMother(), idI, idJ, gridsum, grid);
   if(randomInterval() <  1.-gridsum/_numv/_nums) { // t < tIR
      double rand1=randomInterval();
      double rand2=randomInterval();
      double tmax = ENb*ENb/2.;
      double tmin = tmax*_tIRRatio;
      t = tmin*rand1;
      zmin = 0.5-0.5*sqrt(1-t/tmax); //Calculate the zmin and zmax for that t
      zmax = 0.5+0.5*sqrt(1-t/tmax);
      z = zmin + (zmax-zmin)*rand2;
      prob = 1.-gridsum/_nums/_numv;
      prob /= tmin;
      prob /= (zmax - zmin);
      jac /= prob;
   }
   else { // t > tIR
      //Determine the values of s and v
      double s, v;
      prob = getSV(s,v, ENb, phiRad.idMother(), idI, idJ,gridsum,grid);
      //Now convert this to values in t and z
      prob *= convertSVtoTZ(t, z, s, v, ENb, phiRad.idMother(), idI, idJ);
      jac /= prob;
   }
   //Now convert the t and z values to xi and y
   phiRad.xi() = ximax*(1-z);
   phiRad.y() = 1. - 4.*t / (Q*Q*ximax*ximax*z*(1-z));
   jac *= 4. / (Q*Q*ximax*z*(1-z));

   //Generate the phi value
   phiRad.phi() = randomAngle();
   jac *= 2.*math_constants::pi();

   return  64.*math_constants::pi3() / jac;

}

//------------------------------------------------------------------------------
// Generates the PhiRadFKS for final state radiation
double GeneratorEE::generatePhiRadFSR(const PhiNFKS& phiN, PdgID idI, PdgID idJ, PhiRadFKS& phiRad) {

   double jac=1.; //This will hold the value of the jacobian that will be returned
   //Make sure that the flavor of the emitter in phiN is the same as idEmitter
   phiRad.idMother() = phiN.emitter->id();
   phiRad.idLeft() = idJ;
   phiRad.idRight() = idI;
   phiRad.radType() = PhiRadFKS::kFSR;

   const Configuration& config = phiN.config;
   Configuration::iterator emitter = phiN.emitter;
   PdgID idK = emitter->id();
   FourVector q = config.initialA()->p() + config.initialB()->p();
   double Q = sqrt(q.square());
   //double ENb = emitter->energy();
   double ximax = 1. - (q - emitter->p()).square() / q.square();
   
   //Set the value of tmax and tIR. Note that I will always use the maximally allowed value of tmax, and then rescale at the end
   double tmax = _Ecm*_Ecm/8.;
   double tIR = tmax*_tIRRatio;
   
   
   double zIRmin = 0.5-0.5*sqrt(1-tIR/tmax);
   double zIRmax = 0.5+0.5*sqrt(1-tIR/tmax);

   //Determine the value of I_{k->ij}
   double I=getIkij(idK,idI,idJ,zIRmin,zIRmax);

   //Now start the veto algorithm

   //Set t to tmax
   double t = tmax;
   double z,zmin,zmax;
   int i = 0;
   while(true) {
      i++;
      t = t*pow(randomInterval(),1/I); //Generate a value of t
      if(t <= tIR) { //If t<tIR, use flat sampling
         t = tIR*randomInterval();
         zmin = 0.5-0.5*sqrt(1-t/tmax); //Calculate the zmin and zmax for that t
         zmax = 0.5+0.5*sqrt(1-t/tmax);
         jac*=tIR;
         z = zmin + (zmax-zmin)*randomInterval();
         jac *= (zmax - zmin);
         jac /= getSudakov(idK, idI, idJ, tIR);
         break;
      } else { //If t>tIR, use f(t,z) Delta(t)
         zmin = 0.5-0.5*sqrt(1-t/tmax); //Calculate the zmin and zmax for that t
         zmax = 0.5+0.5*sqrt(1-t/tmax);
         z = getZ(idK,idI,idJ,zIRmin,zIRmax);
         double foverg = getFoverG(idK,idI,idJ,z);
         if(foverg > randomInterval() && zmin< z && z < zmax) {
            jac /= getSplittingProb(idK, idI, idJ, t, z);
            break;
         }
      }
   }
   //Now convert the t and z values to xi and y
   phiRad.xi() = ximax*(1-z);
   phiRad.y() = 1. - 4*t / (Q*Q*ximax*ximax*z*(1-z));
   jac *= 4 / (Q*Q*ximax*z*(1-z));

   //Generate the phi value
   phiRad.phi() = randomAngle();
   jac *= 2.*math_constants::pi();

   return  64.*math_constants::pi3() / jac;

}

double GeneratorEE::getSV(double& s, double& v, double ENb, PdgID idK, PdgID idI, PdgID idJ, const double gridsum, const double *grid) {

      double rand1 = gridsum*randomInterval();
      int gridPos = 0;
      double gridRunningSum = grid[gridPos];
      while(gridRunningSum < rand1) {
         gridPos++;
         gridRunningSum += grid[gridPos];
      }
      //Now that I have the grid tile, determine the value of s and v
      double rand2 = randomInterval();
      double rand3 = randomInterval();

      int gridPosS = gridPos / _numv;
      int gridPosV = gridPos % _numv;
      s = (gridPosS+rand2)/_nums;
      v = (gridPosV+rand3)/_numv;
      return grid[gridPos];

}

   void GeneratorEE::get2Dgrid(double ENb, PdgID idK, PdgID idI, PdgID idJ, double& gridsum, double *grid) {
   if(idK.isQuark()) { // q -> qg splitting
      int i = 0;
      while(true) {
         if(arrayqqg[i][0] >= ENb) {
            for(int j = 0; j < _nums*_numv; j++) {
               gridsum += arrayqqg[i][j+1];
               grid[j] = arrayqqg[i][j+1];
            }
            break;
         }
         i++;
      }
   }
   else if(idK.isGluon()) {
      if(idJ.isGluon()) {// g -> gg splitting
         int i = 0;
         while(true) {
            if(arrayggg[i][0] >= ENb) {
               for(int j = 0; j < _nums*_numv; j++) {
                  gridsum += arrayggg[i][j+1];
                  grid[j] = arrayggg[i][j+1];
               }
               break;
            }
            i++;
         }
      }
      else if(idJ.isQuark()) { // g -> qq splitting
         int i = 0;
         while(true) {
            if(arraygqq[i][0] >= ENb) {
               for(int j = 0; j < _nums*_numv; j++) {
                  gridsum += arraygqq[i][j+1];
                  grid[j] = arraygqq[i][j+1];
               }
               break;
            }
            i++;
         }
      }
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }
   }
   else {
      Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
      exit(0);
   }
}

double GeneratorEE::convertSVtoTZ(double& t, double& z, double s, double v, double ENb, PdgID idK, PdgID idI, PdgID idJ) {
      double tmax = ENb*ENb/2.;
      double tmin = tmax*_tIRRatio;
      t = tmin * pow(tmax/tmin,s);
      double jac = 1./t/log(tmax/tmin);
      double zmin = 0.5-0.5*sqrt(1-t/tmax);
      double zmax = 0.5+0.5*sqrt(1-t/tmax);
      if(idK.isQuark()) { // q -> qg splitting
         z = 1.-(1.-zmin)*pow((1.-zmax)/(1.-zmin),v);
         jac /= (1.-z)*log((1.-zmin)/(1.-zmax));
         return jac;

      }
      else if(idK.isGluon()) {
         if(idJ.isGluon()) {// g -> gg splitting
            double temp = pow((1.-zmax)*zmin/(1.-zmin)/zmax,v);
            temp *= (1.-zmin)/zmin;
            temp += 1.;
            z = 1./temp;
            jac /= z*(1-z)*log(zmax*(1.-zmin)/zmin/(1.-zmax));
            return jac;
         }
         else if(idJ.isQuark()) {// g -> qq splitting
            z=zmin+v*(zmax-zmin);
            jac /= zmax-zmin;
            return jac;
         }
         else {
            Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
            exit(0);
         }
      }
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }

}

// Determine the I_{k->ij} function (the z-integral over the g_{k->ij} function
double GeneratorEE::getIkij(PdgID idK, PdgID idI, PdgID idJ, double zIRmin,double zIRmax) {
   if(idK.isQuark()) { // q -> qg splitting
      return 0.118/math_constants::pi()*SU<3>::CF*log((1.-zIRmin)/(1.-zIRmax));
   }
   else if(idK.isGluon()) {
      if(idJ.isGluon()) // g -> gg splitting
         return 0.118/math_constants::pi()*SU<3>::CA*log((1.-zIRmin)/(1.-zIRmax));
      else if(idJ.isQuark()) // g -> qq splitting
         //return 0.118/2./math_constants::pi()*SU<3>::TF/4.*(1.+2*zIRmax*zIRmax+2*zIRmin*zIRmin-4.*zIRmin);
         return 0.118/2/math_constants::pi()*SU<3>::TF*(zIRmax - zIRmin);
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }
   }
   else {
      Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
      exit(0);
   }

}

// Determine the z value based on the g_{k->ij} function
double GeneratorEE::getZ(PdgID idK, PdgID idI, PdgID idJ, double zIRmin,double zIRmax) {
   if(idK.isQuark()) { // q -> qg splitting
      return 1 - (1.-zIRmin)*pow((1.-zIRmax)/(1.-zIRmin),randomInterval());
   }
   else if(idK.isGluon()) {
      if(idJ.isGluon()) // g -> gg splitting
         return 1./(1.+(1.-zIRmin)/zIRmin*pow(zIRmin*(1.-zIRmax)/zIRmax/(1.-zIRmin), randomInterval()));
      else if(idJ.isQuark()) {// g -> qq splitting
         //double norm = 1/4.*(1.+2*zIRmax*zIRmax-4*zIRmin+2*zIRmin*zIRmin);
         //double rand = randomInterval();
         //if(rand < 1/4.*(1.+2./4.-4*zIRmin+2*zIRmin*zIRmin)/norm)
         //   return 0.5*(2.-sqrt(2)*sqrt(2-rand-rand*zIRmax*zIRmax-4*zIRmin+4*rand*zIRmin+2*zIRmin*zIRmin-2*rand*zIRmin*zIRmin));
         //else
         //   return 1/sqrt(2)*sqrt(-1+rand+2*rand*zIRmax*zIRmax+4*zIRmin-4*rand*zIRmin-2*zIRmin*zIRmin+2*rand*zIRmin*zIRmin);
         return zIRmin + randomInterval()*(zIRmax-zIRmin);
      }
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }
   }
   else {
      Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
      exit(0);
   }
   
}

// Determine the ratio of f_{k->ij}/g_{k->ij}
double GeneratorEE::getFoverG(PdgID idK, PdgID idI, PdgID idJ, double z) {
   if(idK.isQuark()) { // q -> qg splitting
      return (1+z*z)/2;
   }
   else if(idK.isGluon()) {
      if(idJ.isGluon()) // g -> gg splitting
         return ((1-z)/z + z/(1-z) + z*(1-z))*z*(1-z);
      else if(idJ.isQuark()) // g -> qq splitting
      //   return (z*z+(1-z)*(1-z))/(0.5*(1+abs(2*z-1)));
         return z*z+(1-z)*(1-z);
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }
   }
   else {
      Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
      exit(0);
   }

}

// Determine just the Sudakov factor alone
double GeneratorEE::getSudakov(PdgID idK, PdgID idI, PdgID idJ, double t) {
   double tmax = _Ecm*_Ecm/8.;
   double that = t/tmax;
   if(idK.isQuark()) { // q -> qg splitting
      double lndelta = 2.*math_constants::pi2()/3.-6.*sqrt(1.-that)-4.*log((1.-sqrt(1.-that))/2.)*log((1.-sqrt(1.-that))/2.);
      lndelta += 3.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
      lndelta += 2.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)))*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
      lndelta -= 8.*dilog((1.-sqrt(1.-that))/2.);
      lndelta *= 0.118*SU<3>::CF/4./math_constants::pi();
      lndelta = exp(lndelta);
      return lndelta;
   }
   else if(idK.isGluon()) {
      if(idJ.isGluon()) {// g -> gg splitting
         double that = t/tmax;
         double lndelta = 2.*math_constants::pi2()/3.+67./9.*sqrt(1.-that)-1./9.*that*sqrt(1.-that)-4.*log((1.-sqrt(1.-that))/2.)*log((1.-sqrt(1.-that))/2.);
         lndelta += 11./3.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
         lndelta += 2.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)))*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
         lndelta -= 8.*dilog((1.-sqrt(1.-that))/2.);
         lndelta *= 0.118*SU<3>::CA/4./math_constants::pi();
         lndelta = exp(lndelta);
         return lndelta;
      }
      else if(idJ.isQuark()) { // g -> qq splitting
         double lndelta = _nf/9.*((1.-that)*sqrt(1.-that)-6.*(-2.*sqrt(1-that)+2.*log(1+sqrt(1-that))-log(that)));
         lndelta *= 0.118*SU<3>::TF/2./math_constants::pi();
         lndelta = exp(lndelta);
         return lndelta;
      }
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }
   }
   else {
      Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
      exit(0);
   }
}

// Determine the z value based on the g_{k->ij} function
double GeneratorEE::getSplittingProb(PdgID idK, PdgID idI, PdgID idJ, double t, double z) {
   double tmax = _Ecm*_Ecm/8.;
   double that = t/tmax;
   if(idK.isQuark()) { // q -> qg splitting
      double p = 0.118/2./math_constants::pi()*SU<3>::CF*(1.+z*z)/(1.-z);
      p *= 1./t;
      double lndelta = 2.*math_constants::pi2()/3.-6.*sqrt(1.-that)-4.*log((1.-sqrt(1.-that))/2.)*log((1.-sqrt(1.-that))/2.);
      lndelta += 3.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
      lndelta += 2.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)))*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
      lndelta -= 8.*dilog((1.-sqrt(1.-that))/2.);
      lndelta *= 0.118*SU<3>::CF/4./math_constants::pi();
      p *= exp(lndelta);
      return p;
   }
   else if(idK.isGluon()) {
      if(idJ.isGluon()) {// g -> gg splitting
         double p = 0.118/2./math_constants::pi()*SU<3>::CA;
         p *= z/(1.-z) + (1.-z)/z + z*(1.-z);
         p *= 1./t;
         double lndelta = 2.*math_constants::pi2()/3.+67./9.*sqrt(1.-that)-1./9.*that*sqrt(1.-that)-4.*log((1.-sqrt(1.-that))/2.)*log((1.-sqrt(1.-that))/2.);
         lndelta += 11./3.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
         lndelta += 2.*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)))*log((1.+sqrt(1.-that))/(1.-sqrt(1.-that)));
         lndelta -= 8.*dilog((1.-sqrt(1.-that))/2.);
         lndelta *= 0.118*SU<3>::CA/4./math_constants::pi();
         p *= exp(lndelta);
         return p;
      }
      else if(idJ.isQuark()) { // g -> qq splitting
         double p = 0.118/2./math_constants::pi()*SU<3>::TF;
         p *= z*z+(1.-z)*(1.-z);
         p *= 1./t;
         double lndelta = _nf/9.*((1.-that)*sqrt(1.-that)-6.*(-2.*sqrt(1-that)+2.*log(1+sqrt(1-that))-log(that)));
         lndelta *= 0.118*SU<3>::TF/2./math_constants::pi();
         p *= exp(lndelta);
         return p;
      }
      else {
         Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
         exit(0);
      }
   }
   else {
      Logger::globalLogger() << ERROR << "Can only have quarks or gluons" << std::endl;
      exit(0);
   }
   
}

   //------------------------------------------------------------------------------
   // Generates the PhiRadFKS for initial state radiation
   double GeneratorEE::generatePhiRadISR(const PhiNFKS& phiN, PdgID idI, PdgID idJ, PhiRadFKS& phiRad) {
      
//      double jac=1.; //This will hold the value of the jacobian that will be returned
//      //Make sure that the flavor of the emitter in phiN is the same as idEmitter
//      phiRad.idMother() = phiN.emitter->id();
//      phiRad.idLeft() = idJ;
//      phiRad.idRight() = idI;
//      phiRad.radType() = PhiRadFKS::kFSR;
//      
//      const Configuration& config = phiN.config;
//      Configuration::iterator emitter = phiN.emitter;
//      PdgID idK = emitter->id();
//      FourVector q = config.initialA()->p() + config.initialB()->p();
//      double Q = sqrt(q.square());
//      double ENb = emitter->energy();
//      double ximax = 1. - (q - emitter->p()).square() / q.square();
//      _tmax = ENb*ENb/2.;
//      
//      //Set the value of tIR and the limits zmin/max(tIR)
//      double tIR = 1.;
//      if(tIR > _tmax)
//         tIR = _tmax;
//      double zIRmin = 0.5-0.5*sqrt(1-tIR/_tmax);
//      double zIRmax = 0.5+0.5*sqrt(1-tIR/_tmax);
//      
//      //Determine the value of I_{k->ij}
//      double I=getIkij(idK,idI,idJ,zIRmin,zIRmax);
//      
//      //Now start the veto algorithm
//      
//      //Set t to tmax
//      double t = _tmax;
//      double z,zmin,zmax;
//      int i = 0;
//      while(true) {
//         i++;
//         t = t*pow(randomInterval(),1/I); //Generate a value of t
//         if(t <= tIR) { //If t<tIR, use flat sampling
//            t = tIR*randomInterval();
//            zmin = 0.5-0.5*sqrt(1-t/_tmax); //Calculate the zmin and zmax for that t
//            zmax = 0.5+0.5*sqrt(1-t/_tmax);
//            jac*=tIR;
//            z = zmin + (zmax-zmin)*randomInterval();
//            jac *= (zmax - zmin);
//            jac /= exp(-0.118*4./3./2./math_constants::pi()*log(tIR/_tmax)*log(tIR/_tmax));
//            break;
//         } else { //If t>tIR, use f(t,z) Delta(t)
//            zmin = 0.5-0.5*sqrt(1-t/_tmax); //Calculate the zmin and zmax for that t
//            zmax = 0.5+0.5*sqrt(1-t/_tmax);
//            z = getZ(idK,idI,idJ,zIRmin,zIRmax);
//            double foverg = getFoverG(idK,idI,idJ,z);
//            if(foverg > randomInterval() && zmin< z && z < zmax) {
//               jac /= getSplittingProb(idK, idI, idJ, t, z);
//               break;
//            }
//         }
//      }
//      //Now convert the t and z values to xi and y
//      phiRad.xi() = ximax*(1-z);
//      phiRad.y() = 1. - 4*t / (Q*Q*ximax*ximax*z*(1-z));
//      jac *= 4 / (Q*Q*ximax*z*(1-z));
//      
//      //Generate the phi value
//      phiRad.phi() = randomAngle();
//      jac *= 2.*math_constants::pi();
//      
//      return  64.*math_constants::pi3() / jac;
      return 0.;
   }
   
//------------------------------------------------------------------------------
// Returns the weight of the last generated configuration.
double GeneratorEE::getLastWeight()
{
   if (_isCalculated)
      return _lastWeight;
   else {
      _lastWeight = getWeight(_lastConfig);
      _isCalculated = true;
      return _lastWeight;
   }
}

//------------------------------------------------------------------------------
// Returns the generation weight for the given configuration.
//NOTE: The following is correct only because only calls 
// to getWeight(_lastConfig) appear in the MultiChannelGenerator code. 
// TODO: Restore this functions to its intended behaviour, if possible
double GeneratorEE::getWeight(const Configuration& config)
{
    if (_sigSet.find(Signature(config)) == _sigSet.end()) {
        return 0.0;
    }
   return 32.*math_constants::pi2() / _importanceJac / _sigSet.size();
}

//------------------------------------------------------------------------------
// Returns the name "GeneratorEE" of the Generator.
const std::string GeneratorEE::name() const
{
   return "GeneratorEE";
}

} // namespace Geneva
