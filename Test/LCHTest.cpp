//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../WordNet.h"
#include "../Similarity/LCH.h"

TEST_CASE("LCHTest-testComputeSimilarity") {
    WordNet turkish = WordNet();
    LCH lch = LCH(turkish);
    REQUIRE_THAT(2.8332, Catch::Matchers::WithinAbs(lch.computeSimilarity(*turkish.getSynSetWithId("TUR10-0656390"), *turkish.getSynSetWithId("TUR10-0600460")), 0.0001));
    REQUIRE_THAT(0.7673, Catch::Matchers::WithinAbs(lch.computeSimilarity(*turkish.getSynSetWithId("TUR10-0412120"), *turkish.getSynSetWithId("TUR10-0755370")), 0.0001));
    REQUIRE_THAT(0.6241, Catch::Matchers::WithinAbs(lch.computeSimilarity(*turkish.getSynSetWithId("TUR10-0195110"), *turkish.getSynSetWithId("TUR10-0822980")), 0.0001));
}