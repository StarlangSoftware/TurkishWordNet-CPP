cmake_minimum_required(VERSION 3.12)
project(WordNet)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(WordNet CategoryType.h InterlingualDependencyType.h SemanticRelationType.h Relation.cpp Relation.h SemanticRelation.cpp SemanticRelation.h)