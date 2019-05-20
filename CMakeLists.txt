cmake_minimum_required(VERSION 3.12)
project(WordNet)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(WordNet CategoryType.h InterlingualDependencyType.h SemanticRelationType.h Relation.cpp Relation.h SemanticRelation.cpp SemanticRelation.h InterlingualRelation.cpp InterlingualRelation.h Literal.cpp Literal.h Synonym.cpp Synonym.h IdMapping.cpp IdMapping.h SynSet.cpp SynSet.h WordNet.cpp WordNet.h Similarity/Similarity.h Similarity/ICSimilarity.h Similarity/JCN.cpp Similarity/JCN.h Similarity/LCH.cpp Similarity/LCH.h Similarity/Lin.cpp Similarity/Lin.h Similarity/Resnik.cpp Similarity/Resnik.h Similarity/SimilarityPath.cpp Similarity/SimilarityPath.h Similarity/WuPalmer.cpp Similarity/WuPalmer.h PolarityType.h)
add_executable(TestWordNet CategoryType.h InterlingualDependencyType.h SemanticRelationType.h Relation.cpp Relation.h SemanticRelation.cpp SemanticRelation.h InterlingualRelation.cpp InterlingualRelation.h Literal.cpp Literal.h Synonym.cpp Synonym.h IdMapping.cpp IdMapping.h SynSet.cpp SynSet.h WordNet.cpp WordNet.h Similarity/Similarity.h Similarity/ICSimilarity.h Similarity/JCN.cpp Similarity/JCN.h Similarity/LCH.cpp Similarity/LCH.h Similarity/Lin.cpp Similarity/Lin.h Similarity/Resnik.cpp Similarity/Resnik.h Similarity/SimilarityPath.cpp Similarity/SimilarityPath.h Similarity/WuPalmer.cpp Similarity/WuPalmer.h TestWordNet.cpp PolarityType.h)

target_link_libraries(WordNet Dictionary XmlParser MorphologicalAnalysis Corpus)
target_link_libraries(TestWordNet Dictionary XmlParser MorphologicalAnalysis Corpus)