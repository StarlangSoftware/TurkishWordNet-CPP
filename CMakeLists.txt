cmake_minimum_required(VERSION 3.12)
project(WordNet)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(morphological_analysis REQUIRED)

add_library(WordNet src/InterlingualDependencyType.h src/SemanticRelationType.h src/Relation.cpp src/Relation.h src/SemanticRelation.cpp src/SemanticRelation.h src/InterlingualRelation.cpp src/InterlingualRelation.h src/Literal.cpp src/Literal.h src/Synonym.cpp src/Synonym.h src/SynSet.cpp src/SynSet.h src/WordNet.cpp src/WordNet.h src/Similarity/Similarity.h src/Similarity/ICSimilarity.h src/Similarity/JCN.cpp src/Similarity/JCN.h src/Similarity/LCH.cpp src/Similarity/LCH.h src/Similarity/Lin.cpp src/Similarity/Lin.h src/Similarity/Resnik.cpp src/Similarity/Resnik.h src/Similarity/SimilarityPath.cpp src/Similarity/SimilarityPath.h src/Similarity/WuPalmer.cpp src/Similarity/WuPalmer.h
        src/IdMapping.cpp)
add_executable(Test src/InterlingualDependencyType.h src/SemanticRelationType.h src/Relation.cpp src/Relation.h src/SemanticRelation.cpp src/SemanticRelation.h src/InterlingualRelation.cpp src/InterlingualRelation.h src/Literal.cpp src/Literal.h src/Synonym.cpp src/Synonym.h src/SynSet.cpp src/SynSet.h src/WordNet.cpp src/WordNet.h src/Similarity/Similarity.h src/Similarity/ICSimilarity.h src/Similarity/JCN.cpp src/Similarity/JCN.h src/Similarity/LCH.cpp src/Similarity/LCH.h src/Similarity/Lin.cpp src/Similarity/Lin.h src/Similarity/Resnik.cpp src/Similarity/Resnik.h src/Similarity/SimilarityPath.cpp src/Similarity/SimilarityPath.h src/Similarity/WuPalmer.cpp src/Similarity/WuPalmer.h Test/WordNetTest.cpp Test/LCHTest.cpp Test/SimilarityPathTest.cpp Test/WuPalmerTest.cpp)
target_link_libraries(WordNet morphological_analysis::morphological_analysis)
target_link_libraries(Test morphological_analysis::morphological_analysis)