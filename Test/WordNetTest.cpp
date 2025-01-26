//
// Created by Olcay Taner YILDIZ on 7.01.2021.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "../src/WordNet.h"
#include "CounterHashMap.h"

TEST_CASE("WordNetTest"){
    static WordNet turkish = WordNet();

    SECTION("WordNetTest-testSynSetList") {
        int literalCount = 0;
        for (const SynSet& synSet : turkish.getSynSetList()){
            literalCount += synSet.getSynonym().literalSize();
        }
        REQUIRE(110259 == literalCount);
    }

    SECTION("WordNetTest-testLiteralList") {
        REQUIRE(82276 == turkish.getLiteralList().size());
    }

    SECTION("WordNetTest-testGetSynSetWithId") {
        REQUIRE_FALSE(turkish.getSynSetWithId("TUR10-0000040") == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithId("TUR10-0648550") == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithId("TUR10-1034170") == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithId("TUR10-1047180") == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithId("TUR10-1196250") == nullptr);
    }

    SECTION("WordNetTest-testGetSynSetWithLiteral") {
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("sıradaki", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("Türkçesi", 2) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("tropikal orman", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("mesut olmak", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("acı badem kurabiyesi", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("açık kapı siyaseti", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("bir baştan bir başa", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("eş zamanlı dil bilimi", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("bir iğne bir iplik olmak", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("yedi kat yerin dibine geçmek", 2) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("kedi gibi dört ayak üzerine düşmek", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("bir kulağından girip öbür kulağından çıkmak", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("anasından emdiği süt burnundan fitil fitil gelmek", 1) == nullptr);
        REQUIRE_FALSE(turkish.getSynSetWithLiteral("bir ayak üstünde kırk yalanın belini bükmek", 1) == nullptr);
    }

    SECTION("WordNetTest-testNumberOfSynSetsWithLiteral") {
        REQUIRE(1 == turkish.numberOfSynSetsWithLiteral("yolcu etmek"));
        REQUIRE(2 == turkish.numberOfSynSetsWithLiteral("açık pembe"));
        REQUIRE(3 == turkish.numberOfSynSetsWithLiteral("bürokrasi"));
        REQUIRE(4 == turkish.numberOfSynSetsWithLiteral("bordür"));
        REQUIRE(5 == turkish.numberOfSynSetsWithLiteral("duygulanım"));
        REQUIRE(6 == turkish.numberOfSynSetsWithLiteral("sarsıntı"));
        REQUIRE(7 == turkish.numberOfSynSetsWithLiteral("kuvvetli"));
        REQUIRE(8 == turkish.numberOfSynSetsWithLiteral("merkez"));
        REQUIRE(9 == turkish.numberOfSynSetsWithLiteral("yüksek"));
        REQUIRE(10 == turkish.numberOfSynSetsWithLiteral("biçim"));
        REQUIRE(11 == turkish.numberOfSynSetsWithLiteral("yurt"));
        REQUIRE(12 == turkish.numberOfSynSetsWithLiteral("iğne"));
        REQUIRE(13 == turkish.numberOfSynSetsWithLiteral("kol"));
        REQUIRE(14 == turkish.numberOfSynSetsWithLiteral("alem"));
        REQUIRE(15 == turkish.numberOfSynSetsWithLiteral("taban"));
        REQUIRE(16 == turkish.numberOfSynSetsWithLiteral("yer"));
        REQUIRE(17 == turkish.numberOfSynSetsWithLiteral("ağır"));
        REQUIRE(18 == turkish.numberOfSynSetsWithLiteral("iş"));
        REQUIRE(19 == turkish.numberOfSynSetsWithLiteral("dökmek"));
        REQUIRE(20 == turkish.numberOfSynSetsWithLiteral("kaldırmak"));
        REQUIRE(21 == turkish.numberOfSynSetsWithLiteral("girmek"));
        REQUIRE(22 == turkish.numberOfSynSetsWithLiteral("gitmek"));
        REQUIRE(23 == turkish.numberOfSynSetsWithLiteral("vermek"));
        REQUIRE(24 == turkish.numberOfSynSetsWithLiteral("olmak"));
        REQUIRE(25 == turkish.numberOfSynSetsWithLiteral("bırakmak"));
        REQUIRE(26 == turkish.numberOfSynSetsWithLiteral("çıkarmak"));
        REQUIRE(27 == turkish.numberOfSynSetsWithLiteral("kesmek"));
        REQUIRE(28 == turkish.numberOfSynSetsWithLiteral("açmak"));
        REQUIRE(33 == turkish.numberOfSynSetsWithLiteral("düşmek"));
        REQUIRE(38 == turkish.numberOfSynSetsWithLiteral("atmak"));
        REQUIRE(39 == turkish.numberOfSynSetsWithLiteral("geçmek"));
        REQUIRE(44 == turkish.numberOfSynSetsWithLiteral("çekmek"));
        REQUIRE(50 == turkish.numberOfSynSetsWithLiteral("tutmak"));
        REQUIRE(59 == turkish.numberOfSynSetsWithLiteral("çıkmak"));
    }

    SECTION("WordNetTest-testGetSynSetsWithPartOfSpeech") {
        REQUIRE(43882 == turkish.getSynSetsWithPartOfSpeech(Pos::NOUN).size());
        REQUIRE(17773 == turkish.getSynSetsWithPartOfSpeech(Pos::VERB).size());
        REQUIRE(12406 == turkish.getSynSetsWithPartOfSpeech(Pos::ADJECTIVE).size());
        REQUIRE(2549 == turkish.getSynSetsWithPartOfSpeech(Pos::ADVERB).size());
        REQUIRE(1552 == turkish.getSynSetsWithPartOfSpeech(Pos::INTERJECTION).size());
        REQUIRE(74 == turkish.getSynSetsWithPartOfSpeech(Pos::PRONOUN).size());
        REQUIRE(61 == turkish.getSynSetsWithPartOfSpeech(Pos::CONJUNCTION).size());
        REQUIRE(30 == turkish.getSynSetsWithPartOfSpeech(Pos::PREPOSITION).size());
    }

    SECTION("WordNetTest-testGetInterlingual") {
        REQUIRE(1 == turkish.getInterlingual("ENG31-05674544-n").size());
        REQUIRE(2 == turkish.getInterlingual("ENG31-00220161-r").size());
        REQUIRE(3 == turkish.getInterlingual("ENG31-02294200-v").size());
        REQUIRE(4 == turkish.getInterlingual("ENG31-06205574-n").size());
        REQUIRE(5 == turkish.getInterlingual("ENG31-02687605-v").size());
        REQUIRE(6 == turkish.getInterlingual("ENG31-01099197-n").size());
        REQUIRE(7 == turkish.getInterlingual("ENG31-00587299-n").size());
        REQUIRE(9 == turkish.getInterlingual("ENG31-02214901-v").size());
        REQUIRE(10 == turkish.getInterlingual("ENG31-02733337-v").size());
        REQUIRE(19 == turkish.getInterlingual("ENG31-00149403-v").size());
    }

    SECTION("WordNetTest-testSize") {
        REQUIRE(78327 == turkish.size());
    }

    SECTION("WordNetTest-testTotalForeignLiterals") {
        int count = 0;
        for (const SynSet& synSet : turkish.getSynSetList()){
            for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
                if (!synSet.getSynonym().getLiteral(i).getOrigin().empty()){
                    count++;
                }
            }
        }
        REQUIRE(3981 == count);
    }

    SECTION("WordNetTest-testTotalGroupedLiterals") {
        int count = 0;
        for (const SynSet& synSet : turkish.getSynSetList()){
            for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
                if (synSet.getSynonym().getLiteral(i).getGroupNo() != 0){
                    count++;
                }
            }
        }
        REQUIRE(5973 == count);
    }

    SECTION("WordNetTest-testGroupSize") {
        CounterHashMap<int> groups = CounterHashMap<int>();
        for (const SynSet& synSet : turkish.getSynSetList()){
            vector<Synonym> literalGroups = synSet.getSynonym().getUniqueLiterals();
            for (const Synonym& synonym : literalGroups){
                if (synonym.getLiteral(0).getGroupNo() != 0){
                    groups.put(synonym.literalSize());
                }
            }
        }
        REQUIRE(0 == groups.count(1));
        REQUIRE(2949 == groups.count(2));
        REQUIRE(21 == groups.count(3));
        REQUIRE(3 == groups.count(4));
    }

    SECTION("WordNetTest-testFindPathToRoot") {
        REQUIRE(1 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0814560")).size());
        REQUIRE(2 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0755370")).size());
        REQUIRE(3 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0516010")).size());
        REQUIRE(4 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0012910")).size());
        REQUIRE(5 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0046370")).size());
        REQUIRE(6 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0186560")).size());
        REQUIRE(7 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0172740")).size());
        REQUIRE(8 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0195110")).size());
        REQUIRE(9 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0285060")).size());
        REQUIRE(10 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0066050")).size());
        REQUIRE(11 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0226380")).size());
        REQUIRE(12 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0490230")).size());
        REQUIRE(13 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-1198750")).size());
        REQUIRE(12 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0412120")).size());
        REQUIRE(13 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-1116690")).size());
        REQUIRE(13 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0621870")).size());
        REQUIRE(14 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0822980")).size());
        REQUIRE(15 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0178450")).size());
        REQUIRE(16 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0600460")).size());
        REQUIRE(17 == turkish.findPathToRoot(turkish.getSynSetWithId("TUR10-0656390")).size());
    }
}
