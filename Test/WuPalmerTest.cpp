//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../WordNet.h"
#include "../Similarity/WuPalmer.h"

TEST_CASE("WuPalmerTest-testComputeSimilarity") {
    WordNet turkish = WordNet();
    WuPalmer wuPalmer = WuPalmer(turkish);
    REQUIRE_THAT(0.9697, Catch::Matchers::WithinAbs(wuPalmer.computeSimilarity(*turkish.getSynSetWithId("TUR10-0656390"), *turkish.getSynSetWithId("TUR10-0600460")), 0.0001));
    REQUIRE_THAT(0.25, Catch::Matchers::WithinAbs(wuPalmer.computeSimilarity(*turkish.getSynSetWithId("TUR10-0412120"), *turkish.getSynSetWithId("TUR10-0755370")), 0.0001));
    REQUIRE_THAT(0.3636, Catch::Matchers::WithinAbs(wuPalmer.computeSimilarity(*turkish.getSynSetWithId("TUR10-0195110"), *turkish.getSynSetWithId("TUR10-0822980")), 0.0001));
}