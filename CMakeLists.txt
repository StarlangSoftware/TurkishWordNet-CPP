cmake_minimum_required(VERSION 3.12)
project(WordNet)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(WordNet CategoryType.h InterlingualDependencyType.h SemanticRelationType.h Relation.cpp Relation.h SemanticRelation.cpp SemanticRelation.h InterlingualRelation.cpp InterlingualRelation.h Literal.cpp Literal.h Synonym.cpp Synonym.h IdMapping.cpp IdMapping.h SynSet.cpp SynSet.h)

target_link_libraries(WordNet Dictionary)