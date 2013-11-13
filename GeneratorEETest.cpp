//------------------------------------------------------------------------------
/// \file GeneratorEETest.cpp
//
// Author(s):
//    Alex Roberts
//
// Copyright:
//    Copyright (C) 2013 LBNL
//
//    This file is part of the Geneva MC framework. Geneva is distributed under
//    the terms of the GNU General Public License version 3 (GPLv3), see the
//    COPYING file that comes with this distribution for details.
//    Please respect the academic usage guidelines in the GUIDELINES file.
//
// Description:
//    Test code for the GeneratorEE class
//------------------------------------------------------------------------------

#include "GeneratorEE.h"
#include "CalcPSVolume.h"
#include "Configuration.h"
#include "SignatureManager.h"

#include "gtest/gtest.h"
#include <cmath>
#include <vector>

namespace Geneva
{
   std::vector<int> nums;

   SignatureSet createSignatures(const int maxJets, std::vector<int> nums)
   {
      SignatureSet masterSet;
      // five quark flavors
      int num;
      for (int i = 2; i <= maxJets; ++i) {
         num = masterSet.size();
         masterSet += SignatureManager().getSignatureseeJets(i, 5);
         nums.push_back( masterSet.size() - num );
      }
      return masterSet;
   }
            
   class GeneratorEETest : public testing::Test
   {
   protected:
      GeneratorEETest()
      : _Ecm(7000.), _gen(_Ecm), _maxJets(4) {
         ASSERT_TRUE(_gen.setSignatures(createSignatures(_maxJets,nums)));
      }
      double _Ecm;
      GeneratorEE _gen;
      double getValue(const Configuration& config, SignatureSet& sigSet);
      double _maxJets;

   };

   double GeneratorEETest::getValue(const Configuration& config, SignatureSet& sigSet)
   {
      int N = config.sizeFinal();
      // number of n-body signatures
      int nsig = sigSet.count_if(CheckSignatureSize(N + 2));
      
      const double S = _Ecm*_Ecm;
      
      // handle special N=1 case (no emission, boson not decayed)
      
      // kinematical phase space volume:
      double V_n = (pow(math_constants::pi(), 3 - 2 * N) * pow(2.0, 5 - 4 * N) * pow(S, N - 2)) / (factorial(N - 1) * factorial(N - 2));
     
      // return 1/(V_n*nsig) in pb, so the result is 1
      return (1.0) / (V_n * nsig * (_maxJets - 1.));
   }

   TEST_F(GeneratorEETest, QuickIntegralPhaseSpaceTest)
   {
      Configuration config;
      std::list<GeneratorEE> generators;
      generators.push_back(_gen);
            
      for (std::list <GeneratorEE>::iterator it = generators.begin(); it != generators.end(); ++it) {
         SignatureSet sigSet = it->getSignatures();
         double result = 0.0;
         double error = 0.0;
         const unsigned int nPoints = 1000000;
         int countFailures = 0;
         for (unsigned int i = 0; i < nPoints ; i++) {
            try {
               it->generate(config);
            } catch(std::exception& e) {
               Logger::globalLogger() << WARNING << e.what() << "Retrying ..." << std::endl;
               i--;
               countFailures++;
               ASSERT_LE((double)countFailures, double(nPoints) / 1000.);
               continue;
            }
            ASSERT_TRUE(config.sizeFinal() >= 1) << std::endl << config << "not in " << std::endl <<  it->getSignatures();
            double calcWeight = getValue(config, sigSet);
            double genWeight = it->getLastWeight();
            double weight = calcWeight / genWeight;
            result += weight;
            error += weight * weight;
         }
         result /= nPoints;
         error = std::sqrt((error / nPoints - result * result) / nPoints);
         ASSERT_NEAR(result, 1.0, 0.01) << "Result: " << result << " Error: " << error << std::endl <<  it->getSignatures() << std::endl;
         ASSERT_LT(error / result, 0.02) << "Result: " << result << " Error: " << error << std::endl <<  it->getSignatures() << std::endl;
         ASSERT_LT(fabs(result - 1.0) / error, 1.0) << "Result: " << result << " Error: " << error << std::endl <<  it->getSignatures() << std::endl;
      }
   }

} // namespace Geneva