
#include "nnif1.h"

#include <math.h>

#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/lagged_fibonacci.hpp>





float nnif1(const float& X, const nnif_weights& InterconnectData) {

    float denom = InterconnectData.Scale + fabs(X + InterconnectData.HOfsD);

    if (denom == 0.0) {
        return 0.0;
    }

    return ((((X * InterconnectData.NumCoeff) + InterconnectData.HOfsN) / denom) * InterconnectData.XScale) + InterconnectData.VOfs;

}





void nnif1_genesis(nnif_weights* InterconnectBase, const int Count) {

    boost::lagged_fibonacci4423 GenesisRngCore;
    boost::uniform_real<float>  GenesisDistribution(-10.0f, 10.0f);

    boost::variate_generator<
        boost::lagged_fibonacci4423&,
        boost::uniform_real<float>
    > RNG(GenesisRngCore, GenesisDistribution);

    for (int i=Count; i>0; --i) {

        InterconnectBase->XScale   = RNG();
        InterconnectBase->NumCoeff = RNG();
        InterconnectBase->HOfsN    = RNG();
        InterconnectBase->HOfsD    = RNG();
        InterconnectBase->VOfs     = RNG();
        InterconnectBase->Scale    = RNG();

        ++InterconnectBase;

    }

}
