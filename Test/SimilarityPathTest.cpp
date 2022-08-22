//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#include "catch.hpp"
#include "../src/WordNet.h"
#include "../src/Similarity/SimilarityPath.h"

TEST_CASE("SimilarityPathTest-testComputeSimilarity") {
    WordNet turkish = WordNet();
    SimilarityPath similarityPath = SimilarityPath(turkish);
    REQUIRE_THAT(32.0, Catch::Matchers::WithinAbs(similarityPath.computeSimilarity(*turkish.getSynSetWithId("TUR10-0656390"), *turkish.getSynSetWithId("TUR10-0600460")), 0.0001));
    REQUIRE_THAT(13.0, Catch::Matchers::WithinAbs(similarityPath.computeSimilarity(*turkish.getSynSetWithId("TUR10-0412120"), *turkish.getSynSetWithId("TUR10-0755370")), 0.0001));
    REQUIRE_THAT(13.0, Catch::Matchers::WithinAbs(similarityPath.computeSimilarity(*turkish.getSynSetWithId("TUR10-0195110"), *turkish.getSynSetWithId("TUR10-0822980")), 0.0001));
}